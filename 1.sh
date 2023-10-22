
clear
python3 1.py
gcc -c main.c big_int/big_int.c lib/lib.c tests.c -march=native -O3
gcc -o main main.o big_int.o lib.o tests.o -lm -march=native -O3
./main
