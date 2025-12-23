echo alias del=rm > t.tmp
source t.tmp
del *.o
del *.a
gcc -c *.c
del simplex_main.o
ar rcs libsmp.a *.o
gcc -lm simplex_main.c libsmp.a
