CC = g++
CCFLAGS = -lSDL -lroscpp_serialization -I/opt/ros/indigo/include -L/opt/ros/indigo/lib -Wl,-rpath,/opt/ros/indigo/lib -lroscpp -lrosconsole -lrostime

all : compassInput

compassInput : compassInput.cpp
	$(CC) compassInput.cpp $(CCFLAGS) $(LIBS)
	
clean:
	rm -f compassInput
