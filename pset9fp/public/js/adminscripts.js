/*global $ _ partners */

/**
 * adminscripts.js
 *
 * js scripts for admin landing page
 * 
 */

// execute when the DOM is fully loaded
$(function() {

    // alter margin of container based on viewport size
    $(window).resize(function () {

        if(isBreakpoint('xs') ) {
            $('.mar-bottom').css('margin-bottom', '395px');
            }
            
        if(isBreakpoint('md') || isBreakpoint('lg')) {
            $('.mar-bottom').css('margin-bottom', '175px');
            }
    });
    
    // generate front-end links for referral sheets
    $("#getlink").on("click", function(){

        if ($("#sheetselect").val() != null && $("#partnerselect").val() != null && $("#logoselect").val() != null)
        {
            var url = encodeURI('http://'+document.location.host+'?sheet='+$("#sheetselect").val()+'&p_id='+$("#partnerselect").val()+'&logo='+$("#logoselect").val());
            $("#linkfield").val(url);
            $("#linkfield").select();            
        }
    });
    
    // set hover styles for list items
    $(".list-group-item").hover(function() {
            $( this ).addClass("active");
            }, function() {
            $( this ).removeClass("active");
            }
    );
    
    // upon modal show
    $("#partnermodal").on('shown.bs.modal', function(){
        $("#oldham").focus();
    });
    
    // configure typeahead
    $("#oldham").typeahead({
        autoselect: false,
        highlight: true,
        minLength: 1
    },
    {
        source: partnermatcher(partners),
        templates: {
            suggestion: _.template("<p><%- partner %></p>")
        }
    });
    
    // if typeahead option selected
    $("#oldham").on("typeahead:selected", function() {

        $("#partnermodal").modal('hide');
        
        // flash message and fade
            $("#partneralert").fadeIn("fast");
            setTimeout(function(){ $("#partneralert").fadeOut("slow"); }, 1000);
    });

});

// Detect bootstrap breakpoints - http://stackoverflow.com/a/14965892/6372580
function isBreakpoint(alias) 
{
    return $('.device-' + alias).is(':visible');
}


/**
 * Searches through array of partner objects for typeahead suggestions
 */
var partnermatcher = function(strs) {
  
    return function findMatches(q, cb) {
        
    var matches, substringRegex;

    // an array that will be populated with substring matches
    matches = [];

    // regex used to determine if a string contains the substring `q`
    substringRegex = new RegExp(q, 'i');

    // iterate through the pool of strings and for any string that
    // contains the substring `q`, add it to the `matches` array
    $.each(strs, function(i, str) {
        if (substringRegex.test(str.partner)) 
        {
            matches.push({partner: str.partner});
        }
    });

    cb(matches);
    };
};