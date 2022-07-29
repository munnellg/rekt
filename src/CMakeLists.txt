SET(APP_CXX_LIST main.cpp rektapp.cpp)
SET(APP_HEADER_LIST rektapp.hpp)
SET(LIB_CXX_LIST rectangle.cpp)
SET(LIB_HEADER_LIST
	"${PROJECT_SOURCE_DIR}/include/rekt/rectangle.hpp"
)

FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.10.5/json.tar.xz)
FetchContent_MakeAvailable(json)

# Make an automatic library - will be static or dynamic based on user setting
add_library(rekt ${LIB_CXX_LIST} ${LIB_HEADER_LIST})
add_executable(rektapp ${APP_CXX_LIST} ${APP_HEADER_LIST})

# We need this directory, and users of our library will need it too
target_include_directories(rekt PUBLIC ../include)

target_link_libraries(rekt PRIVATE nlohmann_json::nlohmann_json)
target_link_libraries(rektapp PRIVATE rekt)

# Use C++17
target_compile_features(rekt PRIVATE cxx_std_17)
target_compile_features(rektapp PRIVATE cxx_std_17)