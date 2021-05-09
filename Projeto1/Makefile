#compile

CC = g++
LD = g++
AR = ar


#linkedit
DEBUG = -D _MY_DEBUG_
CFLAGS = -Wall -g
LDFLAGS = -Wall

AFLAGS = -r

SOURCES = main.cpp FileCreator.cpp FixedRecord.cpp FileHeader.cpp FileManager.cpp FileManipulator.cpp \
								 ./fixedHeap/FixedHeapFileCreator.cpp \
								 ./fixedHeap/FixedHeapHeader.cpp \
								 ./fixedHeap/FixedHeapManipulator.cpp
MAIN = main
MAINOBJS = $(SOURCES:.c=.o)

EXECS = $(MAIN)

ALL = $(MAIN)

$(MAIN) : $(MAINOBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

clean:
	rm -f *.o $(ALL)