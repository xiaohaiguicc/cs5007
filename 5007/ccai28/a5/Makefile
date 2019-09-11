# chenxi cai 2019-2-22
all: play test

matrix_build: a5.h a5_matrix.c
	gcc a5_matrix.c -o matrix

list_build: a5.h a5_list.c
	gcc a5_list.c -o list

matrix: matrix_build
	./matrix

list: list_build
	./list

run: matrix list

memcheck: matrix_build list_build
	valgrind --leak-check=full ./matrix
	valgrind --leak-check=full ./list

.PHONY: clean
clean:
	rm -f matrix
	rm -f list
