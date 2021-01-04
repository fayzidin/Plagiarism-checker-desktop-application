# change application name here (executable output name)
TARGET=Plagiarism
# compiler
CC=gcc
# debug
DEBUG=-g
# optimisation
OPT=-O0
# warnings
WARN=-Wall

PTHREAD=-pthread

CCFLAGS=$(DEBUG) $(OPT) $(WARN) $(PTHREAD) -pipe

GTKLIB=`pkg-config --cflags --libs gtk+-3.0`

# linker
LD=gcc
LDFLAGS=$(PTHREAD) $(GTKLIB) -export-dynamic

OBJS=    main.o

all: $(OBJS)
	$(LD) -o $(TARGET) $(OBJS) $(LDFLAGS)
    
<<<<<<< HEAD
<<<<<<< HEAD
main.o: admin.c
	$(CC) -c $(CCFLAGS) admin.c $(GTKLIB) -o main.o
=======
main.o: src/txtcheck.c
	$(CC) -c $(CCFLAGS) src/txtcheck.c $(GTKLIB) -o main.o
>>>>>>> eb4f344df4ee88f933b9138174b647f68458a93e
=======
main.o: src/txtcheck.c
	$(CC) -c $(CCFLAGS) src/txtcheck.c $(GTKLIB) -o main.o
>>>>>>> eb4f344df4ee88f933b9138174b647f68458a93e
    
clean:
	rm -f *.o $(TARGET)
