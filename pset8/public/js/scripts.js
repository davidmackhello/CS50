/* global google */
/* global _ */
/**
 * scripts.js
 *
 * Computer Science 50
 * Problem Set 8
 *
 * Global JavaScript.
 */

// Google Map
var map;

// markers for map
var markers = [];

// info window
var info = new google.maps.InfoWindow();

// execute when the DOM is fully loaded
$(function() {

    // styles for map
    // https://developers.google.com/maps/documentation/javascript/styling
    var styles = [

        // hide Google's labels
        {
            featureType: "all",
            elementType: "labels",
            stylers: [
                {visibility: "off"}
            ]
        },

        // hide roads
        {
            featureType: "road",
            elementType: "geometry",
            stylers: [
                {visibility: "off"}
            ]
        },
        
        // show university features
        {
            featureType: "poi.school",
            elementType: "all",
            stylers: [
                {visibility: "on"}
            ]
        },

    ];

    // options for map
    // https://developers.google.com/maps/documentation/javascript/reference#MapOptions
    var options = {
        center: {lat: 42.335515, lng: -71.1712763}, // Boston College, Chestnut Hill, Massachusetts
        disableDefaultUI: true,
        mapTypeId: google.maps.MapTypeId.ROADMAP,
        maxZoom: 14,
        panControl: true,
        styles: styles,
        zoom: 13,
        zoomControl: true
    };

    // get DOM node in which map will be instantiated
    var canvas = $("#map-canvas").get(0);

    // instantiate map
    map = new google.maps.Map(canvas, options);

    // configure UI once Google Map is idle (i.e., loaded)
    google.maps.event.addListenerOnce(map, "idle", configure);

});

/**
 * Adds marker for place to map.
 */
function addMarker(place)
{
    // create marker with label and add to map at inputted location
    var marker = new MarkerWithLabel({
        position: {
            lat: (_.isNumber(place.latitude)) ? place.latitude : parseFloat(place.latitude), 
            lng: (_.isNumber(place.longitude)) ? place.longitude : parseFloat(place.longitude)
        },
        map: map,
        icon: "img/wifi.png", // icon source: http://mapicons.nicolasmollet.com/category/markers/
        labelAnchor: new google.maps.Point(45, 0),
        labelContent: "<span class=\"label\">"+place.place_name+", "+place.admin_code1+"</span>"
    });
    
    // add click listener to marker that fetches local articles and displays in info window
    marker.addListener('click', function() {

        // fetch articles for given geo point using zip code
        var parameters = {
            geo: place.postal_code
        };
        $.getJSON("articles.php", parameters)
        .done(function(data, textStatus, jqXHR) {
            
            // check if no articles received
            if (data.length < 1)
            {
                // show info window
                showInfo(marker, "Slow news day!");
            }
            
            else
            {
                // start unordered list
                var list = "<ul>";
                
                // create compilation function to format each article in list
                var compiled = _.template("<li><a href=\"<%- url %>\" target=\"_blank\"><%- title %></a></li>");
                
                // format each article and add to unordered list
                for (var i = 0; i < data.length; i++)
                {
                    list += compiled({url: data[i].link, title: data[i].title});
                }
    
                // complete unordered list
                list += "</ul>";
    
                // show info window
                showInfo(marker, list);
            }
        })
        .fail(function(jqXHR, textStatus, errorThrown) {
    
             // log error to browser's console
             console.log(errorThrown.toString());
        });
        
        // create undefined variable to trigger gif in info window while AJAX request completes
        var loader;
        
        // show info window with loader gif
        showInfo(marker, loader);
    });
    
    // add marker to global markers array
    markers.push(marker);
}

/**
* Constructor function for buttons that center map
* Adapted from https://developers.google.com/maps/documentation/javascript/examples/control-custom
*/
function CenterControl(controlDiv, map, loc) {
    
    // Set CSS for the control border.
    var controlUI = document.createElement('div');
    controlUI.style.backgroundColor = '#fff';
    controlUI.style.border = '2px solid #fff';
    controlUI.style.borderRadius = '3px';
    controlUI.style.boxShadow = '0 2px 6px rgba(0,0,0,.3)';
    controlUI.style.cursor = 'pointer';
    controlUI.style.marginBottom = '22px';
    controlUI.style.textAlign = 'center';
    controlUI.title = loc.label;
    controlDiv.appendChild(controlUI);

    // Set CSS for the control interior.
    var controlText = document.createElement('div');
    controlText.style.color = 'rgb(25,25,25)';
    controlText.style.fontFamily = 'Roboto,Arial,sans-serif';
    controlText.style.fontSize = '16px';
    controlText.style.lineHeight = '20px';
    controlText.style.paddingLeft = '5px';
    controlText.style.paddingRight = '5px';
    controlText.innerHTML = loc.label;
    controlUI.appendChild(controlText);

    // Set click event listener for control to reposition and update map
    controlUI.addEventListener('click', function() {
        map.setCenter(loc.coord);
        map.setZoom(14);
    });
}

