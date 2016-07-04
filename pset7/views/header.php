<!DOCTYPE html>

<html>

    <head>

        <!-- http://getbootstrap.com/ -->
        <link href="/css/bootstrap.min.css" rel="stylesheet"/>

        <link href="/css/styles.css" rel="stylesheet"/>

        <?php if (isset($title)): ?>
            <title>C$50 Finance: <?= htmlspecialchars($title) ?></title>
        <?php else: ?>
            <title>C$50 Finance</title>
        <?php endif ?>

        <!-- https://jquery.com/ -->
        <script src="/js/jquery-1.11.3.min.js"></script>

        <!-- http://getbootstrap.com/ -->
        <script src="/js/bootstrap.min.js"></script>

        <script src="/js/scripts.js"></script>

    </head>
    <body>
        <div class="rightnav">
              <?php if (!empty($_SESSION["id"])): ?>
                    <?php if (!empty($_SESSION["username"])): ?>
                        Greetings, <strong><?= htmlspecialchars($_SESSION["username"]) ?>!</strong>
                    <?php endif ?>
              <ul class="list-inline">
                <li><a href="password.php">Change Password</a></li>
                <li><a href="logout.php"><strong>Log Out</strong></a></li>
              </ul>
              <?php endif ?>
        </div>
        <div class="container">
            <div id="top">
                <div>
                    <a href="/"><img alt="C$50 Finance" src="/img/logo.png"/></a>
                </div>
                <?php if (!empty($_SESSION["id"])): ?>
                    <ul class="nav nav-pills">
                        <li><a href="quote.php">Quote</a></li>
                        <li><a href="buy.php">Buy</a></li>
                        <li><a href="sell.php">Sell</a></li>
                        <li><a href="history.php">History</a></li>
                        <li><a href="deposit.php">Deposit</a></li>
                    </ul>
                <?php endif ?>
                <?php if (isset($greeting)): ?>
                    <div class="greet">
                        <h3><?= htmlspecialchars($greeting) ?></h3>
                    </div>
                <?php endif ?>
            </div>
            <div id="middle">