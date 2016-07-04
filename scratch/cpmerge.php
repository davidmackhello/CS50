#!/usr/bin/env php
<?php

    // ensure proper number of command line arguments
    if ($argc !== 2)
    {
        print("Usage: ./cpmerge /filepath\n");
        exit;
    }
    
    // ensure file exists
    if (!file_exists($argv[1]))
    {
        print("File does not exist! Please note file names are case sensitive.\n");
        exit;
    }
    
    // ensure file is a readable .csv file
    if (!is_readable($argv[1]) || (pathinfo($argv[1], PATHINFO_EXTENSION) !== "csv"))
    {
        print("The file is not readable. Please submit a valid .csv file!\n");
        exit;
    }
    
    $i = 0;
    $num = 0;
    $string = "";
    
    // open files
    if ((($csvfile = fopen($argv[1], "r")) !== false) && (($outfile = fopen("outfile.txt", "w")) !== false))
    {
        // iterate through each row of csv
        while (($data = fgetcsv($csvfile, 500)) !== false)
        {
            // set counter
            $i += $data[0];
            
            // set print freq
            $num += $data[0];
            
            // evaluate count
            switch ($i)
            {
                
            case ($i === 1):
                $string .= $data[3]."\n";
                for ($j = 0; $j < $num; $j++)
                {
                    fwrite($outfile, $string);
                }
                $i = 0;
                $num = 0;
                $string = "";
                break;
                
            case ($i === 2):
                
                $string .= ($num === 2) ? $data[3]." and " : $data[3].", and ";
                $i--;
                break;
                
            case ($i > 2):
                $string .= $data[3].", ";
                $i--;                
                break;
            }
        }
        
        // close file and exit
        fclose($csvfile);
        fclose($outfile);
        print("Import completed!\n");
        exit;
    }
    
    // file was not opened
    else
    {
        print("Could not open file.\n");
    }
    
?>