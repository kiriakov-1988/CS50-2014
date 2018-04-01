<p class="lead">
    <?= htmlspecialchars($cash[0]["username"]) ?>, у Вас в наличии <?= htmlspecialchars( number_format($cash[0]["cash"], 2, ',', ' ') ) ?> у.е. !           
</p>

<form action="buy.php" method="post">
    <fieldset>
        <div class="form-group">
            <input autofocus autocomplete="off" class="form-control" name="symbol" placeholder="Symbol" type="text" list="list_symbol"/>
            
            <datalist id="list_symbol">
                <?php foreach ($list_of_symbols as $list_of_symbol): ?>
				    <option value="<?= $list_of_symbol['symbol'] ?>"> </option>
                <?php endforeach ?> 
            </datalist> 
        </div>
        <div class="form-group">
            <input class="form-control" autocomplete="off" name="quantity" placeholder="Количество" type="number" min="1"/>
        </div>
        <div class="form-group">
            <button type="submit" class="btn btn-default">Купить</button>
        </div>
    </fieldset>
</form>


<br />
<p>  <a href="https://finance.yahoo.com/lookup">Ссылка на большую часть кодов</a> </p>
