CC = g++
CCFLAGS = -lSDL -lroscpp_serialization -I/opt/ros/indigo/include -L/opt/ros/indigo/lib -Wl,-rpath,/opt/ros/indigo/lib -lroscpp -lrosconsole -lrostime

all : compassInput

compassInput : compassInput.cpp
	$(CC) compassInput.cpp -o compassInput $(CCFLAGS)
	
clean:
	rm -f compassInput
