/**
 * scripts.js
 *
 * Computer Science 50
 * Problem Set 7
 *
 * Global JavaScript, if any.
 */
 
 
 /* спрятать и затем удалить*/
 setTimeout(function(){$('#register_message').fadeOut('slow')},10000);  //5000 = 5 секунд
 setTimeout(function(){$('#register_message').remove()},18000);
 

 
$(document).ready(function() {

    /* проверка регистрационной формы */
	$('.confirm_class').keyup(function() {
      var pass1 = $("#password").val();
      var pass2 = $("#confirm_password").val();
	  
	  if ( pass1.length != 0 && pass2.length != 0 )
	  {
          if ( pass1 != pass2 ) {
		    $("#confirm_password").css('border', 'red 2px solid');
		    $("#confirm_password").css('background', '#fff none');
          }
          else {
            $("#confirm_password").css('background', 'url(../img/ok.png) 98% center no-repeat');
            $("#confirm_password").css('border', '#ccc 1px solid');
          }
      }
      else
      {
          $("#confirm_password").css('background', '#fff none');
          $("#confirm_password").css('border', '#ccc 1px solid');
      }
      
	});
	
	$('#password').keyup(function() {
	    $("#confirm_password").val('');
	    $("#confirm_password").css('background', '#fff none');
        $("#confirm_password").css('border', '#ccc 1px solid');
	});
	//////// 
	
	/* проверка количества имеющихся акций при проверке цены */    
	$('#symbol-control').change(symbol_own_share);
    $('#symbol-control').keyup(symbol_own_share);
                
                
    function symbol_own_share() {
        $.ajax({
            type: "GET",
            url: "ajax_q.php",
            data: "symbol_own_share="+$("#symbol-control").val(),
            success: function(html){
                $("#count_shares").html(html);
            }
        });
        
        return false;
                    
                    /*                     var url = 'ajax_q.php?symbol_own_share=' + $('#symbol-control').val();
                    $.getJSON(url, function(data) {
                        $('#count_shares').html(data.val());
                    });
                    $('#count_shares').html('a');            */
    };
    //////// 
    
    
    /* проверка количества (max) имеющихся акций при их продаже */  
    
    $('#sell_symbol').change(function(){
        $.ajax({
            type: "GET",
            url: "sell.php",
            data: "sell_symbol="+$("#sell_symbol").val(),
            success: function(html){
                $("#quantity_symbol").attr('max', html);
            }
        });
        
        return false;

        
        /* var max_share = $('#sell_symbol').val();
            alert(max_share);
            var i = max_share.search(/\s/)
            max_share = max_share.substr(i);
            i = max_share.search(/\s/)
            max_share = max_share.substr(0, i); */

    });
     
     
     
     
     
                
	
});   // --- ready ////////////////////////////////////////////////////////////////

       

       
                                        
 
 
