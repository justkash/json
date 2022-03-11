add_library(
    ${PROJECT_NAME}
    STATIC
    json.cpp
    jsonarray.cpp
    jsonboolean.cpp
    jsonnull.cpp
    jsonnumber.cpp
    jsonobject.cpp
    jsonstring.cpp
)
add_library(${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)

target_include_directories(
    ${PROJECT_NAME}
    PUBLIC
    "$<BUILD_INTERFACE:${PROJECT_INCLUDE_DIR}>"
    "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
)
target_include_directories(${PROJECT_NAME} PRIVATE ./)

# Install the target and create export-set
include(GNUInstallDirs)
set(PROJECT_TARGETS "${PROJECT_NAME}Targets")
install(
    TARGETS ${PROJECT_NAME}
    EXPORT ${PROJECT_TARGETS}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

# Install header file
install(
    FILES 
    "${PROJECT_INCLUDE_DIR}/json/json.hpp"
    "${PROJECT_INCLUDE_DIR}/json/jsonarray.cpp"
    "${PROJECT_INCLUDE_DIR}/json/jsonboolean.cpp"
    "${PROJECT_INCLUDE_DIR}/json/jsonnull.cpp"
    "${PROJECT_INCLUDE_DIR}/json/jsonnumber.cpp"
    "${PROJECT_INCLUDE_DIR}/json/jsonobject.cpp"
    "${PROJECT_INCLUDE_DIR}/json/jsonstring.cpp"
    DESTINATION 
    ${CMAKE_INSTALL_INCLUDEDIR}
)

# Generate and install export file
install(
    EXPORT ${PROJECT_TARGETS}
    FILE "${PROJECT_NAME}${PROJECT_TARGETS}.cmake"
    NAMESPACE "${PROJECT_NAME}::"
    DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}"
)
