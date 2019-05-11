gcc -c dataset.c -o dataset.o
gcc -c models.c -o models.o
gcc main.c models.o dataset.o -o main