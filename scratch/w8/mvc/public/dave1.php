<?php require("../includes/helpers.php"); ?>

<?php render("header", ["title" => "Dave1"]); ?>

<ul>
    <li>My first bullet</li>
    <li>My second bullet</li>
</ul>

        <div id="d1" class="indent">
            hello
            
            <div class="indent">
                there
            </div>
        </div>
             
        <div id="d2">
            darkness
        </div>
        <div id="d3">
            my
        </div>
        <div id="d4">
            old
        </div>
        <div id="d5">
            friend
        </div>

<?php render("footer"); ?>