CC = g++
CCFLAGS = -lSDL -lroscpp_serialization -I/opt/ros/indigo/include -L/opt/ros/indigo/lib -Wl,-rpath,/opt/ros/indigo/lib -lroscpp -lrosconsole -lrostime

all : compassOutput

compassOutput : compassOutput.cpp SDL_rotozoom.c
	$(CC) compassOutput.cpp SDL_rotozoom.c $(CCFLAGS) 
	
clean:
	rm -f compassOutput
