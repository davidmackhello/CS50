#!/usr/bin/env php
<?php

    /**
     * import
     *
     * Imports tab delimited .txt file into SQL database
     * 
     */

    require(__DIR__ . "/../includes/config.php");

    // ensure proper number of command line arguments
    if ($argc !== 2)
    {
        print("Usage: ./import /filepath\n");
        exit;
    }
    
    // ensure file exists
    if (!file_exists($argv[1]))
    {
        print("File does not exist! Please note file names are case sensitive.\n");
        exit;
    }
    
    // ensure file is a readable .txt file
    if (!is_readable($argv[1]) || (pathinfo($argv[1], PATHINFO_EXTENSION) !== "txt"))
    {
        print("The file is not readable. Please submit a valid .txt file!\n");
        exit;
    }
    
    // open file
    if (($txtfile = fopen($argv[1], "r")) !== false)
    {
        // get first argument for CS50 query INSERT function for all rows
        $sqlstring = queryarg("places", ["country_code", "postal_code", "place_name", "admin_name1", "admin_code1", "admin_name2", "admin_code2", "admin_name3", "admin_code3", "latitude", "longitude", "accuracy"]);
        
        // iterate through each row of tab-delimited file
        while (($data = fgetcsv($txtfile, 500, "\t")) !== false)
        {
            // prepend first query argument onto array of column data
            array_unshift($data, $sqlstring);
            
            // insert columns into table using array of parameters passed to CS50 query
            call_user_func_array("CS50::query", $data);
        }
        
        // close file and exit
        fclose($txtfile);
        print("Import completed!\n");
        exit;
    }
    
    // file was not opened
    else
    {
        print("Could not open file.\n");
    }
    
?>