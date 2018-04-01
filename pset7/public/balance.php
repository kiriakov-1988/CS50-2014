<?php

    // configuration
    require("../includes/config.php");

    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // выгрузка наличных денег
        $cash = query("SELECT username, cash FROM users WHERE id = ?", $_SESSION["id"]);
        
        
        // проверка наличия еще попыток на пополнение счета
        date_default_timezone_set('Europe/Kiev');
        $today = date("Y-m-d");
        
        $attempt_query = query("SELECT attempt FROM balance WHERE (user_id = ? and date = ?)", $_SESSION["id"],  $today);
        
        $count_attempt = count($attempt_query);
        
        if ($count_attempt == 0)
        {
            if (empty($_SESSION["attempt"]))
            {
                $_SESSION["attempt"] = rand(1, 3);
            }
            
            $attempt = $_SESSION["attempt"];
        }
        else if ( $count_attempt < $attempt_query[0]["attempt"] )
        {
            $attempt = $attempt_query[0]["attempt"] - $count_attempt;
        }
        else
        {
            $attempt = 0;
        }
        
        // на сколько был пополнен счет за все время / сегодня
        
        $balance_adds = query("SELECT balance, date FROM balance WHERE user_id = ?", $_SESSION["id"] );
        
        $all_balance_adds = 0;
        $today_balance_adds = 0;
        
        foreach ($balance_adds as $balance_add)
        {
            if ($balance_add["date"] == $today)
            {
                $today_balance_adds = $today_balance_adds + $balance_add["balance"];
            }
            
            $all_balance_adds = $all_balance_adds + $balance_add["balance"];
        }
        
        // else render form
        render("balance_form.php", ["title" => "Пополнить баланс", "cash" => $cash, "attempt" => $attempt, 
                                                                    "all_balance_adds" => $all_balance_adds, "today_balance_adds" => $today_balance_adds ]);
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
		
		if (!empty($_POST["attempt"]))
		{
			$attempt = $_POST["attempt"];

			if (!is_numeric($attempt) || !preg_match("/^\d+$/", $attempt) || $attempt < 0 || $attempt > 5)
			{
				apologize("Скрытое число от 0 до 5 включительно ! Не меняйте его !");
			}
		}
		else
		{
			$attempt = 0;
		}
		
		date_default_timezone_set('Europe/Kiev');
        $now = date("H i s"); // текущее время
        $sec = date("s"); // текущая секунда
        $today = date("Y-m-d");
        
        
        $balance = $quantity * $sec * array_sum(str_split($sec));
        
        if ( ($sec % 2) == 0 ) /* четная секунда */
        {
            $balance = $balance * array_sum(str_split($now)) ;
        }
        else /* нечетная секунда */
        {
            $balance = $balance * (34 - array_sum(str_split($now)) ); /* 2 3   5 9   5 9 ==> 33 +1  */
        }
        
        $balance = $balance % (10000 / rand(2, 5));
        
        $add_balance = query("START TRANSACTION");
        
        $add_balance = query("INSERT INTO balance (attempt, date, user_id, balance) VALUES (?, ?, ?, ?)", $attempt, $today, $_SESSION["id"], $balance);
        
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


