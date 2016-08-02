<?php

    // page only takes POST requests (for ajax requests)
    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // request for listing of current ajax files
        if ($_POST["purpose"] == "sheetlist")
        {
            // open json directory
            if ($handle = opendir('../json')) 
            {
                // create array for json file names
                $a = array();
                
                // grab .json filenames from directory -- http://php.net/manual/en/function.readdir.php
                while (false !== ($entry = readdir($handle))) {
                    if ($entry != "." && $entry != "..") 
                    {
                        // remove file extension and add filenames to array -- http://stackoverflow.com/questions/2395882/how-to-remove-extension-from-string-only-real-extension
                        $a[] = preg_replace('/\\.[^.\\s]{4}$/', '', $entry);
                    }
                }
                closedir($handle);
            }
            
            // encode filename array for ajax
            header("Content-type: application/json");
            print(json_encode($a, JSON_PRETTY_PRINT));
        }

        // request for writing new .json files
        else if ($_POST["purpose"] == "write")
        {
            // open new .json file to store data
            if (($jsonfile = fopen("../json/".$_POST["slug"].".json", "w")) !== false)
            {
                // write json blob to file.
                if ((fwrite($jsonfile, json_encode($_POST["blob"], JSON_PRETTY_PRINT))) === FALSE) 
                {
                    http_response_code(400);
                    exit;
                }
                
                // on successful write
                else
                {
                    header("Content-type: text/html");
                    print("Your sheet was created successfully!");
                }
            }
            else
            {
                http_response_code(400);
                exit;
            }
        }
    }
    
    // 403 error non-POST requests
    else
    {
        http_response_code(403);
        exit;

    }
?>