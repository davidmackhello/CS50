<?php require("../includes/helpers.php"); ?>

<?php render("header", ["title" => "Posting Form"]); ?>

<form action="post.php" method="post">
    <p>Enter dimension (d): <input name="param" type="text" placeholder="e.g. 4" /></p>
    <input type="submit" value="Multiply!" />
</form>

<?php render("footer"); ?>