cmake_minimum_required(VERSION 3.5)
project(osu_player)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIR})

find_package(X11 REQUIRED)
include_directories(${X11_INCLUDE_DIR})

find_package(Threads REQUIRED)

include_directories(include)

# clicker
add_library(clicker STATIC src/clicker.cpp include/clicker.h)
target_link_libraries(clicker ${X11_LIBRARIES} Xtst)

# screener
add_library(screener STATIC src/screener.cpp include/screener.h)
target_link_libraries(screener ${X11_LIBRARIES})
target_link_libraries(screener ${OpenCV_LIBRARIES})

#analysis
add_library(analysis STATIC src/analysis.cpp include/analysis.h)
target_link_libraries(analysis ${OpenCV_LIBRARIES})

#target_link_libraries(screener ${X11_LIBRARIES} ${X11_XTest_LIB} ${OpenCV_LIBRARIES})


# main
add_executable(osu_player src/main.cpp)
target_link_libraries(osu_player clicker screener analysis ${CMAKE_THREAD_LIBS_INIT})