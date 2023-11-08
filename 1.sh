
clear

gcc -c main.c big_int/big_int.c lib/lib.c tests.c rsa/rsa.c -O3 -march=native
gcc -o main main.o big_int.o lib.o tests.o rsa.o -lm -O3 -march=native
./main

