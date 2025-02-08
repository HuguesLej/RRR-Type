cmake_minimum_required(VERSION 3.15)



# -------------------- Project configuration --------------------

project(rrr-type LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

set(SERVER ${PROJECT_NAME}_server)
set(CLIENT ${PROJECT_NAME}_client)
set(GAME_ENGINE GameEngine)
set(NETWORK Network)

if(WIN32)
    add_definitions(-D_WIN32_WINNT=0x0A00)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif()

# Set warning flags for GCC and Clang
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Set warning flags for MSVC
if(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    add_compile_options(/W4)
endif()

set(CMAKE_BUILD_TYPE Debug)



# -------------------- Utility functions --------------------

# Return a list containing a given directory and all its subdirectories (recursive)
function(collect_subdirectories RESULT CUR_DIR)
    file(GLOB CHILDREN ${CUR_DIR}/*)
    set(DIR_LIST ${CUR_DIR})
    foreach(CHILD ${CHILDREN})
        if(IS_DIRECTORY ${CHILD})
            collect_subdirectories(SUBDIR_LIST ${CHILD})
            list(APPEND DIR_LIST ${SUBDIR_LIST})
        endif()
    endforeach()
    set(${RESULT} ${DIR_LIST} PARENT_SCOPE)
endfunction()



# -------------------- vcpkg configuration --------------------

# Find dependencies provided by vcpkg
find_package(SFML CONFIG REQUIRED COMPONENTS system window graphics audio network)
find_package(asio CONFIG REQUIRED)



# -------------------- Network library compilation --------------------

# Find all network source files
file(GLOB_RECURSE NETWORK_SRC
    ${CMAKE_SOURCE_DIR}/Network/src/*.cpp
)

# Find all network include directories
collect_subdirectories(NETWORK_INC_DIRS ${CMAKE_SOURCE_DIR}/Network/include)

# Add network library
add_library(${NETWORK} SHARED ${NETWORK_SRC})

# Include directories for the network library
target_include_directories(${NETWORK} PUBLIC
    ${NETWORK_INC_DIRS}
)

# Link Asio library to the network library
target_link_libraries(${NETWORK} PUBLIC asio::asio)

# Link against the Windows Sockets library for networking
if(WIN32)
    target_link_libraries(${NETWORK} PUBLIC ws2_32)
endif()



# -------------------- Game engine library compilation --------------------

# Find all game engine source files
file(GLOB_RECURSE GAME_ENGINE_SRC
    ${CMAKE_SOURCE_DIR}/GameEngine/src/*.cpp
)

# Find all game engine include directories
collect_subdirectories(GAME_ENGINE_INC_DIRS ${CMAKE_SOURCE_DIR}/GameEngine/include)

# Add game engine library
add_library(${GAME_ENGINE} SHARED ${GAME_ENGINE_SRC})

# Include directories for the game engine library
target_include_directories(${GAME_ENGINE} PUBLIC
    ${GAME_ENGINE_INC_DIRS}
)

# Link SFML and network library to the game engine library
target_link_libraries(${GAME_ENGINE} PUBLIC ${NETWORK} sfml-system sfml-network sfml-graphics sfml-window)



# -------------------- Server compilation and linking --------------------

# Find all server source files
file(GLOB_RECURSE SERVER_SRC
    ${CMAKE_SOURCE_DIR}/Game/serverMain.cpp
)

# Add server executable
add_executable(${SERVER} ${SERVER_SRC})

# Link game engine and network libraries to the server
target_link_libraries(${SERVER} PRIVATE ${GAME_ENGINE} ${NETWORK})



# -------------------- Client compilation and linking --------------------

# Find all client source files
file(GLOB_RECURSE CLIENT_SRC
    ${CMAKE_SOURCE_DIR}/Game/clientMain*.cpp
)

# Add client executable
add_executable(${CLIENT} ${CLIENT_SRC})

# Link game engine and network libraries to the client
target_link_libraries(${CLIENT} PRIVATE ${GAME_ENGINE} ${NETWORK})



# -------------------- Custom commands --------------------

# Build network library
add_custom_target(network
    COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target ${NETWORK}
    DEPENDS ${NETWORK}
)

# Build game engine library
add_custom_target(game_engine
    COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target ${GAME_ENGINE}
    DEPENDS ${GAME_ENGINE}
)

# Build server executable
add_custom_target(server
    COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target ${SERVER}
    DEPENDS ${SERVER}
)

# Build client executable
add_custom_target(client
    COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target ${CLIENT}
    DEPENDS ${CLIENT}
)

# Custom target to clean and rebuild
add_custom_target(re
    COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target clean
    COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target all
)