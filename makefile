CXX = g++
CXXFLAGS = -std=c++14 -Wall
DIRECTORY = src/
OBJECTS = XiangQi.o Interface.o BoardGame.o IO.o Player.o Board.o Item.o Move.o State.o helpers.o
EXEC = exe/XiangQi.exe

${EXEC}: $(addprefix  $(DIRECTORY), $(OBJECTS))
	${CXX} $(addprefix $(DIRECTORY), $(OBJECTS)) ${CXXFLAGS} -o ${EXEC}


.PHONY: clean

clean:
	rm $(addprefix  $(DIRECTORY), $(OBJECTS)) ${EXEC}