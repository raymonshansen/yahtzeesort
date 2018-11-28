plot "results.csv" using 1:2 with lines title "Yahtzee-sort" lw 2, \
"" using 1:3 with lines title "Merge-sort" lw 2, \
"" using 1:4 with lines title "Bubble-sort" lw 2, \
"" using 1:5 with lines title "Quick-sort" lw 2
pause 1
stats "results.csv" using 1 nooutput
if(STATS_max > 19000){
    pause 3
    exit
}
reread