<?php

    // configuration
    require("../includes/config.php");
    
    // if user reached page via GET (link or redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // render quote lookup form
        render("quote_lookup.php", ["title" => "Quote", "greeting" => "Lookup Quote"]);
    }
    
    // if user reached page via POST
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // ensure symbol submitted
        if (empty($_POST["symbol"]))
        {
            apologize(["text" => "You must provide a symbol.", "redirect" => "quote.php"]);
        }
        
        // look up stock
        else
        {
            $stock = lookup($_POST["symbol"]);
            
            // apologize if stock does not exist
            if ($stock === false)
            {
                apologize(["text" => "Please enter a valid symbol.", "redirect" => "quote.php"]);
            }
            
            // else return quote 
            else
            {
                render("quote_return.php", ["symbol" => $stock["symbol"], "name" => $stock["name"], "price" => number_format($stock["price"], 2, '.', ',')]);
            }
        }
    }