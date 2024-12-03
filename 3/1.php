<?php

$file = file("input.txt");

$total = 0;
$enabled = true;
foreach($file as $line) {
    preg_match_all("/do\(\)|don't\(\)|mul\(([0-9]+),([0-9]+)\)/",$line,$matches);
    for($i=0;$i<count($matches[0]);$i++) {
        if ($matches[0][$i]=="do()") {
            $enabled = true;
        } else if ($matches[0][$i]=="don't()") {
            $enabled = false;
        } else if ($enabled) {
            $mul = $matches[1][$i]*$matches[2][$i];
            $total += $mul;    
        }
    }
}

echo $total."\n";