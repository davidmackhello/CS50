<?php
    date_default_timezone_set('US/Eastern');
    $time = date('h:i:s', time());
?>

<html>
    <head>
        <style>
            
            body
            {
                font-family: tahoma;
            }
            
        </style>
        <title>Current time in Cambridge</title>
    </head>
    <body>
        The current time in Cambridge is <?= $time ?>.
    </body>
</html>