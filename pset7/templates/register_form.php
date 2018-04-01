<form action="register.php" method="post" id="register_form" >
    <fieldset>
    
        <div class="form-group">
            <input class="form-control" name="username" placeholder="Username" type="text" required autofocus pattern=".{3,}" title="от 3 символов" />
        </div>
        
        <div class="form-group">
            <input class="form-control confirm_class" name="password" placeholder="Password" type="password" required id="password" pattern=".{3,}" title="от 3 символов" />
        </div>
        
        <div class="form-group">
            <input class="form-control confirm_class" name="confirmation" placeholder="Repeat password" type="password"  id="confirm_password" />
        </div>
        
        <div class="form-group">
            <button class="btn btn-default" type="submit" >Register</button>
        </div>
        
    </fieldset>
</form>
<div>
    or <a href="login.php">log in</a>
</div>
