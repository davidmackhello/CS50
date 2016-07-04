<?php

    // configuration
    require("../includes/config.php");
    
    // if user reached page via GET
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // render deposit form
        render("deposit_form.php", ["title" => "Deposit", "greeting" => "Deposit Funds"]);
    }
    
    // if user reached page via POST
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // ensure cash value submitted
        if (empty($_POST["funds"]))
        {
            apologize(["text" => "You must enter a cash amount.", "redirect" => "deposit.php"]);
        }
        
        // ensure currency format is valid
        if (!isCurrency($_POST["funds"]))
        {
            apologize(["text" => "Please enter currency in correct format.", "redirect" => "deposit.php"]);
        }

        else
        {
            // update cash in users table
            CS50::query("UPDATE users SET cash = cash + ? WHERE id = ?", $_POST["funds"], $_SESSION["id"]);
            
            // redirect to portfolio
            redirect("/");
        }
    }
?>