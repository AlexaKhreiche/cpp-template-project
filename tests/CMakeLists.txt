include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.15.2
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
include(GoogleTest)

# Make all targets in this directory look for headers here
include_directories(${CMAKE_SOURCE_DIR}/src ${CMAKE_SOURCE_DIR}/include)
# Make all targets in this directory link against Gtest
link_libraries(GTest::gtest_main)

#add_executable(test_some_library test_some_library.cpp) # Compile a test source
# Link against any required libraries. The library "some_library" is compiled in src/
#target_link_libraries(test_some_library some_library)
#gtest_discover_tests(test_some_library)            # Register the tests to gtest



add_executable(sess17_test sess17_test.cpp) 
target_link_libraries(sess17_test PRIVATE sess17_lib)
gtest_discover_tests(sess17_test)     

add_executable(arabic_test arabic_test.cpp)
target_link_libraries(arabic_test PRIVATE arabic_lib)
gtest_discover_tests(arabic_test) 

add_executable(arabic2_test arabic2_test.cpp)
target_link_libraries(arabic2_test PRIVATE arabic2_lib)
gtest_discover_tests(arabic2_test) 