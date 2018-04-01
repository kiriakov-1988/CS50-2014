<?php

    // configuration
    require("../includes/config.php");

    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // выгрузка имеющихся акций
        $own_shares = query("SELECT symbol,shares FROM own_shares WHERE id = ?", $_SESSION["id"]);
        
        // else render form
        render("sell_form.php", ["title" => "Sell", "own_shares" => $own_shares]);
    }

    // else if user reached page via POST (as by submitting a form via POST)
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        if (!empty($_POST["symbol"]))
        {
            $symbol = $_POST["symbol"];
        }
        else
        {
            apologize("Выберите акцию для продажи!");
        }
        
        
        if (!empty($_POST["quantity"]))
        {
            $quantity = $_POST["quantity"];
            
            if (!is_numeric($quantity))
            {
                apologize("Введите число !");
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
            apologize("Введите кол-во акций для продажи!");
        }
        
        // загрузка кол-ва акций
        $share_for_sell = query("SELECT shares FROM own_shares WHERE id = ? AND symbol = ?", $_SESSION["id"], $symbol);
        $share_for_sell = $share_for_sell[0]["shares"];
        
        ////////////////////////////////////////////////////////////////////////
        // загрузка цены акции
        $stock_price = lookup($symbol);
        $now = date("Y-m-d H:i:s");
        
        if ($stock_price !== false)
        {
            $name = $stock_price["name"];
            $price = $stock_price["price"];
        }
        else
        {
            apologize("Произошла ошибка при подгрузке цены акции !");
        }
        ////////////////////////////////////////////////////////////////////////
        // попытка продать больше акци чем есть  
        if ($share_for_sell < $quantity)
        {
            apologize("Вы хотите продать {$quantity} акц. {$symbol}, но у Вас их всего - {$share_for_sell} !");
        }
        // продажа части акций
        else if ($share_for_sell > $quantity)
        {
            $sell_some_share = query("START TRANSACTION");
            $sell_some_share = query("UPDATE own_shares SET shares = (shares - ?) WHERE (id = ? AND symbol = ?)", $quantity, $_SESSION["id"], $symbol);
            $sell_some_share = query("INSERT INTO history (id, symbol, shares, price, time) VALUES (?, ?, ?, ?, ?)", $_SESSION["id"], $symbol, -$quantity, $price, $now);
            $sell_some_share = query("UPDATE users SET cash = (cash + (? * ?)) WHERE (id = ?)", $quantity, $price, $_SESSION["id"]);
            $sell_some_share = query("COMMIT");
            
            if ($sell_some_share !== false)
            {
                render("selled_share.php", ["title" => "Selled", "quantity" => $quantity, "symbol" => $symbol, "name" => $name, "price" => $price]);
            }
            else
            {
                apologize("Произошла ошибка при продаже части акций !");
            }
        }
        // продажа всех акций
        else if ($share_for_sell = $quantity)
        {
            $sell_all_share = query("START TRANSACTION");
            $sell_all_share = query("DELETE FROM own_shares WHERE (id = ? AND symbol = ?)", $_SESSION["id"], $symbol);
            $sell_all_share = query("INSERT INTO history (id, symbol, shares, price, time) VALUES (?, ?, ?, ?, ?)", $_SESSION["id"], $symbol, -$quantity, $price, $now);
            $sell_all_share = query("UPDATE users SET cash = (cash + (? * ?)) WHERE (id = ?)", $quantity, $price, $_SESSION["id"]);
            $sell_all_share = query("COMMIT");
            
            if ($sell_all_share !== false)
            {
                render("selled_shares.php", ["title" => "Selled all", "quantity" => $quantity, "symbol" => $symbol, "name" => $name, "price" => $price]);
            }
            else
            {
                apologize("Произошла ошибка при продаже всех акций !");
            }
        }
    }
?>


