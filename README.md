# DS4Snake - HackISU 2018

Must connect a dualshock 4 controller to a windows laptop to play the game.

To run, download the ds4rd.exe file and the Snake.c file, and place in the same folder.

Compile the Snake.c file in cygwin by using the command 
"gcc -o Snake Snake.c -lncurses"

Run the game using the command 
"./ds4rd.exe -d 054c:05c4 -D DS4_BT -t -bd | ./Snake
