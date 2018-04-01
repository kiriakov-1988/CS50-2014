<form action="sell.php" method="post">
    <fieldset>
        <div class="form-group">
            <select class="form-control" name="symbol">
			    <option class="form-control" selected disabled>Выберите акции</option>	
									
				<?php foreach ($own_shares as $own_share): ?>
				    <option class="form-control" value="<?= $own_share['symbol'] ?>"><?= $own_share["symbol"] ?> (<?= $own_share["shares"] ?> шт.)</option>
                <?php endforeach ?> 
                        
		    </select>
        </div>
        <div class="form-group">
            <input class="form-control" name="quantity" placeholder="Количество" type="number" min="1"/>
        </div>
        <div class="form-group">
            <button type="submit" class="btn btn-default">Продать</button>
        </div>
    </fieldset>
</form>
