CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
project(ekshell)
ADD_SUBDIRECTORY(googletest)

set(CMAKE_CXX_STANDARD 11)

ADD_EXECUTABLE(test
	unit_tests/test.cpp
)

ADD_EXECUTABLE(shell
		src/shell.cpp
)
TARGET_LINK_LIBRARIES(test gtest)
TARGET_COMPILE_DEFINITIONS(test PRIVATE gtest_disable_pthreads=ON)



