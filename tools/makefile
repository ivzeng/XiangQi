CXX=g++
CXXFLAGS=-g -Wall -O3 -MMD
CPPFLAGS=
SRC_DIRECTORY= ../src/
EXEC_DIRECTORY = ../
SRC = $(wildcard ${SRC_DIRECTORY}*.cpp)
OBJECTS = $(SRC:.cpp=.o)
DEPENDS = $(SRC:.cpp=.d)
EXEC = 中国象棋.exe

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${CPPFLAGS} ${OBJECTS} -o "${EXEC_DIRECTORY}${EXEC}"

-include ${DEPENDS}


.PHONY: clean

clean:
	rm ${DEPENDS} ${OBJECTS}