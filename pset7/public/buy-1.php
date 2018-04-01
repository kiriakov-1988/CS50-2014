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
        
        date_default_timezone_set('Europe/Kiev');
        $now = date("Y-m-d H:i:s");
        
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
        


        // попытка купить больше акций чем есть денег 
        if ($own_cash < $cost_of_shares)
        {
            $max = floor($own_cash / $price);
            
            apologize("Вы хотите купить {$quantity} акц. {$symbol} по {$price} каждая на общую сумму {$cost_of_shares} у.е., но у Вас всего - {$own_cash} ! 
                        Вы можете купить максимум {$max} шт.");
        }
        // покупка акций
        else
        {
            $buy_some_share = query("START TRANSACTION");
            
            $buy_some_share = query("INSERT INTO own_shares (id, symbol, shares) VALUES(?, ?, ?) ON DUPLICATE KEY UPDATE shares = shares + VALUES(shares)", $_SESSION["id"], $symbol, $quantity);
            
            $buy_some_share = query("INSERT INTO history (id, symbol, shares, price, time) VALUES (?, ?, ?, ?, ?)", $_SESSION["id"], $symbol, $quantity, $price, $now);
            
            $buy_some_share = query("UPDATE users SET cash = (cash - ?) WHERE (id = ?)", $cost_of_shares, $_SESSION["id"]);
            
            $buy_some_share = query("COMMIT");
            
            if ($buy_some_share !== false)
            {
                render("bought_shares.php", ["title" => "Bought", "quantity" => $quantity, "symbol" => $symbol, "name" => $name, "price" => $price]);
            }
            else
            {
                apologize("Произошла ошибка при покупке акций !");
            }
        }

    }
?>


