clear
gcc -c main.c big_int/big_int.c lib/lib.c
gcc -o main main.o big_int.o lib.o -lm
./main
