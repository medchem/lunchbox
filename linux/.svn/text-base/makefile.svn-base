.PHONY: all
all: readlunchdata testlunch
readlunchdata: read_lunch_data.c textutil.o
	gcc -o readlunchdata read_lunch_data.c textutil.o
testlunch: lunchbox.o textutil.o testlunch.c
	gcc -o testlunch lunchbox.o textutil.o testlunch.c 
lunchbox.o: lunchbox.c lunchbox.h
	gcc -c -o lunchbox.o lunchbox.c
textutil.o: textutil.c textutil.h
	gcc -c -o textutil.o textutil.c 
.PHONY: clean
clean: 
	rm *.o 
	rm testlunch 
	rm readlunchdata

