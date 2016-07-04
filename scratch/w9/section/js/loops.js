var wkArray = ['Monday', 'Tuesday', 'Wednesday', 'Thursday',
               'Friday', 'Saturday', 'Sunday'];

// for...of is used to get the values in an associative array/object
function forof() {
    
    for (var day of wkArray)
    {
        console.log(day + '\n');
    }
}

// for...in is used to get the keys in an associative array/object
function forin() {
    
    for (var day in wkArray)
    {
        console.log(day + '\n');
    }
}

