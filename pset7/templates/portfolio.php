                <main>
                
                    <?php if (!empty($_SESSION["register_message"])): ?>
                        <div id="register_message" > 
                            <p class="lead">
                                <span style="background-color: aqua;" > &nbsp; <?= htmlspecialchars($_SESSION["register_message"]) ?> &nbsp; </span>
                            </p>
                        </div>
                    <?php endif; $_SESSION["register_message"] = "" ?>

                    <table class="table table-striped">
                        <thead>
                            <tr>
                                <th width="20%" >Symbol</th>
                                <th width="35%" >Name</th>
                                <th width="15%" >Shares</th>
                                <th width="15%" >Price</th>
                                <th >TOTAL</th>
                            </tr>
                        </thead>
                        <tfoot>
                            <tr>
                                <td colspan="4"></td>
                                <td>$ <?= number_format($total, 2, ',', ' ') ?></td>
                            </tr>
                        </tfoot>
                        <tbody>
                        
                        <?php foreach ($positions as $position): ?>
                            <tr>
                                <td><?= $position["symbol"] ?></td>
                                <td><?= $position["name"] ?></td>
                                <td><?= $position["shares"] ?></td>
                                <td><?= number_format( $position["price"], 2, ',', ' ')  ?></td>
                                <td><?= number_format(($position["shares"] * $position["price"]), 2, ',', ' ') ?></td>
                            </tr>
                        <?php endforeach ?>            

                            <tr>
                                <td colspan="4">CASH</td>
                                <td>$ <?= number_format($cash["cash"], 2, ',', ' ') ?></td>
                            </tr>
                        </tbody>
                    </table>

                </main>
