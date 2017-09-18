<!DOCTYPE html>

<html>

    <head>
        
        <!-- Latest compiled and minified CSS -->
        <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.6/css/bootstrap.min.css" integrity="sha384-1q8mTJOASx8j1Au+a5WDVnPi2lkFfwwEAa8hDDdjZlpLegxhjVME1fgjWPGmkzs7" crossorigin="anonymous">
        
        <!-- jQuery -->
        <script src="https://code.jquery.com/jquery-3.1.0.min.js"   integrity="sha256-cCueBR6CsyA4/9szpPfrX3s49M9vUU5BgtiJj06wt/s="   crossorigin="anonymous"></script>
        
        <!-- app CSS -->
        <link href="/css/styles.css" rel="stylesheet"/>
        
        <!-- app JavaScript -->
        <script src="/js/scripts.js"></script>
        
        <?php if (isset($title)): ?>
            <title><?= htmlspecialchars($title) ?></title>
        <?php else: ?>
            <title>Davetown</title>
        <?php endif ?>

    </head>
    
    <div class="device-xs visible-xs"></div>
    <div class="device-sm visible-sm"></div>
    <div class="device-md visible-md"></div>
    <div class="device-lg visible-lg"></div>
    
    <body>
        <div class="container-fluid mar-bottom">
        <div class="row">
            <div class="col-xs-12" id="shoplist">
                
                <div id="top">
                    <h1>Corporate-Startup Challenge: Northwestern University Referrals</h1>
                    <p><em>Please scan through the technology list below, and use the form at the bottom to suggest any early-stage companies in your network that might be a good fit.</em></p>
                </div>
                <hr>
                
                <div id="middle">