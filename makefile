OBJS = *.cpp
CC = g++

all:
	$(CC) $(OBJS) -o algoritmo-genetico.app
	./algoritmo-genetico.app $(INSTANCE)