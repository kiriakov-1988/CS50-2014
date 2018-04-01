<?php

    // configuration
    require("../includes/config.php"); 

    // запрос на наличку у пользователя
    $cash = query("SELECT * FROM users WHERE id = ?", $_SESSION["id"]);
    $cash = $cash[0]; 
      
    // для рассчета общей суммы
    $total = $cash["cash"];
    
    $rows = query("SELECT symbol,shares FROM own_shares WHERE id = ?", $_SESSION["id"]);
    
    $positions = [];
    foreach ($rows as $row)
    {
        $stock = lookup($row["symbol"]);
        if ($stock !== false)
        {
            $positions[] = [
                "name" => $stock["name"],
                "price" => $stock["price"],
                "shares" => $row["shares"],
                "symbol" => $row["symbol"]
            ];
            
            $total = $total + ($stock["price"] * $row["shares"]);
        }
    }

    // render portfolio
    render("portfolio.php", ["positions" => $positions, "cash" => $cash, "total" => $total, "title" => "Portfolio"]);

?>
