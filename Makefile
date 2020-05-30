O := "a.exe"

all:
	g++ $(wildcard ./src/*.cpp) $(wildcard ./src/**/*.cpp) -o $(O) -g