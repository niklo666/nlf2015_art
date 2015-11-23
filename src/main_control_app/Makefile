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
LIBS = -lpthread

SRCS = main_control_app.cpp

MAIN = main_control_app

# the build target executable:
TARGET = main_control_app

OBJS = $(SRCS:.cpp=.o)

.PHONY: depend clean

all: $(TARGET)
	@echo  $(TARGET) has been built

$(TARGET): $(OBJS)
	$(CPP) $(CPPFLAGS) $(INCLUDES) -o $(MAIN) $(OBJS) $(LFLAGS) $(LIBS)

depend: $(SRCS)
	makedepend $(INCLUDES) $^

clean:
	$(RM) $(TARGET) *.o
