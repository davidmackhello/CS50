<table class="table table-striped">
    <thead>
        <tr>
            <th>Symbol</th>
            <th>Name</th>
            <th>Shares</th>
            <th>Price</th>
            <th>TOTAL</th>
        </tr>
    </thead>
    <tbody>
<?php if (!isset($nostocks)): ?>
<?php foreach ($positions as $position): array_map('htmlspecialchars', $position); ?>
        <tr>
            <td><?= implode('</td><td>', $position) ?></td>
        </tr>
<?php endforeach ?>
<?php endif ?>
        <tr class="info">
            <td colspan="4"><em><strong>CASH</strong></em></td>
            <td><strong><?= $cash ?></strong></td>
        </tr>
    </tbody>
</table>
<?php if (isset($nostocks)): ?>
    <p>Your portfolio is empty, but you have <strong><?= $cash ?></strong> in cash. You can buy stocks <a href="buy.php">here.</a></p>
<?php endif ?>