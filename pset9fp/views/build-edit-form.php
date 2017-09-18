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
        
        <!-- Are-You-Sure dirty form checker -->
        <script src="/js/are-you-sure.js"></script>
        
        <!-- app JavaScript -->
        <script src="/js/build-edit-scripts.js"></script>
        
        <!-- obtain sheet data for edit mode -->
        <?php if (isset($items)): ?>
            <script type="text/javascript">
                var items = <?php echo json_encode($items) ?>; 
                var sheetinfo = <?php echo json_encode($sheetinfo) ?>;
                var slug = <?php echo json_encode($slug) ?>;
            </script>
        <?php endif ?>
        
        <!-- obtain single block and bullet elements for js -->
        <script> var blockHTML = <?php echo json_encode($blockhtml) ?>; var bulletHTML = <?php echo json_encode($bullethtml) ?>;</script>
        
        <title><?= (isset($sheetinfo)) ? "Edit: ".htmlspecialchars($sheetinfo['name']) : "Shopping List Generator"; ?></title>
        
    </head>
    <body>
        <div class="container-fluid">
            <div id="top">
                <h1><?= (isset($sheetinfo)) ? "You are editing: ".htmlspecialchars($sheetinfo['name']) : "Startup Referral Form Builder"; ?></h1>
                    <p><em>Use this tool to generate a startup shopping list/referral form that you can customize for a referral partner. Please complete and save all fields before submitting.</em></p>
            </div>
            <hr class="darkhr">
            <div id="middle">
                <div class="adminform">
                    <form id="myform">
                        <div id="infofields">
                            <div class="form-group shortfield">
                                <label class="control-label" for="title">Sheet Title</label>
                                <div class="input-group">
                                    <input type="text" class="form-control" id="title" placeholder="Enter sheet title" autocomplete="off">
                                    <span class="input-group-btn">
                                        <button class="btn btn-link savedit" type="button">Save</button>
                                    </span>
                                </div>
                                <small class="text-muted control-label">e.g. "USG Corporation" or "CSC Class 3"</small>
                            </div>
                            <div class="form-group shortfield">
                                <label class="control-label" for="slug">URL Slug</label>
                                <div class="input-group">
                                    <input type="text" class="form-control" id="slug" placeholder="slug" autocomplete="off">
                                    <span class="input-group-btn">
                                        <button class="btn btn-link savedit" id="slugbutton" type="button">Save</button>
                                    </span>
                                </div>
                                <small class="text-muted control-label">For admin use only - should be unique and contain no spaces, e.g. "usg" or "class-4"</small>
                            </div>
                            <div class="form-group">
                                <label for="description">Sheet Description</label>
                                <textarea class="form-control" id="description" rows="3" placeholder="Enter instructions for your referral partners here">Please scroll through the technology areas listed below, and submit any companies that you think might be a good fit using the 'Add Referral' fields. When you are done adding companies, click 'Review & Submit.' You only need to refer a startup once, even if it fits multiple categories. If you have any questions, contact David Machajewski at dmachajewski@istcoalition.org.</textarea>
                                <small class="text-muted control-label">These are the instructions your referral partner will see.</small>
                            </div>
                        </div> <!-- #infofields -->
                        <hr>
                        <div id="addblockcontrol">
                        <h2>
                            <button id="addblock" type="button" class="btn btn-default" aria-label="plus">
                                <span class="glyphicon glyphicon-plus" aria-hidden="true"></span>
                            </button> Add category
                        </h2>
                        </div> <!-- #addblockcontrol -->
                        <div id="addblockshere">
                        <?php foreach ($blocknum as $block)
                            {
                                require("../views/blocktop.php");
                                for ($i = 0; $i < $block; $i++)
                                {
                                    require("../views/bullet.php");
                                }
                                require("../views/blockbottom.php");
                            }
                        ?>
                        </div> <!-- #addblockshere -->
                    <button type="submit" id="mysubmit" class="btn btn-primary">Submit</button>
                    <button id="deletesheet" class="btn btn-danger">Delete Sheet</button>
                    </form>
                </div> <!-- #adminform -->
            </div> <!-- #middle -->
        </div> <!-- .container-fluid -->
    </body>
</html>