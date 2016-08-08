/*global $*/

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
            var url = encodeURI('http://'+document.location.host+'?sheet='+$("#sheetselect").val()+'&partner='+$("#partnerselect").val()+'&logo='+$("#logoselect").val());
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
});

// Detect bootstrap breakpoints - http://stackoverflow.com/a/14965892/6372580
function isBreakpoint(alias) 
{
    return $('.device-' + alias).is(':visible');
}