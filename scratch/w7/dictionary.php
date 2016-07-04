<?php

    /**
     * dictionary.php
     *
     * David J. Malan
     * malan@harvard.edu
     *
     * Implements a dictionary in a (non-object-oriented) way that
     * mimics Problem Set 6's implementation in C.  However, an 
     * object-oriented design would be better in PHP.
     */

    // size of dictionary
    $size = 0;

    // hash table
    $table = [];

    /**
     * Returns true if word is in dictionary else false.
     */
    function check($word)
    {
        global $table;
        if (isset($table[strtolower($word)]))
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    /**
     * Loads dictionary into memory.  Returns true if successful else false.
     */
    function load($dictionary)
    {
        global $table, $size;
        if (!file_exists($dictionary) && is_readable($dictionary))
        {
            return false;
        }
        foreach (file($dictionary) as $word)
        {
            $table[chop($word)] = true;
            $size++;
        }
        return true;
    }

    /**
     * Returns number of words in dictionary if loaded else 0 if not yet loaded.
     */
    function size()
    {
        global $size;
        return $size;
    }

    /**
     * Unloads dictionary from memory.  Returns true if successful else false.
     */
    function unload()
    {
        return true;
    }

?>
