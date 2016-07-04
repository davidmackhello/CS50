<?php

    // configuration
    require("../includes/config.php"); 

    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // else render form
        render("login_form.php", ["title" => "Log In"]);
    }

    // else if user reached page via POST (as by submitting a form via POST)
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // validate submission
        if (empty($_POST["username"]))
        {
            apologize(["text" => "You must provide your username.", "redirect" => "login.php"]);
        }
        else if (empty($_POST["password"]))
        {
            apologize(["text" => "You must provide your password.", "redirect" => "login.php"]);
        }

        // query database for user
        $rows = CS50::query("SELECT * FROM users WHERE username = ?", $_POST["username"]);

        // if we found user, check password
        if (count($rows) == 1)
        {
            // first (and only) row
            $row = $rows[0];

            // compare hash of user's input against hash that's in database
            if (password_verify($_POST["password"], $row["hash"]))
            {
                // remember that user's now logged in by storing user's ID and username in session
                $_SESSION["id"] = $row["id"];
                $_SESSION["username"] = $row["username"];

                // redirect to portfolio
                redirect("/");
            }
        }

        // else apologize
        apologize(["text" => "Invalid username and/or password.", "redirect" => "login.php"]);

    }
?>
