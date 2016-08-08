<?php

    // configuration
    require("../includes/config.php");

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
    
    // sort array and render admin page
    asort($sheetnames);
    render("adminpage.php", ["sheetnames" => $sheetnames]);
    
?>