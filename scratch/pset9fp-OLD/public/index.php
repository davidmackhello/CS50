<?php

    // configuration
    require("../includes/config.php");
    
    // ensure proper usage
    if (!isset($_GET["sheet"]) || $_GET["sheet"] == "")
    {
        http_response_code(400);
        exit;
    }
    
    $json = file_get_contents("../json/usg.json");

    $data = json_decode($json, TRUE);
    
    echo ('<pre>' . var_export($data, true) . '</pre>');

    // render generic view
    render("generic.php", ["title" => "USG"]);
?>