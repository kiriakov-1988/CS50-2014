                
                <div>
                    <?php foreach ($own_shares as $own_share): ?>
				        <p><?= $own_share["shares"] ?> шт. - <?= $own_share["symbol"] ?> </p>
                    <?php endforeach ?> 
                </div>
                <br />


<form action="sell_all.php" method="post">
    <fieldset>
        <div class="form-group">
            <button type="submit" name="sell_all" class="btn btn-default"><span class="lead">Продать все</span></button>
        </div>
    </fieldset>
</form>
