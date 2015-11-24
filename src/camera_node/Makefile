# the compiler: gcc for C program, define as g++ for C++
CPP = g++

# compiler flags:
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
#CPPFLAGS  = -g -Wall
CPPFLAGS  = -g

#INCLUDES = -I/home/newhall/include  -I../include
INCLUDES = -I/usr/local/opt/opencv3/include

#LFLAGS = -L/home/newhall/lib  -L../lib
LFLAGS = -L/usr/local/opt/opencv3/lib

#LIBS = -lmylib -lm
LIBS = -lopencv_shape -lopencv_stitching -lopencv_objdetect -lopencv_superres -lopencv_videostab -lopencv_calib3d -lopencv_features2d -lopencv_highgui -lopencv_videoio -lopencv_imgcodecs -lopencv_video -lopencv_photo -lopencv_ml -lopencv_imgproc -lopencv_flann -lopencv_core -lopencv_hal        # put linker settings here

#SRCS = main.cpp camera.cpp comm.cpp sync.cpp monitor.cpp
SRCS = main.cpp camera.cpp comm.cpp

# the build target executable:
TARGET = camera_node

#OBJS = $(SRCS:.cpp=.o)

.PHONY: depend clean

all: $(TARGET)
	@echo  camera_node has been compiled

$(TARGET): $(SRCS)
	$(CPP) $(CPPFLAGS) $(INCLUDES) $(SRCS) -o $(TARGET) $(LFLAGS) $(LIBS)

depend: $(SRCS)
	makedepend $(INCLUDES) $^

clean:
	$(RM) $(TARGET)
	$(RM) *.o
