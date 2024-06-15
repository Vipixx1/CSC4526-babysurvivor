add_executable(mainLauncher mainLauncher.cpp)

target_link_libraries(mainLauncher PUBLIC src sfml-graphics sfml-audio)
if (UNIX)
    target_link_options(mainLauncher PUBLIC -pthread)
endif()

add_custom_target(copy-resources ALL
        COMMAND ${CMAKE_COMMAND} -E copy_directory_if_different ${CMAKE_SOURCE_DIR}/resources ${CMAKE_CURRENT_BINARY_DIR}/resources)
add_dependencies(mainLauncher copy-resources)

if(WIN32)
   file(GLOB_RECURSE DYNAMIC_LIBS CONFIGURE_DEPENDS ${CMAKE_SOURCE_DIR}/lib_openal32/${ARCH}/*.dll)
   file(COPY ${DYNAMIC_LIBS} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
endif()