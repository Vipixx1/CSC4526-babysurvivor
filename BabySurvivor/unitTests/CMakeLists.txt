#
# Lines inspired by https://google.github.io/googletest/quickstart-cmake.html
#

# Note: include(GoogleTest)and enable_testing() already done in top CMakeLists.txt
add_executable(unitTests unitTests.cpp)
target_link_libraries(unitTests GTest::gtest_main src sfml-graphics)
if (UNIX)
  target_link_options(unitTests PUBLIC -pthread)
endif()

# The next line enables CMake’s test runner to discover the tests included in the binary,
# using the GoogleTest CMake module (which was included in root CMakeLists.txt).
gtest_discover_tests(unitTests)

add_custom_target(copy-resources-unitTests ALL 
	 COMMAND ${CMAKE_COMMAND} -E copy_directory_if_different ${CMAKE_SOURCE_DIR}/resources ${CMAKE_CURRENT_BINARY_DIR}/resources)
add_dependencies(unitTests copy-resources-unitTests)

if(WIN32)
   file(GLOB_RECURSE DYNAMIC_LIBS CONFIGURE_DEPENDS ${CMAKE_SOURCE_DIR}/lib_openal32/${ARCH}/*.dll)
   file(COPY ${DYNAMIC_LIBS} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
endif()