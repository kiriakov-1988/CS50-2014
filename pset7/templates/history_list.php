                <main>
                    <form action="history.php" method="post">
                        <fieldset>
                            <div class="form-group">
                                <select class="form-control" name="symbol">
			                        <option class="form-control" selected disabled>Выбрать акцию</option>	
									
				                    <?php foreach ($list_of_symbols as $list_of_symbol): ?>
				                        <option class="form-control" value="<?= $list_of_symbol['symbol'] ?>"><?= $list_of_symbol["symbol"] ?></option>
                                    <?php endforeach ?> 
                                            
		                        </select>
                            </div>
                            <div class="form-group">
                                <button type="submit" class="btn btn-default">Детальнее</button>
                            </div>
                        </fieldset>
                    </form>
                    
                    <table class="table table-striped">
                        <thead>
                            <tr>
                                <th width="30%" >Время</th>
                                <th width="25%" >Symbol</th>
                                <th width="20%" >Количество</th>
                                <th>Цена</th>
                            </tr>
                        </thead>

                        <tbody>
                        <?php foreach ($transactes as $transacte): ?>

                            <tr>
                                <td><?= $transacte["time"] ?></td>
                                <td><?= $transacte["symbol"] ?></td>
                                <td><?= $transacte["shares"] ?></td>
                                <td><?= number_format($transacte["price"], 4, ',', ' ')  ?></td>
                            </tr>
                        <?php endforeach ?>            

                        </tbody>
                    </table>
                </main>
