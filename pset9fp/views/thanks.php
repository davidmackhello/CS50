<!DOCTYPE html>

<html>

    <head>
        <!-- jQuery -->
        <script src="https://code.jquery.com/jquery-3.1.0.min.js" integrity="sha256-cCueBR6CsyA4/9szpPfrX3s49M9vUU5BgtiJj06wt/s=" crossorigin="anonymous"></script>

        <!-- Bootstrap Latest compiled and minified CSS -->
        <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/css/bootstrap.min.css" integrity="sha384-BVYiiSIFeK1dGmJRAkycuHAHRg32OmUcww7on3RYdg4Va+PmSTsz/K68vbdEjh4u" crossorigin="anonymous">        
        
        <!-- Bootstrap Latest compiled and minified JavaScript -->
        <script src="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/js/bootstrap.min.js" integrity="sha384-Tc5IQib027qvyjSMfHjOMaLkfuWVxZxUPnCJA7l2mCWNIpG9mGCD8wGNIcPD7Txa" crossorigin="anonymous"></script>

        <!-- app CSS -->
        <link href="/css/styles.css" rel="stylesheet"/>

        <title>Thanks!</title>

    </head>
    
    <div class="device-xs visible-xs"></div>
    <div class="device-sm visible-sm"></div>
    <div class="device-md visible-md"></div>
    <div class="device-lg visible-lg"></div>
    
    <body class="bodycolor">
        <div class="container">
            <h1>Thank You!</h1>
            <p>Thank you for submitting your referrals. Feel free to contact us with any questions.</p>
            <?php if ($logo != "none"): ?>
                <a href="<?= ($logo == "csc") ? "http://www.illinoisinnovation.com/corporate-startup-challenge" : "http://freshwateradvisors.com/" ?>"><img id="logo" src="img/<?= htmlspecialchars($logo) ?>.png" /></a>
            <?php endif ?>
        </div> <!-- container -->

    </body>

</html>