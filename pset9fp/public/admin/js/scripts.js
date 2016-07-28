/*global $*/

/**
 * scripts.js
 *
 * js scripts for admin page
 *
 * 
 */

// execute when the DOM is fully loaded
$(function() {
    
    // grab block and bullet HTML
    var blockHTML = $("div.block").html();
    var bulletHTML = $("div.bullet").html();
    
    // give focus to title field
    $("#title").focus();
    
    // set click behavior for save/edit buttons and corresponding fields
    $(document).on('click', '.savedit', function(){
    
        // flip save/edit display and readonly property
        if ($(this).html() == 'Save')
        {
            if ($(this).parent().siblings("input").val() === "")
            {
                var formgroup = $(this).closest("div.form-group");
                $(formgroup).removeClass("has-success");
                $(formgroup).addClass("has-error");
                setTimeout(function(){ $(formgroup).removeClass("has-error"); }, 500);

            }
            
            else 
            {
                $(this).html('<span class="glyphicon glyphicon-pencil" aria-hidden="true"></span>');
                $(this).parent().siblings("input").prop('readonly', true);
                $(this).closest("div.form-group").addClass("has-success");
            }
        }
        
        else
        {
            $(this).html('Save');
            $(this).closest("div.form-group").removeClass("has-success");
            $(this).parent().siblings("input").prop('readonly', false);
        }
        
        $(this).blur();

    });
    
    // add new block when main 'add category' button clicked
    $("#addblock").on("click", function(){
    
        // add div to DOM
        var newdiv = document.createElement('div');
        
        // set parameters of new block (including class to hide it initially for animation)
        $(newdiv).addClass('block container-fluid blockmargin hidefirst');
        newdiv.innerHTML = blockHTML;

        // append html in #addblockshere div
        $('#addblockshere').append(newdiv);
        
        // animate appearance of new block
        $("#addblockshere").find(".block:last").slideDown("fast");
            
        // give focus to new category field
        $(newdiv).find("input.catfield").focus();

    });
    
    // set click behavior for remove buttons
    $(document).on('click', '.remove', function(){
    
        // remove blocks
        if ($(this).hasClass("byeblock") == true)
        {
            $(this).closest("div.block").slideUp("fast", function() { $(this).remove(); } );
            //$(this).closest("div.block").remove();
        }
        
        else if ($(this).hasClass("byebullet") == true)
        {
            $(this).closest("div.bullet").slideUp("fast", function() { $(this).remove(); } );
            //$(this).closest("div.bullet").remove();
        }
    });    
    
    // add new bullet to given block section upon button click
    $(document).on('click', '.addbullet', function(){
    
        // add div to DOM
        var newdiv = document.createElement('div');
        
        // set parameters of new bullet
        $(newdiv).addClass('bullet hidefirst');
        newdiv.innerHTML = bulletHTML;
        
        // append html in given .addbulletshere div
        $(this).closest('div.col-xs-3').siblings('div.col-xs-12').find('div.addbulletshere').append(newdiv);
        
        // animate appearance of new bullet
        $(this).closest('div.col-xs-3').siblings('div.col-xs-12').find('div.addbulletshere').find(".bullet:last").slideDown("fast");

        // give focus to new bullet field
        $(newdiv).find("input.bulletfield").focus();

    });
    
    // ensure all fields entered and saved
    $("#mysubmit").on("click", function(e){

        e.preventDefault();

        var empty;
        
        $(":text").each(function() {
            if($(this).val() === "" || $(this).prop('readonly') === false)
            {
                var formgroup = $(this).closest("div.form-group");
                $(formgroup).addClass("has-error");
                setTimeout(function(){ $(formgroup).removeClass("has-error"); }, 500);
                $(this).focus();
                empty = true;
                return false;
            }
        });
        
        if (empty != true)
        {
            // create array for JSON objects
            var blob = [];
            
            // collect first descriptive JSON object and add to blob
            var first = {
                name: $("#title").val(),
                text: $("#description").val()
            };
            
            blob.push(first);
            
            // access each block element
            $("div.block").each(function(){
                
                // store value of current category in this block
                var acategory = $(this).find("input.catfield").val();
                
                // create an empty array to store bullets for this block
                var abulletarray = [];
                
                // access each bullet element
                $(this).find("input.bulletfield").each(function(){
                    
                    // add each bullet value to bullet array
                    abulletarray.push($(this).val());
                    
                });
                
                // add category and bulletarray to object
                var blockobj = {
                    category: acategory,
                    areas: abulletarray
                };
                
                // add object to blob
                blob.push(blockobj);
            });
            

            $.ajax({
     
                url: "../formbuild.php",
             
                data: {
                    slug: $("#slug").val(),
                    blob: blob
                },
             
                type: "POST",
             
                dataType : "html"
            })
            // Code to run if the request succeeds (is done);
            // The response is passed to the function
            .done(function(html) {
                    $("#top").append(html);
                  })
            // Code to run if the request fails; the raw request and
            // status codes are passed to the function
            .fail(function( xhr, status, errorThrown ) {
                    alert( "Sorry, there was a problem!" );
                    console.log( "Error: " + errorThrown );
                    console.log( "Status: " + status );
                    console.dir( xhr );
            });         
        }
    });
});







  
  
  
        //var str = JSON.stringify(blob, null, 4); // (Optional) beautiful indented output.
        //console.log(str); // Logs output to dev tools console.