

gcc -c main.c big_int/big_int.c lib/lib.c tests.c rsa/rsa.c rsa_cli/rsa_cli.c graphs/graphs.c stack/stack.c -O3 -march=native
gcc -o main main.o big_int.o lib.o tests.o rsa.o rsa_cli.o graphs.o stack.o -lm -O3 -march=native
./main