/**
 * Configures application.
 */
function configure()
{
    // update UI after map has been dragged
    google.maps.event.addListener(map, "dragend", function() {
        update();
    });

    // update UI after zoom level changes
    google.maps.event.addListener(map, "zoom_changed", function() {
        update();
    });

    // remove markers whilst dragging
    google.maps.event.addListener(map, "dragstart", function() {
        removeMarkers();
    });

    // configure typeahead
    // https://github.com/twitter/typeahead.js/blob/master/doc/jquery_typeahead.md
    $("#q").typeahead({
        autoselect: true,
        highlight: false,
        minLength: 1
    },
    {
        source: search,
        templates: {
            empty: "no places found yet",
            suggestion: _.template("<p><%- place_name %>, <%- admin_name1 %> <span class=\"postal\"><%- postal_code %></p></span>")
        }
    });

    // re-center map after place is selected from drop-down
    $("#q").on("typeahead:selected", function(eventObject, suggestion, name) {

        // ensure coordinates are numbers
        var latitude = (_.isNumber(suggestion.latitude)) ? suggestion.latitude : parseFloat(suggestion.latitude);
        var longitude = (_.isNumber(suggestion.longitude)) ? suggestion.longitude : parseFloat(suggestion.longitude);

        // set map's center
        map.setCenter({lat: latitude, lng: longitude});
    
        // update UI
        update();
    });

    // hide info window when text box has focus
    $("#q").focus(function(eventData) {
        hideInfo();
    });

    // re-enable ctrl- and right-clicking (and thus Inspect Element) on Google Map
    // https://chrome.google.com/webstore/detail/allow-right-click/hompjdfbfmmmgflfjdlnkohcplmboaeo?hl=en
    document.addEventListener("contextmenu", function(event) {
        event.returnValue = true; 
        event.stopPropagation && event.stopPropagation(); 
        event.cancelBubble && event.cancelBubble();
    }, true);

    // update UI
    update();

    // give focus to text box
    $("#q").focus();
    
    // define university locations for custom controls
    var schools = [
        
        {
            coord: {lat: 42.335515, lng: -71.1712763},
            label: "Boston College"
        },
        
        {
            coord: {lat: 42.376928, lng: -71.116629},
            label: "Harvard University"
        },

        {
            coord: {lat: 41.315802, lng: -72.922206},
            label: "Yale University"
        },        

        {
            coord: {lat: 37.427517, lng: -122.170233},
            label: "Stanford University"
        }

    ];
    
    // construct custom controls
    for (var i = 0; i < schools.length; i++)
    {
        var centerControlDiv = document.createElement('div');
        var centerControl = new CenterControl(centerControlDiv, map, schools[i]);
    
        centerControlDiv.index = (i + 1);
        map.controls[google.maps.ControlPosition.RIGHT_TOP].push(centerControlDiv);
    }
}

/**
 * Hides info window.
 */
function hideInfo()
{
    info.close();
}

/**
 * Removes markers from map.
 */
function removeMarkers()
{
    // hide markers from map
    for (var i = 0; i < markers.length; i++) {
        markers[i].setMap(null);
    }
    
    // clear markers array
    markers = [];
}

/**
 * Searches database for typeahead's suggestions.
 */
function search(query, cb)
{
    // get places matching query (asynchronously)
    var parameters = {
        geo: query
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
 * Shows info window at marker with content.
 */
function showInfo(marker, content)
{
    // start div
    var div = "<div id='info'>";
    if (typeof(content) === "undefined")
    {
        // http://www.ajaxload.info/
        div += "<img alt='loading' src='img/ajax-loader.gif'/>";
    }
    else
    {
        div += content;
    }

    // end div
    div += "</div>";

    // set info window's content
    info.setContent(div);

    // open info window (if not already open)
    info.open(map, marker);
}

/**
 * Updates UI's markers.
 */
function update() 
{
    // get map's bounds
    var bounds = map.getBounds();
    var ne = bounds.getNorthEast();
    var sw = bounds.getSouthWest();

    // get places within bounds (asynchronously)
    var parameters = {
        ne: ne.lat() + "," + ne.lng(),
        q: $("#q").val(),
        sw: sw.lat() + "," + sw.lng()
    };
    $.getJSON("update.php", parameters)
    .done(function(data, textStatus, jqXHR) {

        // remove old markers from map
        removeMarkers();

        // add new markers to map
        for (var i = 0; i < data.length; i++)
        {
            addMarker(data[i]);
        }
     })
     .fail(function(jqXHR, textStatus, errorThrown) {

         // log error to browser's console
         console.log(errorThrown.toString());
     });
}