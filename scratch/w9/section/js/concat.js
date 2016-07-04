// log the entire week in the console
function wholeweek1() {
    
    for (var day in wkArray)
    {
        console.log(wkArray[day] + ' is day number ' + (day + 1) + ' of the week\n');
    }
}

// log the entire week in the console
function wholeweek2() {
    
    for (var day in wkArray)
    {
        console.log(wkArray[day] + ' is day number ' + (parseInt(day) + 1) + ' of the week\n');
    }
}