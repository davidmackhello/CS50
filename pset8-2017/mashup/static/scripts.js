// export API_KEY=AIzaSyBLvf3q_Jn53BZbIibO1NOEnP0z7NLxiX0

// Google Map
var map;

// markers for map
var markers = [];

// info window
var info = new google.maps.InfoWindow();

// HTML template for info window
var infotemplate = Handlebars.compile('<li><a href="{{link}}" target="_blank">{{title}}</a></li>');

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
    }
];

// university locations for school buttons
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
        coord: {lat: 40.1020, lng: -88.2272},
        label: "University of Illinois"
    },

    {
        coord: {lat: 41.315802, lng: -72.922206},
        label: "Yale University"
    }
];

// tack-on style for university map features
var ustyle =
[{
    featureType: "poi.school",
    elementType: "all",
    stylers: [
        {visibility: "on"}
    ]
}];

// global array for school button divs
var schoolcontroldivs = [];

// global bool to track school button visibility
var schools_vis = false;

// execute when the DOM is fully loaded
$(function() {

    // options for map
    // https://developers.google.com/maps/documentation/javascript/reference#MapOptions
    var options = {
        center: {lat: 42.3770, lng: -71.1256}, // Cambridge, MA
        disableDefaultUI: true,
        mapTypeId: google.maps.MapTypeId.ROADMAP,
        maxZoom: 15,
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
    // configure marker and add to map
    var marker = new google.maps.Marker({
        position: {lat: place.latitude, lng: place.longitude},
        map: map,
        title: 'News for ' + place.place_name,
        icon: Flask.url_for("static", {"filename": "newsagent.png"})
    });

    // set click listener on each marker
    marker.addListener('click', function() {

        // update content of info window to ajax gif
        showInfo();

        // open info window
        info.open(map, marker);

        // fetch articles for marker's zip code
        var parameters = {
            geo: place.postal_code
        };
        $.getJSON(Flask.url_for("articles"), parameters)
        .done(function(data, textStatus, jqXHR) {

            // prepare content based on returned articles
            var ul = "<ul>";
            $.each(data, function(i, obj) {
                ul += infotemplate(obj);
            });
            ul += "</ul>";

            // update info window to list of articles
            showInfo(ul);
        })
        .fail(function(jqXHR, textStatus, errorThrown) {

            // log error to browser's console
            console.log(errorThrown.toString());
        });
    });

    // add marker to global marker array
    markers.push(marker);
}

/**
* Constructor function for control buttons (either main schools toggle, or individual school)
* Adapted from https://developers.google.com/maps/documentation/javascript/examples/control-custom
*/
function CustomControl(controlDiv, map, loc) {

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

    // university control object will have coord set - set click listener to center map
    if ('coord' in loc) {
        controlUI.addEventListener('click', function() {
            map.setCenter(loc.coord);
            map.setZoom(15);
        });
    }

    // righthand toggle button - set click behavior
    else {
        controlUI.addEventListener('click', function() {

            // if school controls/univ layer hidden, show them
            if(!schools_vis) {

            // add school controls to map
            for (i = 0; i < schoolcontroldivs.length; i++) {
                map.controls[google.maps.ControlPosition.LEFT_BOTTOM].push(schoolcontroldivs[i]);
            }

            // show university features
            map.setOptions({styles: styles.concat(ustyle)});

            schools_vis = true;

            // if school controls/univ layer showing, hide them
            } else {

                // clear left-hand displays
                map.controls[google.maps.ControlPosition.LEFT_BOTTOM].clear();

                // revert to base map style
                map.setOptions({styles: styles});

                schools_vis = false;
            }
        });
    }
}

/**
 * Configures application.
 */
function configure()
{
    // update UI after map has been dragged
    google.maps.event.addListener(map, "dragstart", function() {

        // if info window isn't open
        // http://stackoverflow.com/a/12410385
        if (!info.getMap || !info.getMap()) {
            removeMarkers();
        }
    });

    // update UI after map has been dragged
    google.maps.event.addListener(map, "dragend", function() {

        // if info window isn't open
        // http://stackoverflow.com/a/12410385
        if (!info.getMap || !info.getMap()) {
            update();
        }
    });

    // update UI after zoom level changes
    google.maps.event.addListener(map, "zoom_changed", function() {
        update();
    });

    // close info window when esc key pressed
    document.onkeydown = function(e) {
        var isEscape = false;
        if ("key" in e) {
            isEscape = (e.key == "Escape" || e.key == "Esc");
        } else {
            isEscape = (e.keyCode == 27);
        }
        if (isEscape) {
            info.close();
        }
    };

    // configure typeahead
    $("#q").typeahead({
        highlight: true,
        minLength: 1
    },
    {
        display: function(suggestion) { return null; },
        limit: 10,
        source: search,
        templates: {
            suggestion: Handlebars.compile(
                "<div>{{place_name}}, {{admin_code1}} {{postal_code}}</div>"
            )
        }
    });

    // re-center map after place is selected from drop-down
    $("#q").on("typeahead:selected", function(eventObject, suggestion, name) {

        // set map's center
        map.setCenter({lat: parseFloat(suggestion.latitude), lng: parseFloat(suggestion.longitude)});

        // update UI
        update();
    });

    // hide info window when text box has focus
    $("#q").focus(function(eventData) {
        info.close();
    });

    // construct lefthand school controls
    for (var i = (schools.length - 1); i > -1; i--) {
        var schoolControlDiv = document.createElement('div');
        new CustomControl(schoolControlDiv, map, schools[i]);

        // add to global array
        schoolcontroldivs.push(schoolControlDiv);
    }

    // construct custom control for hide/show schools toggle
    var rightcontrol = document.createElement('div');
    new CustomControl(rightcontrol, map, {label: "Show/Hide Schools"});
    map.controls[google.maps.ControlPosition.RIGHT_BOTTOM].push(rightcontrol);

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
}

/**
 * Removes markers from map.
 */
function removeMarkers()
{
    // remove markers from map
    $.each(markers, function(i, marker) {
        marker.setMap(null);
    });

    // delete all references to markers currently in array
    markers = [];
}

/**
 * Searches database for typeahead's suggestions.
 */
function search(query, syncResults, asyncResults)
{
    // get places matching query (asynchronously)
    var parameters = {
        q: query
    };
    $.getJSON(Flask.url_for("search"), parameters)
    .done(function(data, textStatus, jqXHR) {

        // call typeahead's callback with search results (i.e., places)
        asyncResults(data);
    })
    .fail(function(jqXHR, textStatus, errorThrown) {

        // log error to browser's console
        console.log(errorThrown.toString());

        // call typeahead's callback with no results
        asyncResults([]);
    });
}

/**
 * Shows info window at marker with content.
 */
function showInfo(content)
{
    // grab info div
    var infodiv = $('#info');

    // if content no content sent, set window to loading gif
    if (typeof(content) == "undefined") {
        // http://www.ajaxload.info/
        infodiv.html("<img alt='loading' src='/static/ajax-loader.gif'/>");
    }

    // if content sent, set it
    else {
        infodiv.html(content);
    }

    // set info window's content
    info.setContent(infodiv.html());
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
    $.getJSON(Flask.url_for("update"), parameters)
    .done(function(data, textStatus, jqXHR) {

        // remove old markers from map
        removeMarkers();

        // add new markers to map
        for (var i = 0; i < data.length; i++) {
            addMarker(data[i]);
        }
    })
    .fail(function(jqXHR, textStatus, errorThrown) {

        // log error to browser's console
        console.log(errorThrown.toString());
    });
}