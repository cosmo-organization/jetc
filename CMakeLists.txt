cmake_minimum_required(VERSION 3.10)
project(jetc)
include_directories("include" "third-party/asio/asio/include")
add_executable(test "src/test.cpp")
