CXX = g++-5
CXXFLAGS = -std=c++14 -Wall -MMD
CXXX11 = -lX11
EXEC = watopoly
OBJECTS = main.o auction.o AB.o Residence.o Gym.o gameboard.o player.o Dice.o cell.o coopfee.o dctimsline.o goose.o gotoTims.o nh.o osap.o property.o slc.o tuition.o window.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} ${CXXX11} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
