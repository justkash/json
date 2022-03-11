include(FetchContent)

# Testing library
FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG v2.13.8
)
FetchContent_MakeAvailable(Catch2)

set(TEST_EXEC "test_lib")
add_executable(
    ${TEST_EXEC}
    test_lib.cpp
    test_jsonstring.cpp
    test_jsonnumber.cpp
    test_jsonboolean.cpp
    test_jsonnull.cpp
    test_jsonarray.cpp
    test_jsonobject.cpp
)

target_compile_features(${TEST_EXEC} PRIVATE cxx_std_17)

# Link to main lib and catch2
target_link_libraries(${TEST_EXEC} PRIVATE ${PROJECT_NAME} Catch2::Catch2)

# Register tests
list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/contrib)
include(Catch)
catch_discover_tests(${TEST_EXEC})

