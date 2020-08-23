cmake_minimum_required(VERSION 3.12.4)

project(combo_parser)

set(ZLIB_ROOT "ext/zlib")
find_package(ZLIB REQUIRED)

set(OPENSSL_ROOT_DIR "ext/openssl")
find_package(OpenSSL REQUIRED)

add_definitions(-DCURL_STATICLIB)
find_package(CURL REQUIRED PATHS "ext")

file(GLOB HEADERS "include/*.hpp")
file(GLOB SOURCES "src/*.cpp")
file(GLOB DLLS "ext/openssl/bin/*.dll")

add_library(${PROJECT_NAME} STATIC ${SOURCES})
add_executable(${PROJECT_NAME}_cli main.cpp)

set_target_properties(${PROJECT_NAME} PROPERTIES DEBUG_POSTFIX "d")
set_target_properties(${PROJECT_NAME}_cli PROPERTIES RUNTIME_OUTPUT_DIRECTORY "bin"
                                                     VS_DEBUGGER_WORKING_DIRECTORY "bin/$<CONFIG>")

target_include_directories(${PROJECT_NAME} PUBLIC include PRIVATE src)

target_link_libraries(${PROJECT_NAME} CURL::libcurl)
target_link_libraries(${PROJECT_NAME}_cli ${PROJECT_NAME})

add_custom_command(TARGET ${PROJECT_NAME}_cli POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different ${DLLS} "bin/$<CONFIG>")

install(FILES ${HEADERS} DESTINATION include)
install(TARGETS ${PROJECT_NAME} ${PROJECT_NAME}_cli
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        RUNTIME DESTINATION bin)
