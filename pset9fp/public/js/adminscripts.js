/*global $*/

/**
 * adminscripts.js
 *
 * js scripts for admin landing page
 * 
 */

// execute when the DOM is fully loaded
$(function() {
    
    console.log("hrllo");
    
    $("#getlink").on("click", function(){

        if ($("#sheetselect").val() != null && $("#partnerselect").val() != null && $("#logoselect").val() != null)
        {
            var url = encodeURI('http://'+document.location.host+'?sheet='+$("#sheetselect").val()+'&partner='+$("#partnerselect").val()+'&logo='+$("#logoselect").val())
            $("#linkfield").val(url);
            $("#linkfield").select();            
        }

    });
});