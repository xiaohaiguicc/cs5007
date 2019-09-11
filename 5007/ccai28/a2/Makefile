all: runbenchmark clean

runslow: slowsort.c
	gcc -o slowsort slowsort.c
	./slowsort

runfast: fastsort.c
	gcc -o fastsort fastsort.c
	./fastsort

runbenchmark: runslow runfast

clean:
	rm -f slowsort
	rm -f fastsort
