<?php

    // configuration
    require("../includes/config.php");

    // query portfolios table for all user positions and users table for cash
    $rows = CS50::query("SELECT symbol, shares FROM portfolios WHERE user_id = ?", $_SESSION["id"]);
    $cashrow = CS50::query("SELECT cash FROM users WHERE id = ?", $_SESSION["id"]);

    // check for empty portfolio
    if (count($rows) == 0)
    {
        // render empty portfolio view
        render("portfolio.php", ["title" => "Portfolio", "cash" => '$'.number_format($cashrow[0]["cash"], 2, '.', ','), "nostocks" => true, "greeting" => "My Portfolio"]);
    }
    
    // create array for all user positions
    $positions = [];
    foreach ($rows as $row)
    {
        $stock = lookup($row["symbol"]);
        if ($stock !== false)
        {
            $positions[] = [
                "Symbol" => $stock["symbol"],
                "Name" => $stock["name"],
                "Shares" => $row["shares"],
                "Price" => '$'.number_format($stock["price"], 2, '.', ','),
                "TOTAL" => '$'.number_format(($stock["price"] * $row["shares"]), 2, '.', ',')
                ];
        }
    }

    // render portfolio view
    render("portfolio.php", ["title" => "Portfolio", "cash" => '$'.number_format($cashrow[0]["cash"], 2, '.', ','), "positions" => $positions, "greeting" => "My Portfolio"]);
?>