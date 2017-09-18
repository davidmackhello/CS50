<?php

    // ensure proper usage
    if (!isset($_GET["string"]) || $_GET["string"] == "")
    {
        http_response_code(400);
        exit;
    }
    
    // Establish connection parameters for MySQL database
    $host = "127.0.0.1";
    $user = "machajew";
    $pass = "";
    $db = "finalproj";
    $port = 3306;
    
    // connect to mySQL
    $connection = mysqli_connect($host, $user, $pass, $db, $port) or die(mysql_error());
    
    // escape incoming typeahead query
    $string = mysqli_real_escape_string($connection, $_GET["string"]);
    
    // find partner matches in database for typeahead query
    $query = "SELECT * FROM startups WHERE startup LIKE '%$string%' LIMIT 10";
    $result = mysqli_query($connection, $query);
    while ($row = mysqli_fetch_assoc($result)) 
    {
        $startups[] = $row;
    }

    // free result and close connection
     mysqli_free_result($result);
     mysqli_close($connection);
    
    // output places as JSON (pretty-printed for debugging convenience)
    header("Content-type: application/json");
    print(json_encode($startups, JSON_PRETTY_PRINT));
    
?>