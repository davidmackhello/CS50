<table class="table table-striped">
    <thead>
        <tr>
            <th>Transaction</th>
            <th>Date/Time</th>
            <th>Symbol</th>
            <th>Shares</th>
            <th>Price</th>
        </tr>
    </thead>
    <tbody>
    <?php if (!isset($nohist)): ?>
    <?php foreach ($transactions as $transaction): array_map('htmlspecialchars', $transaction); ?>
        <tr>
            <td><?= implode('</td><td>', $transaction) ?></td>
        </tr>
    <?php endforeach ?>
    <?php endif ?>
    </tbody>
</table>
    <?php if (isset($nohist)): ?>
        <p>You have no previous transactions.</p>
    <?php endif ?>