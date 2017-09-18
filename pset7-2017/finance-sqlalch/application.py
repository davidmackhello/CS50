from flask import Flask, flash, redirect, render_template, request, session, url_for, Markup
from flask_session import Session
from flask_sqlalchemy import SQLAlchemy
from sqlalchemy import and_
from passlib.apps import custom_app_context as pwd_context
from tempfile import mkdtemp
from datetime import datetime

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

# Flask-SQLAlchemy
app.config["SQLALCHEMY_TRACK_MODIFICATIONS"] = False
app.config["SQLALCHEMY_DATABASE_URI"] = "sqlite:///finance.db"
app.config["SQLALCHEMY_ECHO"] = True
db = SQLAlchemy(app)

class User(db.Model):

    __tablename__ = "users"
    id = db.Column(db.Integer, nullable=False, primary_key=True)
    username = db.Column(db.Text, nullable=False, unique=True)
    hash = db.Column(db.Text, nullable=False)
    cash = db.Column(db.Float, nullable=False, default=10000.00)

    def __init__(self, username, password):
        self.username = username
        self.hash = pwd_context.hash(password)

class Stock(db.Model):

    __tablename__ = "stocks"
    id = db.Column(db.Integer, nullable=False, primary_key=True)
    symbol = db.Column(db.Text, nullable=False)
    quantity = db.Column(db.Integer, nullable=False)
    
    user_id = db.Column(db.Integer, db.ForeignKey('users.id'))
    user = db.relationship('User', backref=db.backref('stocks', lazy='dynamic'))

    def __init__(self, symbol, quantity, user):
        self.symbol = symbol
        self.quantity = quantity
        self.user = user

class Transaction(db.Model):

    __tablename__ = "transactions"
    id = db.Column(db.Integer, nullable=False, primary_key=True)
    symbol = db.Column(db.Text, nullable=False)
    price = db.Column(db.Float, nullable=False)
    datetime = db.Column(db.Integer, nullable=False, default=datetime.utcnow)
    action = db.Column(db.Text, nullable=False)
    shares = db.Column(db.Integer, nullable=False)

    user_id = db.Column(db.Integer, db.ForeignKey('users.id'))
    user = db.relationship('User', backref=db.backref('transactions', lazy='dynamic'))

    def __init__(self, symbol, price, action, shares, user):
        self.symbol = symbol
        self.price = price
        self.action = action
        self.shares = shares
        self.user = user

@app.route("/")
@login_required
def index():
    """ Default view - table of user holdings"""

    # retrieve portfolio and cash data
    user = User.query.filter(User.id == session["user_id"]).first()
    user_stocks = Stock.query.filter(Stock.user == user).order_by(Stock.symbol).all()

    # assemble list of stock objects
    stocks = []
    for stock in user_stocks:
        # retrieve stock data
        this_stock = lookup(stock.symbol)

        # store each stock param in list
        if this_stock != None:
            stocks.append([
                stock.symbol,
                this_stock["name"],
                stock.quantity,
                usd(this_stock["price"]),
                usd(stock.quantity * this_stock["price"])
            ])
    
    return render_template("index.html", stocks=stocks, cash=round(user.cash, 2))

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

        # get user, calculate cost, determine if user can afford
        user = User.query.filter(User.id == session["user_id"]).first()
        cost = shares * stock["price"]
        cash = round(user.cash, 2)
        if cost > cash:
            return apology("you can't afford that")

        else:
            # update user cash
            user.cash = round(user.cash, 2) - cost

            # check if user already owns this stock
            this_stock = Stock.query.filter(and_(Stock.symbol == stock["symbol"],
                                            Stock.user_id == session["user_id"])).first()

            # insert stock purchase if new
            if this_stock == None:
                new_stock = Stock(stock["symbol"], shares, user)
                db.session.add(new_stock)

            # update existing stock holding
            else:
                this_stock.quantity = this_stock.quantity + shares

            # log transaction
            transaction = Transaction(stock["symbol"], stock["price"], 'BUY', shares, user)
            db.session.add(transaction)

            db.session.commit()
            return redirect(url_for("index"))
    
    # if user reaches route via GET
    else:
        return render_template("buy.html")

@app.route("/history")
@login_required
def history():
    """Show history of transactions."""

    # retrieve all transactions for user
    transactions = Transaction.query.filter(Transaction.user_id == session["user_id"]).all()
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
        user = User.query.filter(User.username == request.form.get("username")).first()

        # ensure username exists and password is correct
        if user == None or not pwd_context.verify(request.form.get("password"), user.hash):
            return apology("invalid username and/or password")

        # remember which user has logged in
        session["user_id"] = user.id

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
        users = User.query.filter(User.username == request.form.get("username")).all()
        if len(users) > 0:
            return apology("username taken")

        # store username and password and retrieve new user ID
        new_user = User(request.form.get("username"), request.form.get("password"))
        db.session.add(new_user)
        db.session.commit()

        # log user in
        session["user_id"] = new_user.id

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
    user_stocks = Stock.query.filter(Stock.user_id == session["user_id"]).all()

    # if user reaches route via POST
    if request.method == "POST":

        # ensure symbol entered
        if not request.form.get("symbol"):
            return apology("must select ticker symbol")

        # ensure positive int entered
        shares = is_posint(request.form.get("shares"))
        if not shares:
            return apology("must enter valid number of shares")
            
        # select stock
        this_stock = next(stock for stock in user_stocks 
                            if stock.symbol == request.form.get("symbol"))

        # ensure user has enough shares to sell
        if shares > this_stock.quantity:
            return apology("you don't have that many shares")

        # retrieve stock data
        stock = lookup(this_stock.symbol)

        # apologize if no stock data
        if stock == None:
            return apology("invalid ticker")

        # calculate price, get user, update cash
        price = shares * stock["price"]
        user = User.query.filter(User.id == session["user_id"]).first()
        user.cash = round(user.cash, 2) + price

        # remove row if all shares sold
        if shares == this_stock.quantity:
            db.session.delete(this_stock)

        # otherwise update stock quantity
        else:
            this_stock.quantity = this_stock.quantity - shares

        # log transaction
        this_transaction = Transaction(stock["symbol"], stock["price"], 'SELL', shares, user)
        db.session.add(this_transaction)

        # commit
        db.session.commit()

        # return to index
        return redirect(url_for("index"))

    # if user reaches route via GET
    else:
        return render_template("sell.html", symbols=[stock.symbol for stock in user_stocks])