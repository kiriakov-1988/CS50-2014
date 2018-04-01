                <main>
                    <form action="history.php" method="post">
                        <fieldset>
                            <div class="form-group">
                                <select class="form-control" name="symbol">
									
				                    <?php foreach ($list_of_symbols as $list_of_symbol): ?>
				                        <option class="form-control" <?php if ($list_of_symbol['symbol'] == $choose_symbol) : ?> <?= ("selected") ?> <?php endif ?>  value="<?= $list_of_symbol['symbol'] ?>"><?= $list_of_symbol["symbol"] ?></option>
                                    <?php endforeach ?> 
                                            
		                        </select>
                            </div>
                            <div class="form-group">
                                <button type="submit" class="btn btn-default">Обновить</button>
                            </div>
                        </fieldset>
                    </form>
                    
                    <table class="table table-striped">
                        <thead>
                            <tr>
                                <th width="30%" >Время</th>
                                <th width="25%" >Symbol</th>
                                <th width="20%" >Количество (остаток)</th>
                                <th>Цена</th>
                            </tr>
                        </thead>

                        <tbody>
                        <?php foreach ($filtered_symbols as $filtered_symbol): ?>

                            <tr>
                                <td><?= $filtered_symbol["time"] ?></td>
                                <td><?= $filtered_symbol["symbol"] ?></td>
                                <td><?= $filtered_symbol["shares"] ?> (<?= $filtered_symbol["quantity_shares"] ?>)</td>
                                <td><?= number_format($filtered_symbol["price"], 4, ',', ' ') ?> (<?php if ($filtered_symbol["delta_price"] > 0):?><?=("+") ?><?php endif ?><?= number_format($filtered_symbol["delta_price"], 4, ',', '') ?>)</td>
                            </tr>
                        <?php endforeach ?>   
                        
                            <tr>
                                <td> </td> <td> </td> <td> </td> <td> </td>
                            </tr> 


                        </tbody>
                        
                        <tfoot>
                            <tr>
                                <td> Доход / убыток </td>
                                <td> <?= $choose_symbol ?> </td>
                                <td>  (<?= $choose_share ?>) </td>
                                <td> <?= number_format($profit, 2, ',', ' ') ?> </td>
                            </tr>  
                        </tfoot>
                        
                    </table>
                </main>
