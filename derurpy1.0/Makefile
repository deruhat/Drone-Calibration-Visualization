CC = g++
CCFLAGS = -g -lSDL -lSDL_ttf -lroscpp_serialization -std=c++0x -I/opt/ros/indigo/include -L/opt/ros/indigo/lib -Wl,-rpath,/opt/ros/indigo/lib -lroscpp -lrosconsole -lrostime

all : compassOutput

compassOutput : compassOutput.cpp SDL_rotozoom.c
	$(CC) compassOutput.cpp -o compassOutput SDL_rotozoom.c $(CCFLAGS) 
	
clean:
	rm -f compassOutput
