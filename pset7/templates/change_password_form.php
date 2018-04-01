<form action="change_password.php" method="post">
    <fieldset>
        <div class="form-group">
            <input autofocus class="form-control" name="old_password" placeholder="Password" type="password"/>
        </div>
        <div class="form-group">
            <input class="form-control confirm_class" name="new_password" placeholder="New password" type="password" id="password" pattern=".{3,}" title="от 3 символов"/>
        </div>
        <div class="form-group">
            <input class="form-control confirm_class" name="confirmation" placeholder="Repeat new password" type="password" id="confirm_password"/>
        </div>
        <div class="form-group">
            <button type="submit" class="btn btn-default">Изменить пароль</button>
        </div>
    </fieldset>
</form>
