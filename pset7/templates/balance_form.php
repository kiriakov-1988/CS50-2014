<p class="lead">
    <?= htmlspecialchars($cash[0]["username"]) ?>, у Вас в наличии <?= htmlspecialchars( number_format($cash[0]["cash"], 2, ',', ' ') ) ?> у.е. ! <br />         
</p>

<?php if ($attempt > 0): ?>

    <p>
        Вы можете пополнить счет сегодня еще <?= htmlspecialchars($attempt) ?> раз(а).           
    </p>

    <form action="balance.php" method="post">
        <fieldset>
            <div class="form-group">
                <input autofocus class="form-control" style="width: 15em" autocomplete="off" name="quantity" placeholder="Любое число от 5 до 15" type="number" min="5" max="15" />
            </div>
            
            <input type="hidden" name="attempt" value="<?= htmlspecialchars($attempt) ?>">
            
            <div class="form-group">
                <button type="submit_balance" class="btn btn-default" >Пополнить счет</button>
            </div>
        </fieldset>
    </form>
<?php else: ?>

    <form >
        <fieldset>
            <div class="form-group">
                <input class="form-control " style="width: 24em; background-color: bisque " autocomplete="off" name="quantity" placeholder="Вы больше не можете пополнять счет сегодня" type="text" />
            </div>
            <div class="form-group">
                <button type="submit_balance" class="btn btn-default" disabled>Пополнить счет</button>
            </div>
        </fieldset>
    </form>
    
 
<?php endif ?>

    <p>
        За все време было пополнение на <?= htmlspecialchars( number_format( $all_balance_adds, 0, ',', ' ') ) ?> у.е., 
                                                               в т.ч. сегодня - на <?= htmlspecialchars(number_format( $today_balance_adds, 0, ',', ' ')) ?> у.е.           
    </p>


