<?php

function foo($s)
{
    $n = strlen($s);
    for ($i; $i < $n; $i++)
    {
        print($s[$i] . "\n");
    }
}

foo("this is cs50");

?>

<?php

$array = [1,2,3];
foreach ($array as $number)
    print($number . "\n");
    
?>