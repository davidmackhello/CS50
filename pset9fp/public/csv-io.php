<?php

    // determine CSV write request
    if ($_GET["purpose"] == "referrals")
    {
        // Establish connection parameters for MySQL database
        $host = "127.0.0.1";
        $user = "machajew";
        $pass = "";
        $db = "finalproj";
        $port = 3306;
        
        // output headers so that the file is downloaded rather than displayed
        header('Content-Type: text/csv; charset=utf-8');
        header('Content-Disposition: attachment; filename=referrals.csv');

        // create a file pointer connected to the output stream
        $output = fopen('php://output', 'w');
        
        // output the column headings
        fputcsv($output, array('startup', 'contact', 'email', 'referred by', 'referral_sheet_name', 'first time referred?', 'referral date'));

        // connect to mySQL
        $connection = mysqli_connect($host, $user, $pass, $db, $port) or die(mysql_error());

        // retrieve all referral data
        $query = "SELECT startups.startup, startups.person, startups.email, partners.partner, referrals.sheet_name, referrals.first_time, referrals.timestamp FROM referrals LEFT JOIN startups ON referrals.startup_id=startups.id LEFT JOIN partners ON referrals.partner_id=partners.id WHERE referrals.timestamp > 0 ORDER BY referrals.id";
        $result = mysqli_query($connection, $query);
        while ($row = mysqli_fetch_assoc($result)) fputcsv($output, $row);
       
        // free result and close connection
        mysqli_free_result($result);
        mysqli_close($connection);
    }
?>