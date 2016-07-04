<?php

    // configuration
    require("../includes/config.php");

    // query history table for all user transactions
    $rows = CS50::query("SELECT transaction, timestamp, symbol, shares, price FROM history WHERE user_id = ?", $_SESSION["id"]);

    // check for no transactions
    if (count($rows) == 0)
    {
        // render empty history view
        render("history.php", ["title" => "History", "nohist" => true]);
    }
    
    // create array for all user transactions
    $transactions = [];
    foreach ($rows as $row)
    {
        $transactions[] = [
            "transaction" => $row["transaction"],
            "date_time" => date_convert($row["timestamp"], 'UTC', 'Y-m-d H:i:s', 'EST', 'n/j/y g:ia T'),
            "symbol" => $row["symbol"],
            "shares" => $row["shares"],
            "price" => '$'.number_format($row["price"], 2, '.', ',')
            ];
    }
    
    // render history view
    render("history.php", ["title" => "History", "transactions" => $transactions]);
?>