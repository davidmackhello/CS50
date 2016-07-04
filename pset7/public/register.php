<?php

    // configuration
    require("../includes/config.php");

    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // render form
        render("register_form.php", ["title" => "Register", "greeting" => "Register"]);
    }

    // else if user reached page via POST (as by submitting a form via POST)
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // ensure username submitted
        if (empty($_POST["username"]))
        {
            apologize(["text" => "You must provide a username.", "redirect" => "register.php"]);
        }
        
        // ensure password fields submitted
        else if (empty($_POST["password"]) || empty($_POST["confirmation"]))
        {
            apologize(["text" => "You must provide a password.", "redirect" => "register.php"]);
        }
        
        // ensure passwords match
        else if ($_POST["password"] != $_POST["confirmation"])
        {
            apologize(["text" => "Passwords do not match.", "redirect" => "register.php"]);
        }
    
        // insert new user into database
        $rows = CS50::query("INSERT IGNORE INTO users (username, hash, cash) VALUES(?, ?, 5000.0000)", $_POST["username"], password_hash($_POST["password"], PASSWORD_DEFAULT));
        
        // check if user already exists
        if ($rows == 0)
        {
            apologize(["text" => "That username is taken. Please try another.", "redirect" => "register.php"]);
        }
        
        // if successful, log user in
        else if ($rows == 1)
        {
            $rows = CS50::query("SELECT LAST_INSERT_ID() AS id");
            $_SESSION["id"] = $rows[0]["id"];
            $_SESSION["username"] = $_POST["username"];
            
            // redirect to portfolio
            redirect("/");
        }
    }
?>