LIBS = \
	./hosts/*.c\
	./packets/*.c\

all:
	gcc -o networth.exec main.c $(LIBS)

clean:
	-rm -f *.exec
	-rm -f *.o
