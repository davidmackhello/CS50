<h1>Sorry!</h1>
<p><?= htmlspecialchars($message) ?></p>

<?php if (isset($redirect)): ?>
    <p><a href="<?= $redirect ?>">Go back</a></p>
<?php endif ?>