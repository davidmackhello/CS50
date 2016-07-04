var nums = [1, 2, 3, 4, 5];

// demonstrates an anonymous function
function changeArray()
{
    // display nums before the map has been applied
    console.log('Before: ');
    var logstring = '';
    for (var element of nums)
    {
        logstring += element + '  ';
    }
    console.log(logstring);
    
    // map the array and assign it back to nums
    nums = nums.map(function(num) {
        return num * 2;
    });
    
    // display nums after the map has been applied
    console.log('After: ');
    logstring = '';
    for (var element of nums)
    {
        logstring += element + '  ';
    }
    console.log(logstring + '\n');
}