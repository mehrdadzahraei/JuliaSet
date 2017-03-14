
cmake_minimum_required(VERSION 2.6) 
PROJECT (FractalesJulia)
find_package(OpenCV REQUIRED )
set( NAME_SRC
    juliaset.cpp    
)

# set the path to the library folder
link_directories(/usr/local/lib)

# link the libraries to the executable
target_link_libraries (FractalesJulia)

SET(CMAKE_CXX_FLAGS "-std=c++11")


INCLUDE_DIRECTORIES(-L/usr/local/include/)
link_directories( ${CMAKE_BINARY_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
add_executable( FractalesJulia ${NAME_SRC} )

target_link_libraries( FractalesJulia ${OpenCV_LIBS} )