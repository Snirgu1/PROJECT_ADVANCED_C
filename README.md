# PROJECT_ADVANCED_C
Apartments database 2020 - advanced C program course 

The next program maintenance database of apartments. 

There are 5 main commands - add, find, delete , buy, exit .
There are 2 history commands - "history " - Prints full commands history . 
"shor_history" = Print Last 7 commands . 
There is another command type - Reconstruction -  " ! " 
The combination of '!' and number will call the command that has this number in the history list.
The searching result will be printed from highest price  to lowest price if  "-s" combined in the command line.
The searching result will be printed from lowest price  to highest t price if  "-sr" combined in the command line.
In addition the program documents the history of commands and saves it between runs. The program saves all the data for the next run at the end of the program, Commands history is saved in txt.file.Apartment's information is saved in bin.file .The program loads the saved data(if there is any saved data) at the start.The loading is by reading Bin file and Txt file .
Test 1 ( Without files to load from ):

add-apt "Dizengoff 180 Tel Aviv" 2000000 4 28 09 20
add-apt "Rothschild 67 Rishon Le Zion" 1700000 3 03 10 20
add-apt "Ben Gurion 25 Herzliya" 2200000 5 01 08 20 
add-apt "Gordon 85 Holon" 1500000 3 15 06 21
find-apt –MinNumRooms 3 –MaxNumRooms 5 –MaxPrice 1750000 –s 
find-apt –MinNumRooms 4 –srfind-apt –MaxNumRooms 5 –s 
buy-apt 2history!5^5^6!3^Ben Gurion^David Ben Gurion short_history
!6 
!!
find-apt -Date 01102020 –sr 
exit

Test 2 ( With files from first run ):
history 
add-apt "Moshe Dayan 4 Eilat" 1300000 4 27 08 20 
find-apt -MaxPrice 2250000 –sr
short_history
history 
exit

For any questions please email me at : snirgu1@gmail.com









