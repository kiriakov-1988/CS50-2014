query("START TRANSACTION");
query("UPDATE own_shares SET shares = shares - $quantity WHERE id = ? AND symbol = ?", $_SESSION["id"], $symbol);
query("UPDATE users SET cash = cash + $quantity * ? WHERE id = ? AND symbol = ?", $price, $_SESSION["id"], $symbol);
query("COMMIT");


$sell_some_share = query("START TRANSACTION");
            $sell_some_share = query("UPDATE own_shares SET shares = (shares - ?) WHERE (id = ? AND symbol = ?)", $quantity, $_SESSION["id"], $symbol);
            $sell_some_share = query("UPDATE users SET cash = (cash + (? * ?)) WHERE (id = ? AND symbol = ?)", $quantity, $price, $_SESSION["id"], $symbol);
            $sell_some_share = query("COMMIT");
            
            
INSERT INTO own_shares (id, symbol, shares) VALUES (9,  FB,  3);

INSERT INTO table (id, symbol, shares) VALUES(6, "FREE", 10) ON DUPLICATE KEY UPDATE shares = shares + VALUES(shares)
 
