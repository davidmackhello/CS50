// execute when the DOM is fully loaded
$(function() {

    $(window).resize(function () {

        if(isBreakpoint('xs') ) {
            $('.mar-bottom').css('margin-bottom', '395px');
            }
            
        if(isBreakpoint('md') || isBreakpoint('lg')) {
            $('.mar-bottom').css('margin-bottom', '175px');
            }
    });
});

    /**
     * Detect breakpoint
     * http://stackoverflow.com/a/14965892/6372580
     */
function isBreakpoint(alias) 
{
    return $('.device-' + alias).is(':visible');
}