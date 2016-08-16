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
    
    // retrieve all partners and place in assoc array by partner_id
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
        // create array for json file names and bool to test for match
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
    render("list.php", ["partner" => $partners[$_GET["p_id"]], "sheetinfo" => $sheetinfo, "items" => $items, "logo" => $_GET["logo"]]);
?>