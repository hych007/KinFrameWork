cmake_minimum_required(VERSION 3.12)
project(KinBase)

set(CMAKE_CXX_STANDARD 17)

find_path(KinCommonPath KinCommonSetting.cmake)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${KinCommonPath})
include(KinCommonSetting)

find_package(spdlog)
find_package(KinBoost)
find_package(catch2)

add_subdirectory(Source)