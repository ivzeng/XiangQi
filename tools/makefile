CXX=g++
CXXFLAGS=-Wall -O3
CPPFLAGS=
SRC_DIRECTORY= ../src/
EXEC_DIRECTORY = ../
OBJECTS = XiangQi.o Interface.o BoardGame.o IO.o Player.o Board.o Item.o Move.o State.o Texts.o helpers.o
EXEC = 中国象棋.exe

${EXEC}: $(addprefix  ${SRC_DIRECTORY}, ${OBJECTS})
	${CXX} $(addprefix ${SRC_DIRECTORY}, ${OBJECTS}) ${CXXFLAGS} ${CPPFLAGS} -o "${EXEC_DIRECTORY}${EXEC}"


.PHONY: clean

clean:
	rm $(addprefix  ${SRC_DIRECTORY}, ${OBJECTS})