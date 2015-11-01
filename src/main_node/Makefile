# the compiler: gcc for C program, define as g++ for C++
CPP = g++

# compiler flags:
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
CPPFLAGS  = -g -Wall

#INCLUDES = -I/home/newhall/include  -I../include
INCLUDES =

#LFLAGS = -L/home/newhall/lib  -L../lib
LFLAGS =

#LIBS = -lmylib -lm
LIBS =

SRCS = main.cpp light.cpp comm.cpp sync.cpp monitor.cpp

# the build target executable:
TARGET = camera_node

OBJS = $(SRCS:.cpp=.o)

.PHONY: depend clean

all: $(TARGET)
	@echo  camera_node has been compiled

$(TARGET): $(OBJS)
	$(CPP) $(CPPFLAGS) $(INCLUDES) -o $(MAIN) $(OBJS) $(LFLAGS) $(LIBS)

depend: $(SRCS)
	makedepend $(INCLUDES) $^

clean:
	$(RM) $(TARGET)
