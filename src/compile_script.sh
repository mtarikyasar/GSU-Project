gcc -c quick_sort_table.c -o quick_sort_table.o
gcc -c models.c -o models.o
gcc -c dataset.c -o dataset.o
gcc main.c dataset.o models.o quick_sort_table.o -o main 
