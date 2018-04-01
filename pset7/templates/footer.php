                <br />
                <?php if (!empty($_SESSION["id"])): ?>
                    
                    <div>
                        <?php if (isset($cash["username"])) : ?>
                            <?= htmlspecialchars($cash["username"]) ?>, 
                        <?php endif ?>
                        
                        <a href="logout.php">Log Out</a>
                    </div>
                <?php endif ?>
            
            </div>

            <div id="bottom">
                Copyright &#169; John Harvard
            </div>

        </div>

    </body>

</html>
