cmake_minimum_required(VERSION 3.17)
project(ParallelSort)

set(CMAKE_CXX_STANDARD 20)

add_executable(ParallelSort main.cpp TaskQueue/TaskQueue.h QueueHandler/QueueHandler.h FileReader/Reader.h)