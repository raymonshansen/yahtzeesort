CC=gcc
CFLAGS=-Wall -Werror -Wextra

make: yahtzeesort.o 
	gcc -o yahtzee yahtzeesort.o
