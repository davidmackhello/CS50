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
    
    // if post request (add new partner)
    if ($_SERVER["REQUEST_METHOD"] == "POST" && !empty($_POST["oldham"]))
    {
        // escape new partner name
        $string = mysqli_real_escape_string($connection, $_POST["oldham"]);
        
        // Insert new partner into database
        $query = "INSERT INTO partners (partner) VALUES('$string')";
        $result = mysqli_query($connection, $query);

        // close connection
        mysqli_close($connection);

        // redirect back to admin.php with GET method
        header("Location: admin.php");
        exit;
    }
    
    // retrieve all referral partners
    $query = "SELECT id, partner FROM partners ORDER BY partner";
    $result = mysqli_query($connection, $query);
    while ($row = mysqli_fetch_assoc($result)) 
    {
        $partners[] = $row;
    }

    // free result and close connection
     mysqli_free_result($result);
     mysqli_close($connection);

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
    
    // sort array alphabetically
    asort($sheetnames);
    
    // render admin page
    render("adminpage.php", ["sheetnames" => $sheetnames, "partners" => $partners]);

?>