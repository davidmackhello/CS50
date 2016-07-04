#!/usr/bin/env php
<?php

    /***********************************************************************
     * speller.php
     *
     * David J. Malan
     * malan@harvard.edu
     *
     * Implements a spell-checker.
     **********************************************************************/ 

    require("dictionary.php");

    // maximum length for a word
    // (e.g., pneumonoultramicroscopicsilicovolcanoconiosis)
    define("LENGTH", 45);

    // default dictionary
    define("WORDS", "/home/cs50/pset5/dictionaries/large");

    // check for correct number of args
    if ($argc != 2 && $argc != 3)
    {
        print("Usage: speller [dictionary] text\n");
        return 1;
    }

    // benchmarks
    $time_load = 0.0; $time_check = 0.0; $time_size = 0.0; $time_unload = 0.0;

    // determine dictionary to use
    $dictionary = ($argc == 3) ? $argv[1] : WORDS;

    // load dictionary
    $before = microtime(true);
    $loaded = load($dictionary);
    $after = microtime(true);

    // abort if dictionary not loaded
    if (!$loaded)
    {
        print("Could not load $dictionary.\n");
        return 1;
    }

    // calculate time to load dictionary
    $time_load = $after - $before;

    // try to open file
    $file = ($argc == 3) ? $argv[2] : $argv[1];
    $fp = fopen($file, "r");
    if ($fp === false)
    {
        print("Could not open $file.\n");
        return 1;
    }

    // prepare to report misspellings
    printf("\nMISSPELLED WORDS\n\n");

    // prepare to spell-check
    $word  = "";
    $index = 0; $misspellings = 0; $words = 0;

    // spell-check each word in file
    for ($c = fgetc($fp); $c !== false; $c = fgetc($fp))
    {
        // allow alphabetical characters and apostrophes (for possessives)
        if (preg_match("/[a-zA-Z]/", $c) || ($c == "'" && $index > 0))
        {
            // append character to word
            $word .= $c;
            $index++;

            // ignore alphabetical strings too long to be words
            if ($index >= LENGTH)
            {
                // consume remainder of alphabetical string
                while (($c = fgetc($fp)) !== false && preg_match("/[a-zA-Z]/", $c));

                // prepare for new word
                $index = 0; $word = "";
            }
        }

        // ignore words with numbers (like MS Word)
        else if (ctype_digit($c))
        {
            // consume remainder of alphabetical string
            while (($c = fgetc($fp)) !== false && preg_match("/[a-zA-z0-9]/", $c));

            // prepare for new word
            $index = 0; $word = "";
        }

        // we must have found a whole word
        else if ($index > 0)
        {
            // update counter
            $words++;

            // check word's spelling
            $before = microtime(true);
            $misspelled = !check($word);
            $after = microtime(true);

            // update benchmark
            $time_check += $after - $before;

            // print word if misspelled
            if ($misspelled)
            {
                print("$word\n");
                $misspellings++;
            }

            // prepare for next word
            $index = 0; $word = "";
        }
    }

    // close file
    fclose($fp);

    // determine dictionary's size
    $before = microtime(true);
    $n = size();
    $after = microtime(true);

    // calculate time to determine dictionary's size
    $time_size = $after - $before;

    // unload dictionary
    $before = microtime(true);
    $unloaded = unload();
    $after = microtime(true);

    // abort if dictionary not unloaded
    if (!$unloaded)
    {
        print("Could not load $dictionary.\n");
        return 1;
    }
    // calculate time to determine dictionary's size
    $time_unload = $after - $before;

    // report benchmarks
    printf("\nWORDS MISSPELLED:     %d\n", $misspellings);
    printf("WORDS IN DICTIONARY:  %d\n", $n);
    printf("WORDS IN TEXT:        %d\n", $words);
    printf("TIME IN load:         %.2f\n", $time_load);
    printf("TIME IN check:        %.2f\n", $time_check);
    printf("TIME IN size:         %.2f\n", $time_size);
    printf("TIME IN unload:       %.2f\n", $time_unload);
    printf("TOTAL TIME:           %.2f\n\n", $time_load + $time_check + $time_size + $time_unload);

?>
