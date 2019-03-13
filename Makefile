LIBS = \
	./hosts/*.c\
	./packets/*.c\

all:
	gcc -o main.exec main.c $(LIBS)

clean:
	-rm -f *.exec
	-rm -f *.o
