
## Created by Anjuta

CC = gcc
CFLAGS = -g -Wall
OBJECTS = gravity_sim.o
INCFLAGS = 
LDFLAGS = -Wl,-rpath,/usr/local/lib,-lglut,-lm
LIBS = 

all: gravity_sim

gravity_sim: $(OBJECTS)
	$(CC) -o gravity_sim $(OBJECTS) $(LDFLAGS) $(LIBS)

.SUFFIXES:
.SUFFIXES:	.c .cc .C .cpp .o

.c.o :
	$(CC) -o $@ -c $(CFLAGS) $< $(INCFLAGS)

count:
	wc *.c *.cc *.C *.cpp *.h *.hpp

clean:
	rm -f *.o

.PHONY: all
.PHONY: count
.PHONY: clean
