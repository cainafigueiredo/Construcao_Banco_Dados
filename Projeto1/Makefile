#compile

CC = g++
LD = g++
AR = ar


#linkedit
DEBUG = -D _MY_DEBUG_
CFLAGS = -Wall -g
LDFLAGS = -Wall

AFLAGS = -r

SOURCES = main.cpp FileCreator.cpp FixedRecord.cpp ./fixedHeap/FixedHeapFileCreator.cpp ./fixedHeap/FixedHeapHeader.cpp
RESULTADO = resultado
MAINOBJS = $(SOURCES:.c=.o)

EXECS = $(RESULTADO)

ALL = $(RESULTADO)

$(RESULTADO) : $(MAINOBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

clean:
	rm -f *.o $(ALL)