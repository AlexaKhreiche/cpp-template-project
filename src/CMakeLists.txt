
# Look for headers in the include directory
include_directories(${CMAKE_SOURCE_DIR}/include)
#add_library(some_library SHARED some_library.cpp)

# You can also add any stand alone executables
# add_executable(example main.cpp) # Will make a binary called "example" inside build/bin using main.cpp
#add_library(sess17 SHARED sess17.cpp)
add_executable(sess17 sess17.cpp)
add_executable(arabic arabic.cpp)
add_executable(arabic2 arabic2.cpp)