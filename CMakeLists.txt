cmake_minimum_required(VERSION 3.18)

project(rekt VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_EXTENSIONS OFF)

include(CTest)
include(FetchContent)

if(MSVC)
  add_compile_options(/W4 /WX)
else()
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(Doxygen)
# find_package(nlohmann_json 3.2.0 REQUIRED)

add_subdirectory(src)
add_subdirectory(test)

if (DOXYGEN_FOUND)
	add_subdirectory(docs/doxygen)
else()
	message(WARNING "Doxygen not found. Source code documentation will not be generated.")
endif()
