from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session, url_for, Markup
from flask_session import Session
from passlib.apps import custom_app_context as pwd_context
from tempfile import mkdtemp

from helpers import *

# configure application
app = Flask(__name__)

# ensure responses aren't cached
if app.config["DEBUG"]:
    @app.after_request
    def after_request(response):
        response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
        response.headers["Expires"] = 0
        response.headers["Pragma"] = "no-cache"
        return response

# custom filter
app.jinja_env.filters["usd"] = usd

# configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

@app.route("/")
@login_required
def index():
    """ Default view - table of user holdings"""

    # retrieve portfolio and cash data
    rows = db.execute("SELECT symbol, quantity FROM stocks "
                        "WHERE user_id = :user_id ORDER BY symbol", 
                        user_id=session["user_id"])

    cashrow = db.execute("SELECT cash FROM users WHERE id = :id", 
                        id=session["user_id"])
    
    # assemble list of stock objects
    stocks = []
    for row in rows:
        # retrieve stock data
        this_stock = lookup(row["symbol"])

        # store each stock param in list
        if this_stock != None:
            stocks.append([
                row["symbol"],
                this_stock["name"],
                row["quantity"],
                usd(this_stock["price"]),
                usd(row["quantity"] * this_stock["price"])
            ])
    
    return render_template("index.html", stocks=stocks, cash=cashrow[0]["cash"])

@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock."""
    
    # if user reaches route via POST
    if request.method == "POST":

        # ensure symbol entered
        if not request.form.get("symbol"):
            return apology("must enter ticker symbol")

        # ensure positive int entered
        shares = is_posint(request.form.get("shares"))
        if not shares:
            return apology("must enter valid number of shares")

        # retrieve stock data
        stock = lookup(request.form.get("symbol"))

        # apologize if no stock data
        if stock == None:
            return apology("invalid ticker")
            
        # calculate cost, determine if user can afford
        cost = shares * stock["price"]
        rows = db.execute("SELECT cash FROM users WHERE id = :id", id=session["user_id"])
        if cost > rows[0]["cash"]:
            return apology("you can't afford that")
        else:
            # update user cash
            db.execute("UPDATE users SET cash = cash - :cost WHERE id = :id", 
                        cost=cost, id=session["user_id"])
            
            # update portfolio, inserting new user/stock row if needed
            db.execute("INSERT OR IGNORE INTO stocks (symbol, quantity, user_id) "
                        "VALUES(:symbol, 0, :user_id);", 
                        symbol=stock["symbol"], user_id=session["user_id"])
            db.execute("UPDATE stocks SET quantity = quantity + :shares "
                        "WHERE symbol = :symbol and user_id = :user_id;", 
                        shares=shares, symbol=stock["symbol"], user_id=session["user_id"])
    
            # log transaction
            db.execute("INSERT INTO transactions (symbol, price, user_id, action, shares) "
                        "VALUES(:symbol, :price, :user_id, :action, :shares);", 
                        symbol=stock["symbol"], price=stock["price"], user_id=session["user_id"], 
                        action="BUY", shares=shares)

            # return to index
            return redirect(url_for("index"))

    # if user reaches route via GET
    else:
        return render_template("buy.html")

@app.route("/history")
@login_required
def history():
    """Show history of transactions."""
    
    # retrieve all transactions for user
    rows = db.execute("SELECT * FROM transactions WHERE user_id = :user_id", user_id=session["user_id"])
    
    # store each transaction as ordered list in list
    transactions = []
    for row in rows:
        transactions.append([
            row["symbol"],
            usd(row["price"]),
            row["action"],
            row["shares"],
            row["datetime"]
        ])

    return render_template("history.html", transactions=transactions)

@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in."""

    # forget any user_id
    session.clear()

    # if user reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username")

        # ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password")

        # query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username", username=request.form.get("username"))

        # ensure username exists and password is correct
        if len(rows) != 1 or not pwd_context.verify(request.form.get("password"), rows[0]["hash"]):
            return apology("invalid username and/or password")

        # remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # redirect user to home page
        return redirect(url_for("index"))

    # else if user reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")

