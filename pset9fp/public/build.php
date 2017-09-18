<?php

    // configuration
    require("../includes/config.php");
    
    // retrieve html for block section of admin form (generates 1 block with 1 bullet)
    $bullethtml = file_get_contents("../views/bullet.php");
    $blockhtml = file_get_contents("../views/blocktop.php").$bullethtml.file_get_contents("../views/blockbottom.php");

    // render admin form (build view)
    render("build-edit-form.php", ["blocknum" => [1], "blockhtml" => $blockhtml, "bullethtml" => $bullethtml]);
    
?>