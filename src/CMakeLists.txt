
# Look for headers in the include directory
include_directories(${CMAKE_SOURCE_DIR}/include)
#add_library(some_library SHARED some_library.cpp)


add_library(sess17_lib sess17.cpp)
add_executable(sess17 main.cpp)
target_link_libraries(sess17 PRIVATE sess17_lib)

add_library(arabic_lib arabic.cpp)
add_executable(arabic main_arabic.cpp)
target_link_libraries(arabic PRIVATE arabic_lib)

add_library(arabic2_lib arabic2.cpp)
add_executable(arabic2 main_arabic2.cpp)
target_link_libraries(arabic2 PRIVATE arabic2_lib)