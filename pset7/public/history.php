<?php

    // configuration
    require("../includes/config.php");

    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // выгрузка истории
        $transactes = query("SELECT * FROM history WHERE id = ? ORDER BY time DESC", $_SESSION["id"]);
        
        // спиок уникальных акций
        $list_of_symbols = query("SELECT DISTINCT symbol FROM history WHERE id = ?", $_SESSION["id"]);
        
        // else render form
        render("history_list.php", ["title" => "History", "transactes" => $transactes, "list_of_symbols" => $list_of_symbols]);
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
            apologize("Выберите акцию для фильтра!");
        }
        
        // список уникальных акций
        $list_of_symbols = query("SELECT DISTINCT symbol FROM history WHERE id = ?", $_SESSION["id"]);
        
        // выгрузка истории по определенной акции
        $filtered_symbols = query("SELECT * FROM history WHERE (id = ? and symbol = ?)", $_SESSION["id"], $symbol);
        
        $profit = 0;
        
        $quantity_shares = 0;
        // $delta_shares = 0;
        
        $filtered = [];
        
        $prev_price = $filtered_symbols[0]["price"];
        $now_price = $filtered_symbols[0]["price"];
        
        
        foreach ($filtered_symbols as $filtered_symbol)
        {
            $profit = $profit + ($filtered_symbol["shares"] * $filtered_symbol["price"]);
            
            $quantity_shares = $quantity_shares + $filtered_symbol["shares"];
            
            $now_price = $filtered_symbol["price"];
            

            /*
            if ($delta_shares == 0)
            {
             */
                $filtered[] = [
                    "symbol" => $filtered_symbol["symbol"],
                    "shares" => $filtered_symbol["shares"],
                    "price" => $filtered_symbol["price"],
                    "time" => $filtered_symbol["time"],
                    "delta_price" => ($now_price-$prev_price),
                    "quantity_shares" => $quantity_shares
                ];
            /*
            }
            else
            {
                $filtered[] = [
                    "symbol" => $filtered_symbol["symbol"],
                    "shares" => $filtered_symbol["shares"],
                    "price" => $filtered_symbol["price"],
                    "time" => $filtered_symbol["time"],
                    "delta_price" => ($now_price-$prev_price),
                    "quantity_shares" => $quantity_shares
                ];
            }
            
            $delta_shares = $quantity_shares;
             */

            $prev_price = $now_price;

        }
        
        /* выгрузка цены акции
        $stock = lookup($symbol);
        
        if ($stock !== false)
        {
            $name = $stock["name"];
            $price = $stock["price"];
        }
        else
        {
            $name = $symbol;
            $price = "?";
        }
        */
        
        //выгрузка остатка акции
        $own_share = query("SELECT shares FROM own_shares WHERE (id = ? and symbol = ?)", $_SESSION["id"], $symbol);
        
        if (empty($own_share[0]["shares"]))
        {
            $own_share = 0;
        }
        else
        {
            $own_share = $own_share[0]["shares"];
        }
        
        // $profit = $profit - ($own_share * $price);
        
        
        // сгенерировать страничку
        render("history_filtered.php", ["title" => "Filtered history", "filtered_symbols" => $filtered, "list_of_symbols" => $list_of_symbols, 
                                            "choose_symbol" => $symbol, /*"choose_name" => $name, "choose_price" => $price,*/ "choose_share" => $own_share, "profit" => $profit ]);
    }
?>


