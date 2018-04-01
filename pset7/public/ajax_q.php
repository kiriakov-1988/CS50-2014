<?php

    // configuration
    require("../includes/config.php");
    
    // проверка количества имеющейся акции
    
    if (!empty($_GET["symbol_own_share"]))
    {
        $symbol_own_share = $_GET["symbol_own_share"];
        
        // выгрузка кол-ва вкций, если есть
        $count_own_share = query("SELECT shares FROM own_shares WHERE (id = ? AND symbol = ?) ", $_SESSION["id"], $symbol_own_share );
        
        if(count($count_own_share) == 1)
        {
            $count_own_share = "У Вас в наличии - " . $count_own_share[0]["shares"] . " шт.";
        }
        else
        {
            $count_own_share = "";
        }
        
        print $count_own_share ;
        
        ///// output stock as JSON
        // header("Content-Type: application/json");
        // print(json_encode($count_own_share));
        
    }
    


?>
