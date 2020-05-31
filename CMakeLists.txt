cmake_minimum_required(VERSION 2.8)

project( eurobot-vision )

find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

add_executable( eurobot-vision
	eurobot-vision.cpp
	Color/Color.cpp
	Camera/Camera.cpp
	Contouring/Contouring.cpp
	ColorTracking/ColorTracking.cpp
)
target_link_libraries( eurobot-vision ${OpenCV_LIBS} )