@app.route("/logout")
def logout():
    """Log user out."""

    # forget any user_id
    session.clear()

    # redirect user to login form
    return redirect(url_for("login"))

@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    
    # if user reaches route via POST
    if request.method == "POST":
        
        # ensure symbol was submitted
        if not request.form.get("symbol"):
            return apology("must enter ticker symbol")
            
        # retrieve stock data
        stock = lookup(request.form.get("symbol"))

        # apologize if no stock data
        if stock == None:
            return apology("no stock data")
            
        # share stock info
        else:
            return render_template("quote_return.html", stock=stock)

    # else if reached via GET
    else:
        return render_template("quote_lookup.html")

@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user."""
    
    # forget any user_id
    session.clear()    
    
    # if user reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username")

        # ensure password fields were submitted
        elif not request.form.get("password") or not request.form.get("confirm"):
            return apology("must provide password")

        # ensure passwords match
        elif request.form.get("password") != request.form.get("confirm"):
            return apology("passwords must match")

        # check if username taken
        rows = db.execute("SELECT * FROM users WHERE username = :username", username=request.form.get("username"))
        if len(rows) > 0:
            return apology("username taken")

        # store username and password and retrieve new user ID
        insert = db.execute("INSERT INTO users (username, hash) VALUES(:username, :hash)", 
                            username=request.form.get("username"), hash=pwd_context.hash(request.form.get("password"))) 

        # if SQL error
        if insert == None:
            return apology("SQL error")

        else:
            # log user in
            session["user_id"] = insert

            # redirect user to home page
            return redirect(url_for("index"))

    # else if user reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("register.html")

@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock."""

    # retrieve portfolio info
    rows = db.execute("SELECT symbol, quantity FROM stocks "
                        "WHERE user_id = :user_id ORDER BY symbol", 
                        user_id=session["user_id"])

    # if user reaches route via POST
    if request.method == "POST":

        # ensure symbol entered
        if not request.form.get("symbol"):
            return apology("must select ticker symbol")

        # ensure positive int entered
        shares = is_posint(request.form.get("shares"))
        if not shares:
            return apology("must enter valid number of shares")

        # ensure user has enough shares to sell
        share_dict = {row["symbol"]: row["quantity"] for row in rows}
        if shares > share_dict[request.form.get("symbol")]:
            return apology("you don't have that many shares")

        # retrieve stock data
        stock = lookup(request.form.get("symbol"))

        # apologize if no stock data
        if stock == None:
            return apology("invalid ticker")

        # calculate price and update cash
        price = shares * stock["price"]
        db.execute("UPDATE users SET cash = cash + :price WHERE id = :id;", 
                    price=price, id=session["user_id"])

        # remove row if all shares sold
        if shares == share_dict[request.form.get("symbol")]:
            db.execute("DELETE FROM stocks WHERE symbol = "
                        ":symbol AND user_id = :user_id;", 
                        symbol=request.form.get("symbol"), user_id=session["user_id"])

        # otherwise update stock quantity
        else:
            db.execute("UPDATE stocks SET quantity = quantity - :shares "
                        "WHERE symbol = :symbol AND user_id = :user_id;", 
                        shares=shares, symbol=request.form.get("symbol"), user_id=session["user_id"])

        # log transaction
        db.execute("INSERT INTO transactions (symbol, price, user_id, action, shares) "
                    "VALUES(:symbol, :price, :user_id, :action, :shares);", 
                    symbol=stock["symbol"], price=stock["price"], user_id=session["user_id"], 
                    action="SELL", shares=shares)

        # return to index
        return redirect(url_for("index"))

    # if user reaches route via GET
    else:
        return render_template("sell.html", symbols=[row["symbol"] for row in rows])