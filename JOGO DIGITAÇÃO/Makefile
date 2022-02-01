all: compile link open

compile:
	g++ -IC:\SFML-2.5.1\include -c main.cpp 

link:
	g++ -o main.exe main.o  -LC:\SFML-2.5.1\lib -lsfml-graphics -lsfml-window -lsfml-system

open:
	.\main.exe