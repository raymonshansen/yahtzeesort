CC=gcc
CFLAGS=-pg -g -Wall -Werror -Wextra -fno-pie -static

make: yahtzeesort.o 
	gcc -o yahtzee yahtzeesort.o -pg -static
