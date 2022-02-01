all: compile link open

compile:
	g++ -IC:\SFML-2.5.1\include -c Main.cpp
link:
	g++ -o Main.exe Main.o -LC:\SFML-2.5.1\lib -lsfml-graphics -lsfml-window -lsfml-system

open:
	.\Main.exe