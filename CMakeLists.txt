cmake_minimum_required(VERSION 3.15)



# -------------------- Project configuration --------------------

project(rrr-type LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

set(SERVER ${PROJECT_NAME}_server)
set(CLIENT ${PROJECT_NAME}_client)
set(GAME_ENGINE GameEngine)

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



# -------------------- Game engine library compilation --------------------

# Find all game engine source files
file(GLOB_RECURSE GAME_ENGINE_SRC
    ${CMAKE_SOURCE_DIR}/GameEngine/src/*.cpp
)

# Find all game engine include directories
collect_subdirectories(GAME_ENGINE_INC_DIRS ${CMAKE_SOURCE_DIR}/GameEngine/include)

# Add game engine library
add_library(${GAME_ENGINE} SHARED ${GAME_ENGINE_SRC})

# # Include directories for the game engine library
target_include_directories(${GAME_ENGINE} PUBLIC
    ${GAME_ENGINE_INC_DIRS}
)

# Link SFML libraries to the game engine library
target_link_libraries(${GAME_ENGINE} PRIVATE sfml-system sfml-network sfml-graphics sfml-window)



# # -------------------- Server compilation and linking --------------------

# # Find all server source files
# file(GLOB_RECURSE SERVER_SRC
#     # Add your server source files here. GLOB_RECURSE will search for files
#     # recursively so you don't need to list each subdirectory.
#     # For example:
#     # ${CMAKE_SOURCE_DIR}/network/*.cpp
#     ${CMAKE_SOURCE_DIR}/Server/*.cpp
#     ${CMAKE_SOURCE_DIR}/lib/Network/*.cpp
#     ${CMAKE_SOURCE_DIR}/Utils/*.cpp
# )

# list(REMOVE_ITEM SERVER_SRC ${CMAKE_SOURCE_DIR}/Network/factory/PacketDeserializerClient.cpp)
# list(REMOVE_ITEM SERVER_SRC ${CMAKE_SOURCE_DIR}/Server/ECS/RType.cpp)

# # Add server executable
# add_executable(${SERVER} ${SERVER_SRC})

# # Link Asio and LZ4 libraries for the server
# target_link_libraries(${SERVER} PRIVATE asio::asio)
# target_link_libraries(${SERVER} PRIVATE lz4::lz4)

# # Link the game engine library to the server
# target_link_libraries(${SERVER} PRIVATE ${GAME_ENGINE})

# if(WIN32)
#     # Link against the Windows Sockets library for networking
#     target_link_libraries(${SERVER} PRIVATE ws2_32)
# endif()



# Temp compilation
add_executable(test main.cpp)
target_link_libraries(test PRIVATE ${GAME_ENGINE} sfml-system sfml-network sfml-graphics sfml-window)



# # -------------------- Client compilation and linking --------------------

# # Find all client source files
# file(GLOB_RECURSE CLIENT_SRC
#     # Add your client source files here. GLOB_RECURSE will search for files
#     # recursively so you don't need to list each subdirectory.
#     # For example:
#     # ${CMAKE_SOURCE_DIR}/network/*.cpp
#     ${CMAKE_SOURCE_DIR}/Client/*.cpp
#     ${CMAKE_SOURCE_DIR}/lib/Network/*.cpp
#     ${CMAKE_SOURCE_DIR}/Utils/*.cpp
# )

# list(REMOVE_ITEM CLIENT_SRC ${CMAKE_SOURCE_DIR}/Network/factory/PacketDeserializerServer.cpp)

# # Add client executable
# add_executable(${CLIENT} ${CLIENT_SRC})

# # Link SFML, Asio and lz4 libraries for the client
# target_link_libraries(${CLIENT} PRIVATE sfml-system sfml-network sfml-graphics sfml-window)
# target_link_libraries(${CLIENT} PRIVATE asio::asio)
# target_link_libraries(${CLIENT} PRIVATE lz4::lz4)

# # Link the game engine library to the client
# target_link_libraries(${CLIENT} PRIVATE ${GAME_ENGINE})

# if(WIN32)
#     # Link against the Windows Sockets library for networking
#     target_link_libraries(${CLIENT} PRIVATE ws2_32)
# endif()



# -------------------- Custom commands --------------------

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