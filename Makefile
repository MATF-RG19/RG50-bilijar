CC=g++
PROGRAM = pool

pool: main.o table.o draw_functions.o
	$(CC) -o $(PROGRAM) main.o table.o draw_functions.o -lGL -lGLU -lglut -lm

main.o: main.cpp
	$(CC) -c main.cpp

table.o: table.cpp table.h
	$(CC) -c table.cpp 

ball.o: draw_functions.cpp draw_functions.h
	$(CC) -c draw_functions.cpp

run: $(PROGRAM)
	./$(PROGRAM)
