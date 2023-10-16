
clear

gcc -c main.c big_int/big_int.c lib/lib.c tests.c -march=native -Ofast
gcc -o main main.o big_int.o lib.o tests.o -lm
./main
