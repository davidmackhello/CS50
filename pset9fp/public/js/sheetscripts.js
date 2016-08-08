/*global $*/

/**
 * sheetscripts.js
 *
 * js scripts for front-end referral sheets
 *
 */

// execute when the DOM is fully loaded
$(function() {

    // alter margin of container based on viewport size
    $(window).resize(function () {

        if(isBreakpoint('xs') ) {
            $('.mar-bottom').css('margin-bottom', '395px');
            $("#referform").removeClass("form-inline");
            }
            
        if(isBreakpoint('md') || isBreakpoint('lg')) {
            $('.mar-bottom').css('margin-bottom', '175px');
            $("#referform").addClass("form-inline");
            }
    });
    
    // create array for startup referrals
    var refarray = [];
    
    // configure alert behavior for Add Referral button click
    $("#addreferral").on("click", function(e) {
        
        // prevent form submit
        e.preventDefault();
        
        // check for empty fields
        if ($("#startup").val() === "" || $("#name").val() === "" || $("#email").val() === "")
        {
            var blank = true;
        }
        
        // if any fields blank or improperly formatted email
        if (blank == true || !isemail($("#email").val()))
        {
            // flash warning alert and fade out
            $("#refalert").removeClass("alert-success");
            $("#refalert").addClass("alert-warning");
            (blank) ? $("#refalert").html("<strong>Please complete all fields.<strong>") : $("#refalert").html("<strong>Invalid email address.<strong>");
            $("#refalert").fadeIn("fast");
            setTimeout(function(){ $("#refalert").fadeOut("slow"); }, 1000);
        }
        
        // fields submitted properly
        else
        {

            // add to referral array
            refarray.push({"startup": $("#startup").val(), "contact": $("#name").val(), "email": $("#email").val()});
            
            // flash success alert and fade out
            $("#refalert").removeClass("alert-warning");
            $("#refalert").addClass("alert-success");
            $("#refalert").html("<strong>"+$("#startup").val()+" referred!</strong>");
            $("#refalert").fadeIn("fast");
            setTimeout(function(){ $("#refalert").fadeOut("slow"); }, 1000);  
            
            // clear fields
            $("input").val("");
            
            // print referral table in modal
            arraytotable(refarray);
        }
    });
    
    // set click behavior for remove icons
    $(document).on('click', '.remref', function(){
        
        // remove startup referral object from array
        refarray.splice($(this).closest("tr").attr("id"), 1);
        
        // check if array empty
        if (refarray.length == 0)
        {
            $("#inthemodal").html("<em>You haven't referred any startups yet!</em>");
        }

        // else array still contains objects
        else
        {
            // re-print table
            arraytotable(refarray);
        }
    });
    
});

// detect bootstrap breakpoints - http://stackoverflow.com/a/14965892/6372580
function isBreakpoint(alias) 
{
    return $('.device-' + alias).is(':visible');
}

// validate proper email format using RegEx used by HTML5 for email validation - https://www.w3.org/TR/html5/forms.html#valid-e-mail-address
function isemail(testme)
{
    var re = /^[a-zA-Z0-9.!#$%&'*+/=?^_`{|}~-]+@[a-zA-Z0-9](?:[a-zA-Z0-9-]{0,61}[a-zA-Z0-9])?(?:\.[a-zA-Z0-9](?:[a-zA-Z0-9-]{0,61}[a-zA-Z0-9])?)*$/;
    return re.test(testme);
}

// print referral array to table in modal
function arraytotable(array)
{
    var html = "<div id=\"reftable\"><table class=\"table\"><thead><tr><th>Startup</th><th>Contact Name</th><th>Email</th><th></th></tr></thead><tbody>";

    $.each(array, function(ind, val) {
        
        html += "<tr id=\""+ind+"\">";

        $.each(val, function(k, v) {
          
          html += "<td>"+v+"</td>";

        });
        html += "<td><span class=\"glyphicon glyphicon-remove remref\" aria-hidden=\"true\"></span></td></tr>";
    });
    
    html += "</tbody></table></div>";

    $("#inthemodal").html(html);    
}