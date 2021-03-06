SHELL=cmd.exe
.PHONY: all
all: read_lunch_data.exe testlunch.exe
read_lunch_data.exe: textutil.o textutil.h read_lunch_data.c
	gcc -o read_lunch_data.exe textutil.o read_lunch_data.c \
		-liconv
testlunch.exe: lunchbox.o textutil.o testlunch.c
	gcc -o testlunch.exe lunchbox.o textutil.o testlunch.c -liconv
lunchbox.o: lunchbox.c lunchbox.h
	gcc -c -o lunchbox.o lunchbox.c
textutil.o: textutil.c textutil.h
	gcc -c -o textutil.o textutil.c -liconv
.PHONY: clean
clean: 
	del *.o *.exe
	del *~
