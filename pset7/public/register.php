<?php

    // configuration
    require("../includes/config.php");

    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // else render form
        render("register_form.php", ["title" => "Register"]);
    }

    // else if user reached page via POST (as by submitting a form via POST)
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // TODO
        if (empty($_POST["username"]))
        {
            apologize("Enter your username");
        }
        else if (empty($_POST["password"]))
        {
            apologize("Enter your password");
        }
        else if ($_POST["password"] != $_POST["confirmation"])
        {
            apologize("Your passwords are different !");
        }
        else
        {
            // проверка не зарегин ли уже такой пользователь
            $rows = query("SELECT * FROM users WHERE username = ?", $_POST["username"]);

            // if we found user, check password
            if (count($rows) >= 1)
            {
                apologize("Username \"{$_POST["username"]}\" is registed");
            }
            else
            {
                $result = query("INSERT INTO users (username, hash, cash) VALUES(?, ?, 10000.00)", $_POST["username"], crypt($_POST["password"]));
                
                if ($result !== false)
                {
                    $rows = query("SELECT LAST_INSERT_ID() AS id");
                    $id = $rows[0]["id"];
                    
                    // если успешно зарегеистирован, залогиниваем 
                    $_SESSION["id"] = $id;
                    
                    $_SESSION["register_message"] = "Вы успешно зарегистрированы !";

                    // redirect to portfolio
                    redirect("/");  
                }
                else
                {
                    apologize("Trere is some error in database !");
                }
            }
        }   
    }
?>
