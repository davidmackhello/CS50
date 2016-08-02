<!DOCTYPE html>

<html>

    <head>
        <!-- jQuery -->
        <script src="https://code.jquery.com/jquery-3.1.0.min.js"   integrity="sha256-cCueBR6CsyA4/9szpPfrX3s49M9vUU5BgtiJj06wt/s="   crossorigin="anonymous"></script>

        <!-- Bootstrap Latest compiled and minified CSS -->
        <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/css/bootstrap.min.css" integrity="sha384-BVYiiSIFeK1dGmJRAkycuHAHRg32OmUcww7on3RYdg4Va+PmSTsz/K68vbdEjh4u" crossorigin="anonymous">        
        
        <!-- Bootstrap Latest compiled and minified JavaScript -->
        <script src="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/js/bootstrap.min.js" integrity="sha384-Tc5IQib027qvyjSMfHjOMaLkfuWVxZxUPnCJA7l2mCWNIpG9mGCD8wGNIcPD7Txa" crossorigin="anonymous"></script>
       
        <!-- app CSS -->
        <link href="/css/styles.css" rel="stylesheet"/>
        
        <!-- app JavaScript -->
        <script src="/js/adminscripts.js"></script>
        
        <title>Admin</title>

    </head>
    
    <body class="bodycolor">
        <div class="container-fluid ">

            <div id="top">
                <h1>Admin Page</h1>
                <p><em>This is the admin page</em></p>
            </div>
            <hr class="darkhr">
            <div id="middle">
                
                <h2><a href="build.php">Build a new sheet</a></h2>
                
                <h3>Edit your sheets</h3>
                <ul>
                <?php foreach ($sheetnames as $sheetname): ?>
                    <li><a href="edit.php?sheet=<?= htmlspecialchars($sheetname); ?>"><?= htmlspecialchars($sheetname); ?></a></li>
                <?php endforeach ?>
                </ul>
            </div>
        </div> <!-- container-fluid -->
        <div id="linkbar" class="col-xs-12">
            <div class="entryform">
                <form>
                <div class="col-xs-12 adminrow form-inline">
                    <div class="form-group">
                        <label for="sheetselect">Select Sheet: </label>
                        <select id="sheetselect">
                             <option selected disabled>Select sheet</option>
                        <?php foreach ($sheetnames as $sheetname): ?>
                            <option value="<?= htmlspecialchars($sheetname); ?>"><?= htmlspecialchars($sheetname); ?></option>
                        <?php endforeach ?>
                        </select>
                    </div>
                    <div class="form-group inline-space">
                        <label for="partnerselect">Select Partner: </label>
                        <select id="partnerselect">
                            <option selected disabled>Select partner</option>
                            <option value="Northwestern University">Northwestern University</option>
                            <option value="Catapult">Catapult</option>
                        </select>
                    </div>
                    <div class="form-group inline-space">
                        <label for="logoselect">Select Logo: </label>
                        <select id="logoselect">
                            <option selected disabled>Select logo</option>
                            <option value="csc">Corporate-Startup Challenge</option>
                            <option value="fa">Freshwater</option>
                            <option value="none">None</option>
                        </select>
                    </div>
                </div> 
                <div class="col-xs-12 adminrow">
                    <div class="input-group shortfield adminform">
                        <span class="input-group-btn">
                            <button class="btn btn-primary" type="button" id="getlink">Get Link</button>
                        </span>
                        <input type="text" class="form-control" id="linkfield">
                    </div>
                </div>    
                </form>
            </div> <!-- .entryform -->
        </div> <!-- #linkbar -->
    </body>
</html>