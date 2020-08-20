CC=g++
PROGRAM = pool

pool: main.o table.o draw_functions.o ball.o
	$(CC) -o $(PROGRAM) main.o table.o draw_functions.o ball.o -lGL -lGLU -lglut -lm

main.o: main.cpp
	$(CC) -c main.cpp

table.o: table.cpp table.h
	$(CC) -c table.cpp

ball.o: ball.cpp ball.h
	$(CC) -c ball.cpp 

draw_functions.o: draw_functions.cpp draw_functions.h
	$(CC) -c draw_functions.cpp

run: $(PROGRAM)
	./$(PROGRAM)
