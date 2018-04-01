<!DOCTYPE html>

<html>

    <head>

        <link href="/css/bootstrap.min.css" rel="stylesheet"/>
        <link href="/css/bootstrap-theme.min.css" rel="stylesheet"/>
        <link href="/css/styles.css" rel="stylesheet"/>
        
        <meta charset="utf-8">

        <?php if (isset($title)): ?>
            <title>C$50 Finance: <?= htmlspecialchars($title) ?></title>
        <?php else: ?>
            <title>C$50 Finance</title>
        <?php endif ?>

        <script src="/js/jquery-1.11.1.min.js"></script>
        <script src="/js/bootstrap.min.js"></script>
        <script src="/js/scripts.js"></script>

    </head>

    <body>

        <div class="container">

            <div id="top">
                <a href="/"><img alt="C$50 Finance" src="/img/logo.gif"/></a>
            </div>

            <div id="middle">
                <?php if (!empty($_SESSION["id"])): ?>
                    
                    <div>
                        <p class="lead">
                            <a href="quote.php">Проверить цену</a> | 
                            <a href="buy.php">Купить</a> | 
                            <a href="sell.php">Продать</a> | 
                            <a href="history.php">История операций</a> | 
                            <a href="balance.php">Пополнить счет</a> | 
                            <a href="change_password.php">Поменять пароль</a>
                        </p>
                    </div>
                    
                <?php endif ?>
                



