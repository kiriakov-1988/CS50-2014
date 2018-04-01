<p class="lead">
    <?= htmlspecialchars($cash[0]["username"]) ?>, у Вас в наличии <?= htmlspecialchars( number_format($cash[0]["cash"], 2, ',', ' ') ) ?> у.е. !           
</p>

<form action="balance.php" method="post">
    <fieldset>
        <div class="form-group">
            <input autofocus class="form-control" style="width: 15em" autocomplete="off" name="quantity" placeholder="Количество от 5 до 15" type="number" min="5" max="15" />
        </div>
        <div class="form-group">
            <button type="submit_balance" class="btn btn-default">Пополнить счет</button>
        </div>
    </fieldset>
</form>
