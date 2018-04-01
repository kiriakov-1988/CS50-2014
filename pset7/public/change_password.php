<?php

    // configuration
    require("../includes/config.php");

    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // else render form
        render("change_password_form.php", ["title" => "Change password"]);
    }

    // else if user reached page via POST (as by submitting a form via POST)
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        if (empty($_POST["old_password"]))
        {
            apologize("Введите действующий пароль");
        }
        else if (empty($_POST["new_password"]))
        {
            apologize("Введите новый пароль");
        }
        else if ($_POST["new_password"] != $_POST["confirmation"])
        {
            apologize("Новые пароли не совпадают !");
        }
        else
        {
            // загрузка старого пароля
            $old_pas = query("SELECT hash FROM users WHERE id = ?", $_SESSION["id"]);

            // проверка введен ли правильно старый пароль
            if (crypt($_POST["old_password"], $old_pas[0]["hash"]) == $old_pas[0]["hash"]) 
            {
                $new_pas = query("UPDATE users SET hash = ? WHERE (id = ?)", crypt($_POST["new_password"]), $_SESSION["id"]);
                
                if ($new_pas !== false)
                {
                    $_SESSION["register_message"] = "Вы поменяли свой пароль !";
                    
                    // redirect to portfolio
                    redirect("/"); 
                }
                else
                {
                    apologize("Произошла ошибка при обновлении пароля !");
                }
            }
            else
            {
                apologize("Вы ввели недействующий текущий пароль");
            }
            
        }   
    }
?>
