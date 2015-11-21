CXX = g++
CPPFLAGS = -I/usr/local/opt/opencv3/include		# put pre-processor settings (-I, -D, etc) here
CXXFLAGS = -Wall  														# put compiler settings here
#LDFLAGS = -L/usr/local/opt/opencv3/lib -lopencv_shape -lopencv_stitching -lopencv_objdetect -lopencv_superres -lopencv_videostab -lopencv_calib3d -lopencv_features2d -lopencv_highgui -lopencv_videoio -lopencv_imgcodecs -lopencv_video -lopencv_photo -lopencv_ml -lopencv_imgproc -lopencv_flann -lopencv_core -lopencv_hal        # put linker settings here

all: socket_client socket_server

socket_client: socket_client.cpp
	$(CXX) socket_client.cpp $(CXXFLAGS) $(LDFLAGS) -o socket_client

socket_server: socket_server.cpp
	$(CXX) socket_server.cpp $(CXXFLAGS) $(LDFLAGS) -o socket_server

#.cpp.o:
#	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $<

clean:
	rm -f *.o socket_client socket_server
