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
        
        <!-- https://github.com/twitter/typeahead.js/ -->
        <script src="/js/typeahead.jquery.min.js"></script>
        
        <!-- http://underscorejs.org/ -->
        <script src="/js/underscore-min.js"></script>
        
        <!-- app JavaScript -->
        <script src="/js/sheetscripts.js"></script>
        
        <!-- obtain partner id and sheet slug -->
        <script> var thispartner = <?php echo json_encode($p_id) ?>; var slug = <?php echo json_encode($slug) ?>; var logo = <?php echo json_encode($logo) ?>;</script>
        
        <?php if (isset($sheetinfo)): ?>
            <title><?= htmlspecialchars($sheetinfo['name']) ?></title>
        <?php endif ?>

    </head>
    
    <div class="device-xs visible-xs"></div>
    <div class="device-sm visible-sm"></div>
    <div class="device-md visible-md"></div>
    <div class="device-lg visible-lg"></div>
    
    <body class="bodycolor">
        <div id="refalert" class="alert" role="alert"></div>
        <div class="container-fluid mar-bottom">
            <div class="modal fade" id="myModal" tabindex="-1" role="dialog" aria-labelledby="myModalLabel">
                <div class="modal-dialog modal-lg" role="document">
                    <div class="modal-content">
                        <div class="modal-header coolcolor">
                            <button type="button" class="close" data-dismiss="modal" aria-label="Close"><span aria-hidden="true">&times;</span></button>
                            <h4 class="modal-title" id="myModalLabel">Confirm your referrals</h4>
                        </div>
                        <div id="inthemodal" class="modal-body">
                        <em>You haven't referred any startups yet!</em>
                        </div>
                        <div class="modal-footer coolcolor">
                            <button type="button" class="btn btn-link" data-dismiss="modal">Go back</button>
                            <button id="finalsubmit" type="button" class="btn btn-success">Submit</button>
                        </div>
                    </div>
                </div>
            </div>
        <div class="row">
            <div class="col-xs-12" id="shoplist">
                
                <div id="top" class="col-xs-12 col-md-9">
                    <div class="lgfield">
                        <?php if (isset($partner) && isset($sheetinfo)): ?>
                            <h1><?= htmlspecialchars($sheetinfo['name']) ?></h1>
                            <h3><?= htmlspecialchars($partner) ?> Referrals</h3>
                        <?php endif ?>
                        
                        <?php if (isset($sheetinfo)): ?>
                            <p><em><?= htmlspecialchars($sheetinfo['text']) ?></p></em>
                        <?php endif ?>
                    </div>
                </div>
                <div class="col-xs-12 col-md-3">
                    <?php if ($logo != "none"): ?>
                        <a href="<?= ($logo == "csc") ? "http://www.illinoisinnovation.com/corporate-startup-challenge" : "http://freshwateradvisors.com/" ?>" target="_blank"><img id="logo" src="img/<?= htmlspecialchars($logo) ?>.png" /></a>
                    <?php endif ?>
                </div>
                <div id="middle" class="col-xs-12">
                    <hr class="darkhr">
                        <?php if (isset($items)): ?>
                        <?php foreach ($items as $item): ?>
                            <h2><?= htmlspecialchars($item['category']) ?></h2>
                            <ul><li><?= implode('</li><li>', $item['areas']) ?></li></ul>
                            <hr class="darkhr">
                        <?php endforeach ?>
                        <?php endif ?>
                </div>
                
            </div>
            
            <div id="entrybar" class="col-xs-12">
                <div class="entryform">
                    <form id="referform" class="form-inline">
                        
                        <div class="form-group inline-space">
                        <label id="startuplabel" for="startup" class="whitetext">Company Name: </label>
                        <input type="text" class="form-control" id="startup" placeholder="StartupX" autocomplete="off">
                        </div>
                        
                        <div class="form-group inline-space">
                        <label for="name" class="whitetext">Contact: </label>
                        <input type="text" class="form-control" id="name" placeholder="Jane Doe" autocomplete="off">
                        </div>
                        
                        <div class="form-group inline-space">
                        <label for="email" class="whitetext">Email: </label>
                        <input type="email" class="form-control" id="email" placeholder="jane@startupx.com" autocomplete="off">
                        </div>
                        
                        <button id="addreferral" class="btn btn-danger"><span class="glyphicon glyphicon-plus" aria-hidden="true"></span> Add referral</button>
                    </form>
                    <div class="adminbox">
                        <button id="bigsubmit" class="btn btn-primary btn-lg" data-toggle="modal" data-target="#myModal">Review & Submit <span class="glyphicon glyphicon-chevron-right" aria-hidden="true"></span></button>
                    </div>                    
                </div> <!-- .entryform -->
                
            </div> <!-- #entrybar -->

        </div> <!-- row -->
        </div> <!-- container -->

    </body>

</html>