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
            if ($("#partnerselect").val() == "GETALL")
            {
                var partnerdata = [["Referral Partner", "Custom Link"]];
                
                for (var i = 0; i < partners.length; i++)
                {
                    var array = [partners[i].partner];
                    var thisurl = encodeURI('http://'+document.location.host+'?sheet='+$("#sheetselect").val()+'&p_id='+partners[i].id+'&logo='+$("#logoselect").val());
                    array.push(thisurl);
                    partnerdata.push(array);
                }
                $("#linkfield").val("");

                exportToCsv("links", partnerdata);
            }
            
            else
            {
                var url = encodeURI('http://'+document.location.host+'?sheet='+$("#sheetselect").val()+'&p_id='+$("#partnerselect").val()+'&logo='+$("#logoselect").val());
                $("#linkfield").val(url);
                $("#linkfield").select();            
            }
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
            setTimeout(function(){ $("#partneralert").fadeOut("slow"); }, 1250);
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

/**
 * export CSV from array of arrays - http://stackoverflow.com/questions/14964035/how-to-export-javascript-array-info-to-csv-on-client-side
 */
function exportToCsv(filename, rows) {
        var processRow = function (row) {
            var finalVal = '';
            for (var j = 0; j < row.length; j++) {
                var innerValue = row[j] === null ? '' : row[j].toString();
                if (row[j] instanceof Date) {
                    innerValue = row[j].toLocaleString();
                };
                var result = innerValue.replace(/"/g, '""');
                if (result.search(/("|,|\n)/g) >= 0)
                    result = '"' + result + '"';
                if (j > 0)
                    finalVal += ',';
                finalVal += result;
            }
            return finalVal + '\n';
        };

        var csvFile = '';
        for (var i = 0; i < rows.length; i++) {
            csvFile += processRow(rows[i]);
        }

        var blob = new Blob([csvFile], { type: 'text/csv;charset=utf-8;' });
        if (navigator.msSaveBlob) { // IE 10+
            navigator.msSaveBlob(blob, filename);
        } else {
            var link = document.createElement("a");
            if (link.download !== undefined) { // feature detection
                // Browsers that support HTML5 download attribute
                var url = URL.createObjectURL(blob);
                link.setAttribute("href", url);
                link.setAttribute("download", filename);
                link.style.visibility = 'hidden';
                document.body.appendChild(link);
                link.click();
                document.body.removeChild(link);
            }
        }
    }