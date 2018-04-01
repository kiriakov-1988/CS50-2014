<?php

    // configuration
    require("../includes/config.php");

    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // выгрузка имеющихся акций
        $own_shares = query("SELECT symbol,shares FROM own_shares WHERE id = ?", $_SESSION["id"]);
        
        // else render form
        render("sell_all_form.php", ["title" => "Sell all", "own_shares" => $own_shares]);
    }

    // else if user reached page via POST (as by submitting a form via POST)
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        if (isset($_POST["sell_all"]))
        {
            // для рассчета общей выручки
            $total_profit = 0;
            
            // выгрузка имеющихся акций
            $own_shares = query("SELECT symbol,shares FROM own_shares WHERE id = ?", $_SESSION["id"]);
            
            date_default_timezone_set('Europe/Kiev');
            
            // счетчики
            $i = 0;
            $j = 0;
            
            foreach ($own_shares as $own_share)
            {
                $i++;
                
                $stock = lookup($own_share["symbol"]);
                if ($stock !== false)
                {
                    $now = date("Y-m-d H:i:s");
                    
                    $sell_all_share = query("START TRANSACTION");
                    $sell_all_share = query("DELETE FROM own_shares WHERE (id = ? AND symbol = ?)", $_SESSION["id"], $own_share["symbol"]);
                    $sell_all_share = query("INSERT INTO history (id, symbol, shares, price, time) VALUES (?, ?, ?, ?, ?)", $_SESSION["id"], $own_share["symbol"], -$own_share["shares"], $stock["price"], $now);
                    $sell_all_share = query("UPDATE users SET cash = (cash + (? * ?)) WHERE (id = ?)", $own_share["shares"], $stock["price"], $_SESSION["id"]);
                    $sell_all_share = query("COMMIT");
                    
                    if ($sell_all_share !== false)
                    {
                        $total_profit = $total_profit + ($stock["price"] * $own_share["shares"]);
                        $j++;
                    }
                }
            }
            
            // сравнение счетчиков
            
            if ($i == $j)
            {
                $all = "все";
            }
            else
            {
                $all = "не все";
            }
            
            // else render form
            render("selled_all.php", ["title" => "Sell all", "total_profit" => $total_profit, "all" => $all ]);

        }
    }
?>


