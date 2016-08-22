<?php
    
    // Establish connection parameters for MySQL database
    $host = "127.0.0.1";
    $user = "machajew";
    $pass = "";
    $db = "finalproj";
    $port = 3306;
    
    // connect to mySQL
    $connection = mysqli_connect($host, $user, $pass, $db, $port) or die(mysql_error());
    
    $query = "SELECT DISTINCT(startup_id) startup_id, person, email FROM referrals";
    $result = mysqli_query($connection, $query);
    while ($row = mysqli_fetch_assoc($result)) 
    {
        $startups[] = $row;
    }
    

    foreach($startups as $startup)
    {
        $id = mysqli_real_escape_string($connection, $startup["startup_id"]);
        $person = mysqli_real_escape_string($connection, $startup["person"]);
        $email = mysqli_real_escape_string($connection, $startup["email"]);
        $query = "UPDATE startups SET person = '$person', email = '$email' WHERE id = '$id'";
        $result = mysqli_query($connection, $query);
    }
    
    // free result and close connection
     mysqli_free_result($result);
     mysqli_close($connection);
    
    // output places as JSON (pretty-printed for debugging convenience)
    header("Content-type: application/json");
    print_r(json_encode($startups, JSON_PRETTY_PRINT));
    echo(count($startups));
    
?>