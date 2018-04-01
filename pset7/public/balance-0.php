<?php

    // configuration
    require("../includes/config.php");

    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // выгрузка наличных денег
        $cash = query("SELECT username, cash FROM users WHERE id = ?", $_SESSION["id"]);
        
        // else render form
        render("balance_form.php", ["title" => "Пополнить баланс", "cash" => $cash]);
    }

    // else if user reached page via POST (as by submitting a form via POST)
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        
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

			if ($quantity < 5 || $quantity > 15)
			{
				apologize("Введите число между 5 и 15 включительно !");
			}

		}
		else
		{
			$quantity = rand(5, 15);
		}
		
		date_default_timezone_set('Europe/Kiev');
        $now = date("H i s"); // текущее время
        $sec = date("s"); // текущая секунда
        
        
        $balance = $quantity * $sec * array_sum(str_split($sec));
        
        if ( ($sec % 2) == 0 ) /* четная секунда */
        {
            $balance = $balance * array_sum(str_split($now)) ;
        }
        else /* нечетная секунда */
        {
            $balance = $balance * (34 - array_sum(str_split($now)) ); /* 2 3   5 9   5 9 ==> 33 +1  */
        }
        
        $balance = $balance % 10000;
        
        $add_balance = query("START TRANSACTION");
	    $add_balance = query("UPDATE users SET cash = (cash + ?) WHERE (id = ?)", $balance, $_SESSION["id"]);
	    $add_balance = query("COMMIT");

	    if ($add_balance !== false)
	    {
		    render("balance_add.php", ["title" => "Счет пополнен", "balance" => $balance ]);
	    }
	    else
	    {
		    apologize("Произошла ошибка при пополнении счета !");
	    }

    }
?>


