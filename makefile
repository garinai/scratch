INCLUDE += -I/usr/local/include/librealsense
LIB += -L/usr/local/lib
LINK += -lrealsense2

INCLUDE += -I/usr/local/include/GLFW3
LINK += -lglfw -lGLU -lGL -lXrandr -lXi -lXinerama -lX11 -lrt -ldl 

make: test
	./test
	
test: rs-multicam.cpp
	g++ -pthread rs-multicam.cpp $(LINK) $(LIB) $(INCLUDE) -o test