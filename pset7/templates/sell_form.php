<form action="sell.php" method="post">
    <fieldset>
        <div class="form-group">
            <select class="form-control" name="symbol" id="sell_symbol" >
			    <option class="form-control" selected disabled>Выберите акции</option>	
									
				<?php foreach ($own_shares as $own_share): ?>
				    <option class="form-control" value="<?= $own_share['symbol'] ?>"><?= $own_share["symbol"] ?> (<?= $own_share["shares"] ?> шт.)</option>
                <?php endforeach ?> 
                        
		    </select>
        </div>
        <div class="form-group">
            <input class="form-control" name="quantity" autocomplete="off" placeholder="Количество" type="number" min="1" max="" id="quantity_symbol" style="width: 10em" />
        </div>
        <div class="form-group">
            <button type="submit" name="sell_some" class="btn btn-default"><span class="lead">Продать</span></button>
        </div>
        
        <br />
        <br />
        
        <div class="form-group">
            <button type="submit" name="sell_all" class="btn btn-default"><span class="text-danger">Продать все !</span></button>
        </div>
    </fieldset>
</form>
