OBJS	= dijkstra.o
SOURCE	= dijkstra.cpp
HEADER	=
OUT	= dijkstra
CC	 = g++
FLAGS	 = -g -c -Wall
LFLAGS	 =

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

dijkstra.o: dijkstra.cpp
	$(CC) $(FLAGS) dijkstra.cpp


clean:
	rm -f $(OBJS) $(OUT)