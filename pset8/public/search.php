<?php

    require(__DIR__ . "/../includes/config.php");

    // ensure proper usage
    if (!isset($_GET["geo"]) || $_GET["geo"] == "")
    {
        http_response_code(400);
        exit;
    }
    
    // numerically indexed array of places
    $places = [];

    // query matches from database
    $rows = CS50::query("SELECT * FROM places WHERE MATCH(postal_code, place_name, admin_name1) AGAINST (?) LIMIT 50", $_GET["geo"]);

    // if query returns results, add to places array
    if (count($rows) > 0)
    {
        foreach($rows as $row)
        {
            $places[] = $row;
        }
    }
        
    // support suggestions for 3-4 digit zip queries
    if(ctype_digit($_GET["geo"]) && strlen($_GET["geo"]) > 2 && strlen($_GET["geo"]) < 5)
    {
        // query matches from zip code column
        $rows = CS50::query("SELECT * FROM places WHERE postal_code LIKE ? LIMIT 50", $_GET["geo"] . "%");

        // if query returns result, add to places array
        if (count($rows) > 0)
        {
            foreach($rows as $row)
            {
                $places[] = $row;
            }
        }
    }
    
    // output places as JSON (pretty-printed for debugging convenience)
    header("Content-type: application/json");
    print(json_encode($places, JSON_PRETTY_PRINT));

?>