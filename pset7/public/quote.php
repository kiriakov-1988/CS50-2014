<?php

    // configuration
    require("../includes/config.php");

    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // else render form
        render("quote_form.php", ["title" => "Quote"]);
    }

    // else if user reached page via POST (as by submitting a form via POST)
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // TODO
        $stock = lookup($_POST["symbol"]);
        
        if ($stock !== false)
        {
            // dump($stock);
            
            $symbol = $stock["symbol"];
            $name = $stock["name"];
            
            // $price = $stock["price"];
            $price = number_format($stock["price"], 2, ',', ' ');
            
            render("quote_stock.php", ["title" => "Quoted", "name" => $name, "symbol" => $symbol, "price" => $price]);
        }
        else
        {
            apologize("Mistake: not found \"{$_POST["symbol"]}\" !");
        }
        
    }
?>
