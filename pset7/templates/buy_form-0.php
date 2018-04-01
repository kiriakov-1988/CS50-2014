<p class="lead">
    <?= htmlspecialchars($cash[0]["username"]) ?>, у Вас в наличии <?= htmlspecialchars( number_format($cash[0]["cash"], 2, ',', ' ') ) ?> у.е. !           
</p>

<form action="buy.php" method="post">
    <fieldset>
        <div class="form-group">
            <input autofocus class="form-control" name="symbol" placeholder="Symbol" type="text"/>
        </div>
        <div class="form-group">
            <input class="form-control" autocomplete="off" name="quantity" placeholder="Количество" type="number" min="1"/>
        </div>
        <div class="form-group">
            <button type="submit" class="btn btn-default">Купить</button>
        </div>
    </fieldset>
</form>
