<?php

    // configuration
    require("../includes/config.php");
    
    // Establish connection parameters for MySQL database
    $host = "127.0.0.1";
    $user = "machajew";
    $pass = "";
    $db = "finalproj";
    $port = 3306;
    
    // connect to mySQL
    $connection = mysqli_connect($host, $user, $pass, $db, $port) or die(mysql_error());
    
    // if post request (submitting new startup referrals into database)
    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // decode json string into array of associative arrays
        $referrals = json_decode($_POST["json"], true);
        
        // iterate through each startup referral
        foreach($referrals as $referral)
        {
            // retrieve startup_id for new referral
            $startup_id = $referral["startup_id"];
            
            // set bool for first-time startups (defaults to false)
            $firsttime = 0;
               
            // insert startup records that are new to the system
            if ($startup_id == "new")
            {
                // set bool for first-time referral
                $firsttime = 1;
                
                // escape column values for insert into startups table
                $startup = mysqli_real_escape_string($connection, $referral["startup"]);
                $contact = mysqli_real_escape_string($connection, $referral["contact"]);
                $email = mysqli_real_escape_string($connection, $referral["email"]);
        
                // insert new startup
                $query = "INSERT INTO startups (startup, person, email) VALUES('$startup', '$contact', '$email')";
                mysqli_query($connection, $query);

                // retrieve last startup id for use in referrals table                
                $query = "SELECT LAST_INSERT_ID()";
                $result = mysqli_query($connection, $query);
                while ($row = mysqli_fetch_row($result)) 
                {
                    $startup_id = $row[0];
                }
                mysqli_free_result($result);
            }
            
            // escape column values for insert into referrals table
            $startup_id = mysqli_real_escape_string($connection, $startup_id);
            $partner_id = mysqli_real_escape_string($connection, $_POST["partner_id"]);
            $sheet_name = mysqli_real_escape_string($connection, $_POST["slug"]);
            $firsttime = mysqli_real_escape_string($connection, $firsttime);
            
            // insert new referral record
            $query = "INSERT INTO referrals (startup_id, partner_id, sheet_name, first_time) VALUES('$startup_id', '$partner_id', '$sheet_name', '$firsttime')";
            mysqli_query($connection, $query);
        }

        // close connection
        mysqli_close($connection);

        // render thank you page
        render("thanks.php", ["logo" => $_POST["logo"]]);
    }
    
    // if GET request (render referral form for partner)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // retrieve all partners and place in assoc array by partner id
        $query = "SELECT * FROM partners";
        $result = mysqli_query($connection, $query);
        while ($row = mysqli_fetch_assoc($result)) 
        {
            $partners[$row["id"]] = $row["partner"];
        }
    
        // free result and close connection
         mysqli_free_result($result);
         mysqli_close($connection);
    
        // ensure proper usage
        if (isset($_GET["sheet"]) && isset($_GET["p_id"]) && $_GET["p_id"] !== "" && isset($_GET["logo"]) && $_GET["logo"] !== "")
        {
            // create array for json file names
            $sheetnames = [];
    
            // open json directory
            if ($handle = opendir('../json')) 
            {
                // grab .json filenames from directory -- http://php.net/manual/en/function.readdir.php
                while (false !== ($entry = readdir($handle))) {
                    if ($entry != "." && $entry != "..") 
                    {
                        // remove file extension and add filenames to array -- http://stackoverflow.com/questions/2395882/how-to-remove-extension-from-string-only-real-extension
                        $sheetnames[] = preg_replace('/\\.[^.\\s]{4}$/', '', $entry);
                    }
                }
                closedir($handle);
            }
    
            // ensure sheet exists
            if (!in_array($_GET["sheet"], $sheetnames))
            {
                http_response_code(400);
                exit;
            }
            
            // ensure partner exists
            if (!array_key_exists($_GET["p_id"], $partners))
            {
                http_response_code(400);
                exit;
            }
        }
    
        else
        {
            http_response_code(400);
            exit;
        }
    
        // retrieve json string from requested sheet
        $json = file_get_contents("../json/{$_GET["sheet"]}.json");
    
        // decode json string into associative array
        $items = json_decode($json, TRUE);
    
        // remove first object (contains sheet info) from array
        $sheetinfo = array_shift($items);
    
        // render list view and referral form for partners
        render("list.php", ["p_id" => $_GET["p_id"], "partner" => $partners[$_GET["p_id"]], "slug" => $_GET["sheet"], "sheetinfo" => $sheetinfo, "items" => $items, "logo" => $_GET["logo"]]);
    }
?>