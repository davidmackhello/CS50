<?php require("../includes/helpers.php"); ?>

<?php render("header", ["title" => "Get1"]); ?>

<?php

    foreach($_GET as $key => $value)
    {
        print("<p><b>{$key}</b>: {$value}</p>");
    }

?>

<?php render("footer");