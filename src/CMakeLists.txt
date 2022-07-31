FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.10.5/json.tar.xz)
FetchContent_MakeAvailable(json)

SET(LIB_CXX_LIST
	rectangle.cpp
	io.cpp
	util.cpp
	rekt.cpp
)

SET(LIB_HEADER_LIST
	"${PROJECT_SOURCE_DIR}/include/rekt/rectangle.hpp"
	"${PROJECT_SOURCE_DIR}/include/rekt/io.hpp"
	"${PROJECT_SOURCE_DIR}/include/rekt/util.hpp"
	"${PROJECT_SOURCE_DIR}/include/rekt/rekt.hpp"
)

add_library(rekt ${LIB_CXX_LIST} ${LIB_HEADER_LIST})

SET(APP_CXX_LIST main.cpp)
add_executable(rektapp ${APP_CXX_LIST})

# We need this directory, and users of our library will need it too
target_include_directories(rekt PUBLIC ../include)

target_link_libraries(rekt PRIVATE nlohmann_json::nlohmann_json)
target_link_libraries(rektapp PRIVATE rekt)

# Use C++17
target_compile_features(rekt PRIVATE cxx_std_17)
target_compile_features(rektapp PRIVATE cxx_std_17)

add_custom_command(TARGET rekt POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E make_directory ${PROJECT_BINARY_DIR}/lib/
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:rekt> ${PROJECT_BINARY_DIR}/lib/
)

add_custom_command(TARGET rektapp POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E make_directory ${PROJECT_BINARY_DIR}/bin/
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:rektapp> ${PROJECT_BINARY_DIR}/bin/
)