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
