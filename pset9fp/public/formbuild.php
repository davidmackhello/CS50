<?php

    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // open new .json file to store data
        if (($jsonfile = fopen("../json/".$_POST["slug"].".json", "w")) !== false)
        {
            // Write $somecontent to our opened file.
            if ((fwrite($jsonfile, json_encode($_POST["blob"], JSON_PRETTY_PRINT))) === FALSE) 
            {
                // output places as JSON (pretty-printed for debugging convenience)
                header("Content-type: text/html");
                print("there was a problem trying to WRITE the file");
            }
            
            else
            {
                header("Content-type: text/html");
                print("success!");
            }
        }
        
        else
        {
            header("Content-type: text/html");
            print("there was a problem OPENING the file");
        }
    }
    
?>