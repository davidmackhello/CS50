<?php

    // configuration
    require("../includes/config.php");
    
    // if user reached page via GET
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // render buy form
        render("buy_form.php", ["title" => "Buy", "greeting" => "Buy New Stock"]);
    }
    
    // if user reached page via POST
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // ensure symbol submitted
        if (empty($_POST["symbol"]))
        {
            apologize(["text" => "You must specify a stock to purchase.", "redirect" => "buy.php"]);
        }
        
        // ensure shares submitted
        if (empty($_POST["shares"]))
        {
            apologize(["text" => "You must specify a number of shares.", "redirect" => "buy.php"]);
        }
        
        // ensure valid number of shares inputted
        if (!ctype_digit($_POST["shares"]))
        {
            apologize(["text" => "Invalid number of shares.", "redirect" => "buy.php"]);
        }
        
        // look up stock
        $stock = lookup($_POST["symbol"]);
        
        // ensure stock exists
        if ($stock === false)
        {
            apologize(["text" => "Please enter a valid symbol.", "redirect" => "buy.php"]);
        }
        
        // check to make sure user can afford purchase
        $rows = CS50::query("SELECT cash FROM users WHERE id = ?", $_SESSION["id"]);
        $debit = $_POST["shares"] * $stock["price"];

        // block illegal purchase
        if ($debit > $rows[0]["cash"])
        {
            apologize(["text" => "You can't afford that.", "redirect" => "buy.php"]);
        }
        
        // else update cash and shares
        else
        {
            // update cash
            CS50::query("UPDATE users SET cash = cash - ? WHERE id = ?", $debit, $_SESSION["id"]);
            
            // format symbol
            $symbol = strtoupper($_POST["symbol"]);
            
            // update shares
            CS50::query("INSERT INTO portfolios (user_id, symbol, shares) VALUES(?, ?, ?) ON DUPLICATE KEY UPDATE shares = shares + VALUES(shares)", $_SESSION["id"], $symbol, $_POST["shares"]);
            
            // log history
            CS50::query("INSERT INTO history (user_id, transaction, symbol, shares, price) VALUES(?, 'BUY', ?, ?, ?)", $_SESSION["id"], $symbol, $_POST["shares"], $stock["price"]);
            
            // redirect to portfolio
            redirect("/");
        }
    }
?>