cmake_minimum_required(VERSION 3.15)
project(EchoClient)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SRC_PATH "../sources")

find_package(Boost REQUIRED)

add_executable(echo_client 
    ${SRC_PATH}/main.cpp
    ${SRC_PATH}/client.cpp
    ${SRC_PATH}/client_session.cpp
    ${SRC_PATH}/connection.cpp
)

target_include_directories(echo_client PRIVATE
    ${Boost_INCLUDE_DIRS}
    include
)
