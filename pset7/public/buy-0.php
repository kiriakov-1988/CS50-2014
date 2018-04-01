<?php

    // configuration
    require("../includes/config.php");

    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // выгрузка наличных денег
        $cash = query("SELECT username, cash FROM users WHERE id = ?", $_SESSION["id"]);
        
        // else render form
        render("buy_form.php", ["title" => "Buy", "cash" => $cash]);
    }

    // else if user reached page via POST (as by submitting a form via POST)
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        if (!empty($_POST["symbol"]))
        {
            $symbol = mb_strtoupper($_POST["symbol"]);
        }
        else
        {
            apologize("Введите код акции для покупки!");
        }
        
        if (!empty($_POST["quantity"]))
        {
            $quantity = $_POST["quantity"];
            
            if (!is_numeric($quantity))
            {
                apologize("Введите целое положительное число !");
            }
            
            if (!preg_match("/^\d+$/", $quantity))
            {
                apologize("Введите целое число !");
            }
            
            if ($quantity < 0)
            {
                apologize("Введите положительное число !");
            }
            
        }
        else
        {
            apologize("Введите кол-во акций для покупки!");
        }
        
        ////////////////////////////////////////////////////////////////////////
        // загрузка цены акции
        $buy_price = lookup($symbol);
        
        if ($buy_price !== false)
        {
            $name = $buy_price["name"];
            $price = $buy_price["price"];
        }
        else
        {
            apologize("Произошла ошибка при выборе акции, проверьте код акции !");
        }
        ////////////////////////////////////////////////////////////////////////
        
        // выгрузка наличных денег
        $cash = query("SELECT cash FROM users WHERE id = ?", $_SESSION["id"]);
        $own_cash = $cash[0]["cash"];
        
        // стоимость новых акций
        $cost_of_shares = $price * $quantity;
        
        
        // проверка есть ли уже в наличии такие акции
        $check_symbol = query("SELECT * FROM own_shares WHERE (id = ? AND symbol = ?)", $_SESSION["id"], $symbol);


        // попытка купить больше акций чем есть денег 
        if ($own_cash < $cost_of_shares)
        {
            apologize("Вы хотите купить {$quantity} акц. {$symbol} по {$price} каждая на общую сумму {$cost_of_shares} у.е., но у Вас всего - {$own_cash} !");
        }
        // докупка дополнительных акций
        else if (count($check_symbol) > 0)
        {
            $buy_some_share = query("START TRANSACTION");
            $buy_some_share = query("UPDATE own_shares SET shares = (shares + ?) WHERE (id = ? AND symbol = ?)", $quantity, $_SESSION["id"], $symbol);
            $buy_some_share = query("UPDATE users SET cash = (cash - ?) WHERE (id = ?)", $cost_of_shares, $_SESSION["id"]);
            $buy_some_share = query("COMMIT");
            
            if ($buy_some_share !== false)
            {
                render("bought_share.php", ["title" => "Bought", "quantity" => $quantity, "symbol" => $symbol, "name" => $name, "price" => $price]);
            }
            else
            {
                apologize("Произошла ошибка при допокупке дополнительных акций !");
            }
        }
        // покупка новых акций
        else if (count($check_symbol) == 0)
        {
            $buy_some_share = query("START TRANSACTION");
            $buy_some_share = query("INSERT INTO own_shares (id, symbol, shares) VALUES (?, ?, ?)", $_SESSION["id"], $symbol, $quantity);
            $buy_some_share = query("UPDATE users SET cash = (cash - ?) WHERE (id = ?)", $cost_of_shares, $_SESSION["id"]);
            $buy_some_share = query("COMMIT");
            
            if ($buy_some_share !== false)
            {
                render("bought_new_share.php", ["title" => "Bought", "quantity" => $quantity, "symbol" => $symbol, "name" => $name, "price" => $price]);
            }
            else
            {
                apologize("Произошла ошибка при покупке новых акций !");
            }
        }
    }
?>


