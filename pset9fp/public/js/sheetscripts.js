/*global $ _ thispartner slug logo*/

/**
 * sheetscripts.js
 *
 * js scripts for front-end referral sheets
 *
 */

// Global variables for startup referrals
var startup_id;

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
    
    // configure behavior for Add Referral button click
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
            refarray.push({"startup": $("#startup").val(), "contact": $("#name").val(), "email": $("#email").val(), "startup_id": startup_id});
            
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

    // configure typeahead
    $("#startup").typeahead({
        highlight: true,
        minLength: 1
    },
    {
        source: search,
        templates: {
            suggestion: _.template("<p><%- startup %></p>")
        }
    });
    
    // if typeahead option selected
    $("#startup").on("typeahead:selected", function(eventObject, suggestion, name) {
        $('#startup').typeahead('val', suggestion.startup);
        $("#name").val(suggestion.person);
        $("#email").val(suggestion.email);
        startup_id = suggestion.id;        
    });
    
    $("#startup").on("change", function() {
        startup_id = "new";
    });

    // resize typeahead suggestion box
    $(".tt-dropdown-menu").css("max-height", "100px");
    $(".tt-dropdown-menu").css("width", "250px");
    
    
    // configure behavior for final submit action (from modal)
    $("#finalsubmit").on("click", function() {
        
        // convert array of referrals to json string
        var str_json = JSON.stringify(refarray);
        
        post("/", {json:str_json, partner_id:thispartner, slug:slug, logo:logo});
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
        
        html +=  "<td>"+val.startup+"</td>"+"<td>"+val.contact+"</td>"+"<td>"+val.email+"</td>";
        
        html += "<td><span class=\"glyphicon glyphicon-remove remref\" aria-hidden=\"true\"></span></td></tr>";
    });
    
    html += "</tbody></table></div>";

    $("#inthemodal").html(html);    
}

/**
 * Searches database for typeahead's suggestions.
 */
function search(query, cb)
{
    // get places matching query (asynchronously)
    var parameters = {
        string: query
    };
    $.getJSON("search.php", parameters)
    .done(function(data, textStatus, jqXHR) {

        // call typeahead's callback with search results (i.e., places)
        cb(data);
    })
    .fail(function(jqXHR, textStatus, errorThrown) {

        // log error to browser's console
        console.log(errorThrown.toString());
    });
}

/**
 * Send post request via js - http://stackoverflow.com/questions/133925/javascript-post-request-like-a-form-submit
 */
function post(path, params, method) {
    method = method || "post"; // Set method to post by default if not specified.

    // The rest of this code assumes you are not using a library.
    // It can be made less wordy if you use one.
    var form = document.createElement("form");
    form.setAttribute("method", method);
    form.setAttribute("action", path);

    for(var key in params) {
        if(params.hasOwnProperty(key)) {
            var hiddenField = document.createElement("input");
            hiddenField.setAttribute("type", "hidden");
            hiddenField.setAttribute("name", key);
            hiddenField.setAttribute("value", params[key]);

            form.appendChild(hiddenField);
         }
    }

    document.body.appendChild(form);
    form.submit();
}