CXX = g++
CXXFLAGS = -std=c++14 -Wall -O3
DIRECTORY = ../../src/
OBJECTS = XiangQi.o Interface.o BoardGame.o IO.o Player.o Board.o Item.o Move.o State.o Texts.o helpers.o
EXEC = 中国象棋.exe

${EXEC}: $(addprefix  $(DIRECTORY), $(OBJECTS))
	${CXX} $(addprefix $(DIRECTORY), $(OBJECTS)) ${CXXFLAGS} -o ${EXEC}


.PHONY: clean

clean:
	rm $(addprefix  $(DIRECTORY), $(OBJECTS))