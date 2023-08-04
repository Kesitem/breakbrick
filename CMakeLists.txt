cmake_minimum_required(VERSION 3.12)

project(BreakBreak VERSION 0.0.1
                  DESCRIPTION "A simple breakout clone"
                  LANGUAGES CXX)

#find_package(OpenGL REQUIRED)

# Add plog
find_package(plog CONFIG REQUIRED)

# Add glad
find_package(glad CONFIG REQUIRED)

# Add glm
find_package(glm CONFIG REQUIRED)

# Add glfw3
find_package(glfw3 CONFIG REQUIRED)

# Set sources files path
set(INC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

# Configure version 
configure_file (
    "${INC_DIR}/config.h.in"
    "${INC_DIR}/config.h"
)

# List of header files
set(HEADERS
    config.h
    input_state.h
    input_button.h
    input_manager.h
    core.h
    input_state.h
    input_button.h
    input_manager.h
    shader.h
    program.h
    vertex_buffer.h
    engine.h
    application.h
)
# List of source files
set(SRCS
    log_formatter.h
    log_formatter.cpp
    input_button.cpp
    input_manager.cpp
    shader.cpp
    program.cpp
    vertex_buffer.cpp
    engine.cpp
    application.cpp
    main.cpp
)

# Generate filename with path
foreach(H ${HEADERS})
    list(APPEND ALL_HEADERS ${INC_DIR}/${H})
endforeach() 
foreach(S ${SRCS})
    list(APPEND ALL_SRCS ${SRC_DIR}/${S})
endforeach()

# Create library
# add_library(${PROJECT_NAME} STATIC ${ALL_SRCS} ${ALL_HEADERS} ${STB_INCLUDE_DIRS})
add_executable(${PROJECT_NAME} ${ALL_SRCS} ${ALL_HEADERS})

# Set C++17 feature
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)

# Add library
target_link_libraries(${PROJECT_NAME} PRIVATE plog::plog glfw glad::glad glm::glm)

# Set include directory for compilation
target_include_directories(${PROJECT_NAME} PUBLIC
        ${PROJECT_SOURCE_DIR}/include)

# Set include directory for clients
target_include_directories(${PROJECT_NAME} PUBLIC
    $<BUILD_INTERFACE:${INC_DIR}/${PROJECT_NAME}>
    $<INSTALL_INTERFACE:include/${PROJECT_NAME}>
    PRIVATE src)

# Add tests
# add_subdirectory(samples)