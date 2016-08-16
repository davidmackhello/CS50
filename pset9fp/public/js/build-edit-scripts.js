/*global $ sheetinfo slug items blockHTML bulletHTML*/

/**
 * build-edit-scripts.js
 *
 * js scripts for build and edit pages
 *
 * 
 */

// execute when the DOM is fully loaded
$(function() {
    
    $('#myform').areYouSure();

    // in edit mode, this step (retrieving list of json names) will be skipped because 'items' will be defined
    if (typeof items == 'undefined')
    {
        // create empty array for existing slugs
        var slugs = [];
        
        // initiate ajax request to get dir listing of existing sheets
        $.ajax({

            url: "json-io.php",
         
            data: {
                purpose: "sheetlist"
            },

            type: "POST",

            dataType : "json"
        })

        // if successful
        .done(function(dirjson) {
                slugs = dirjson;
              })

        // if failure
        .fail(function( xhr, status, errorThrown ) {
                alert( "Server Error" );
                console.log( "Error: " + errorThrown );
                console.log( "Status: " + status );
                console.dir( xhr );
        });         

        // give focus to title field
        $("#title").focus();
    }

    // in edit mode, this step (custom formatting) will be executed because 'items' will be defined
    if (typeof items !== 'undefined')
    {
        //show edit button at bottom of form
        $("#deletesheet").show();
        
        // populate sheet title
        $("#title").val(sheetinfo.name);

        // populate url slug
        $("#slug").val(slug);

        // populate description
        $("#description").val(sheetinfo.text);

        // access each html block element
        $("div.block").each(function(){

            // retrieve first chunk of block data
            var thischunk = items.shift();

            // insert block category value into block element's category field
            $(this).find("input.catfield").val(thischunk.category);

            // access each bullet element of block
            $(this).find("input.bulletfield").each(function(){

                $(this).val(thischunk.areas.shift());

            });
        });
        
        // set all fields to saved status
        $("button.savedit").html('<span class="glyphicon glyphicon-pencil" aria-hidden="true"></span>');
        $("button.savedit").parent().siblings("input").prop('readonly', true);
        $("button.savedit").closest("div.form-group").addClass("has-success");
    }
    
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
                $(this).closest("div.form-group").removeClass("has-error");
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
        
        // mark form as dirty
        $('#myform').addClass('dirty');
    });

    // add new block when main 'add category' button clicked
    $("#addblock").on("click", function(){

        // append html in #addblockshere div
        $('#addblockshere').append(blockHTML);

        // set parameters of new block (hide initially for animation)
        $("#addblockshere").find(".block:last").addClass('hidefirst');

        // animate appearance of new block
        $("#addblockshere").find(".block:last").slideDown("fast");

        // give focus to new category field
        $(".block").find("input.catfield").focus();

        // mark form as dirty if block added
        $('#myform').addClass('dirty');

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
        
        // mark form as dirty if bullet removed
        $('#myform').addClass('dirty');
    });

    // add new bullet to given block section upon button click
    $(document).on('click', '.addbullet', function(){

        // grab selector for this'addbullet' section
        var newdiv = $(this).closest('div.col-xs-3').siblings('div.col-xs-12').find('div.addbulletshere');

        // append html in given .addbulletshere div
        $(newdiv).append(bulletHTML);

        // set parameters of new bullet (hide initially for animation)
        $(newdiv).find(".bullet:last").addClass('hidefirst');

        // animate appearance of new bullet
        $(newdiv).find(".bullet:last").slideDown("fast");

        // give focus to new bullet field
        $(newdiv).find(".bullet:last").find("input.bulletfield").focus();
        
        // mark form as dirty if bullet added
        $('#myform').addClass('dirty');
    });

    // ensure all fields entered and saved
    $("#mysubmit").on("click", function(e){

        // prevent form submit
        e.preventDefault();

        // create bool to validate form
        var bad;

        // verify each input contains data and is saved, else highlight first incomplete field
        $(":text").each(function() {
            if($(this).val() === "" || $(this).prop('readonly') === false)
            {
                var formgroup = $(this).closest("div.form-group");
                $(formgroup).addClass("has-error");
                setTimeout(function(){ $(formgroup).removeClass("has-error"); }, 500);
                $(this).focus();
                bad = true;
                return false;
            }
        });

        if (bad !== true)
        {
            // test slug for invalid characters
            if (isalphanum($("#slug").val()) !== true)
            {
                    // update slug field and warn user
                    slugwarn("URL slug contains invalid characters.");
                    bad = true;
                    return false;            
            }

            // 'items' will only be defined when in edit mode, where this rule will be skipped (allowing sheet .json file to be overwritten)
            if (typeof items == 'undefined')
            {
                // verify slug not already taken
                for (var i = 0; i < slugs.length; i++)
                {
                    if ($("#slug").val().toLowerCase() == slugs[i])
                    {
                        // update slug field and warn user
                        slugwarn("That URL slug is already taken! Please choose another.");
                        bad = true;
                        return false;
                    }
                }                
            }
        }

        // if all fields completed
        if (bad !== true)
        {
            // create array for JSON objects
            var blob = [];

            // collect first descriptive JSON object and add to blob
            var first = {
                name: $("#title").val(),
                text: $("#description").val()
            };

            blob.push(first);

            // access each block element in DOM
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

            // initiate ajax request to send all sheet data
            $.ajax({

                url: "json-io.php",

                data: {
                    purpose: "write",
                    slug: $("#slug").val().toLowerCase(),
                    blob: blob
                },

                type: "POST",

                dataType : "html"
            })

            // if successful
            .done(function() {
                    $('form').areYouSure( {'silent':true} );
                    window.location.replace("/admin.php");
                  })

            // if failure
            .fail(function( xhr, status, errorThrown ) {
                    alert( "Server Error" );
                    console.log( "Error: " + errorThrown );
                    console.log( "Status: " + status );
                    console.dir( xhr );
            });
        }
    });
    
    // set behavior for delete sheet button, first warning user
    $("#deletesheet").on("click", function(e){
    
        // prevent form submit
        e.preventDefault();
        
        // confirm delete action with warning alert
        var warn = confirm("Are you sure you want to delete this sheet? This cannot be undone.");
        
        // if user confirms
        if (warn == true) 
        {

            // initiate ajax request delete sheet from server
            $.ajax({

                url: "json-io.php",

                data: {
                    purpose: "delete",
                    slug: slug
                },

                type: "POST",

                dataType : "html"
            })

            // if successful
            .done(function() {
                    $('form').areYouSure( {'silent':true} );
                    console.log("it's been deleted");
                    window.location.replace("/admin.php");
                  })

            // if failure
            .fail(function( xhr, status, errorThrown ) {
                    alert( "Server Error" );
                    console.log( "Error: " + errorThrown );
                    console.log( "Status: " + status );
                    console.dir( xhr );
            });
                
        }
    });
    
});

/**
 * http://stackoverflow.com/questions/388996/regex-for-javascript-to-allow-only-alphanumeric/389022#389022
 */
function isalphanum(str) {

    // use regex to validate input. Alphanumeric characters allowed, plus "-" and "_"
    return /^[a-z0-9_-]+$/i.test(str);
}

/**
 * trigger warning behavior when slug field is invalid
 */
function slugwarn(message) {

    // flip to edit mode
    $("#slugbutton").html('Save');
    $("#slugbutton").closest("div.form-group").removeClass("has-success");
    $("#slugbutton").parent().siblings("input").prop('readonly', false);

    // flash error warning and focus on slug field
    $("#slug").closest("div.form-group").addClass("has-error");
    setTimeout(function(){ $("#slug").closest("div.form-group").removeClass("has-error"); }, 500);
    $("#slug").focus();

    // alert user
    alert(message);
}