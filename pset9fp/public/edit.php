<?php

    // configuration
    require("../includes/config.php");
    
    // ensure proper usage
    if (isset($_GET["sheet"]))
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
    }
    else
    {
        http_response_code(400);
        exit;
    }
    
    // retrieve json data for given sheet
    $json = file_get_contents("../json/{$_GET["sheet"]}.json");

    // decode json string into associative array
    $items = json_decode($json, TRUE);
    
    // remove first object (contains sheet info) from array
    $sheetinfo = array_shift($items);
    
    // create and fill array that counts # of bullets to add for each block
    $blocknum = [];
    foreach ($items as $item)
    {
        $blocknum[] = count($item["areas"]);
    }
    
    // retrieve html for block section of admin form (generates 1 block with 1 bullet)
    $bullethtml = file_get_contents("../views/bullet.php");
    $blockhtml = file_get_contents("../views/blocktop.php").$bullethtml.file_get_contents("../views/blockbottom.php");
    
    // render admin form (edit view)
    render("build-edit-form.php", ["blocknum" => $blocknum, "sheetinfo" => $sheetinfo, "items" => $items, "slug" => $_GET["sheet"], "blockhtml" => $blockhtml, "bullethtml" => $bullethtml]);
?>