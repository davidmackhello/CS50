<?php

    // configuration
    require("../includes/config.php");

    // query portfolios table for all user positions
    $rows = CS50::query("SELECT symbol, shares FROM portfolios WHERE user_id = ?", $_SESSION["id"]);

    // extract symbols and shares
    $positions = [];
    foreach ($rows as $row)
    {
        $positions[$row["symbol"]] = $row["shares"];
    }
    
    // if user reached page via GET
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // check for empty portfolio
        if (count($rows) == 0)
        {
            apologize(["text" => "You have no stocks to sell!", "redirect" => "/"]);
        }
        
        // render sell form
        else
        {
            // extract symbols
            $symbols = array_keys($positions);
            render("sell_form.php", ["title" => "Sell", "greeting" => "Sell Stock", "symbols" => $symbols]);
        }
    }
    
    // if user reached page via POST
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // ensure symbol submitted
        if (empty($_POST["symbol"]))
        {
            apologize(["text" => "You must select a stock.", "redirect" => "sell.php"]);
        }
        
        // ensure share quantity submitted
        if (empty($_POST["shares"]))
        {
            apologize(["text" => "You must specify a number of shares.", "redirect" => "sell.php"]);
        }
        
        // ensure valid number of shares inputted
        if (!ctype_digit($_POST["shares"]) || $_POST["shares"] > $positions[$_POST["symbol"]])
        {
            apologize(["text" => "Invalid number of shares.", "redirect" => "sell.php"]);
        }
        
        // else update cash and shares
        else
        {
            // lookup stock price and calculate sale amount
            $stock = lookup($_POST["symbol"]);
            $sold = $_POST["shares"] * $stock["price"];
            
            // add cash to user's account
            CS50::query("UPDATE users SET cash = cash + ? WHERE id = ?", $sold, $_SESSION["id"]);
            
            // update shares
            CS50::query("UPDATE portfolios SET shares = shares - ? WHERE user_id = ? AND symbol = ?", $_POST["shares"], $_SESSION["id"], $_POST["symbol"]);
            
            // delete entry if all shares sold
            if ($_POST["shares"] == $positions[$_POST["symbol"]])
            {
                CS50::query("DELETE FROM portfolios WHERE user_id = ? AND symbol = ?", $_SESSION["id"], $_POST["symbol"]);
            }
            
            // log history
            CS50::query("INSERT INTO history (user_id, transaction, symbol, shares, price) VALUES(?, 'SELL', ?, ?, ?)", $_SESSION["id"], $_POST["symbol"], $_POST["shares"], $stock["price"]);
            
            // redirect to portfolio
            redirect("/");
        }
    }
?>