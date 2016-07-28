<?php

    // configuration
    require("../includes/config.php");
    
    // ensure proper usage
    if (!isset($_GET["sheet"]) || $_GET["sheet"] == "" || !isset($_GET["partner"]) || $_GET["partner"] == "")
    {
        http_response_code(400);
        exit;
    }
    
    $json = file_get_contents("../json/{$_GET["sheet"]}.json");

    $items = json_decode($json, TRUE);
    
    $sheetinfo = array_shift($items);
    
    // render list view
    render("list.php", ["title" => $_GET["sheet"], "partner" => $_GET["partner"], "items" => $items, "sheetinfo" => $sheetinfo]);
    
?>