cmake_minimum_required(VERSION 3.27)

project(sylar)

include(cmake/util.cmake)

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_FLAGS "$ENV{CXXFLAGS} -rdynamic -O0 -g -std=c++11 -Wall -Wno-deprecated -Werror -Wno-unused-function -Wno-builtin-macro-redefined")

set(LIB_SRC
        sylar/log.cc
        sylar/util.cc
        sylar/config.cc
)

add_library(sylar SHARED ${LIB_SRC})
# 调用函数来为库目标定义 __FILE__ 宏
define_file_macro_for_sources(sylar)

# add_library(sylar_static STATIC ${LIB_SRC})
# SET_TARGET_PROPERRIES (sylar_static PROPERTIES OUTPUT_NAME "sylar")

add_executable(test tests/test.cc)
add_dependencies(test sylar)
define_file_macro_for_sources(test)
target_link_libraries(test sylar)

add_executable(test_config tests/test_config.cc)
add_dependencies(test_config sylar)
define_file_macro_for_sources(test_config)
target_link_libraries(test_config sylar yaml-cpp)

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
