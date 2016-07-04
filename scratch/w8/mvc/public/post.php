<!DOCTYPE html>

<html>
    <head>
        <title>Mult Table</title>
        <link href="mstyle.css" rel="stylesheet" />
    </head>
    <body>
        <table cellpadding="10">
            <?php 
                $d = $_POST["param"];

                for($i = 0; $i < $d; $i++)
                {
                    print("<tr>");
                    
                    for($j = 0; $j < $d; $j++)
                    {
                        print("<td>" . ($i + 1) * ($j + 1) . "</td>");
                    }
                    
                    print("</tr>");
                }
            
            ?>
        </table>
    </body>
</html>