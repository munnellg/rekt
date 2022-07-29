# Testing library
# Adds Catch2::Catch2
FetchContent_Declare(catch GIT_REPOSITORY https://github.com/catchorg/Catch2.git GIT_TAG v2.13.8)
FetchContent_MakeAvailable(catch)

# Tests need to be added as executables first
add_executable(testrekt EXCLUDE_FROM_ALL testrekt.cpp testrectangle.cpp)

# I'm using C++17 in the test
target_compile_features(testrekt PRIVATE cxx_std_17)

# Should be linked to the main library, as well as the Catch2 testing library
target_link_libraries(testrekt PRIVATE Catch2::Catch2)
target_link_libraries(testrekt PRIVATE rekt)

# If you register a test, then ctest and make test will run it.
# You can also run examples and check the output, as well.
add_test(NAME testrekt COMMAND testrekt) # Command can be a target
