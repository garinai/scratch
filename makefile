# add librealsense to include path
INCLUDE += -I/usr/local/include/librealsense
# add librealsense to library path
LIB += -L/usr/local/lib
# add librealsense to linker flags
LINK += -lrealsense2

# add glfw3 to include path
INCLUDE += -I/usr/local/include/GLFW3
# add glfw3 to library path
LIB += -L/usr/local/lib
# add glfw3 to linker flags
LINK += -lglfw -lGLU -lGL -lXrandr -lXi -lXinerama -lX11 -lrt -ldl 




make: test
	./test
	
	

test: rs-multicam.cpp
	g++ -pthread rs-multicam.cpp $(LINK) $(LIB) $(INCLUDE) -o test