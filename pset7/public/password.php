<?php

    // configuration
    require("../includes/config.php");

    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // render change password form
        render("password_form.php", ["title" => "Change Password", "greeting" => "Change Password"]);
    }

    // else if user reached page via POST (as by submitting a form via POST)
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // validate registration
        if (empty($_POST["oldpass"]))
        {
            apologize(["text" => "You must enter your old password.", "redirect" => "password.php"]);
        }
        else if (empty($_POST["password"]) || empty($_POST["confirmation"]))
        {
            apologize(["text" => "You must provide a new password.", "redirect" => "password.php"]);
        }
        else if ($_POST["password"] != $_POST["confirmation"])
        {
            apologize(["text" => "Passwords do not match.", "redirect" => "password.php"]);
        }
    
        // query user table for old hash
        $rows = CS50::query("SELECT hash FROM users WHERE id = ?", $_SESSION["id"]);

        // if we found hash, check password
        if (count($rows) == 1)
        {
            // compare hash of user's input against hash users in database
            if (password_verify($_POST["oldpass"], $rows[0]["hash"]))
            {
                // update new hash value in user table
                CS50::query("UPDATE users SET hash = ? WHERE id = ?", password_hash($_POST["password"], PASSWORD_DEFAULT), $_SESSION["id"]);
                
                // redirect to portfolio
                redirect("/");
            }
        }
        
        // else apologize
        apologize(["text" => "Invalid password entered.", "redirect" => "password.php"]);
    }
?>