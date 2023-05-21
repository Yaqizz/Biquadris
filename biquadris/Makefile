CXX = g++
CXXFLAGS = -std=c++14 -Wall -O -g -MMD -Werror=vla -I/usr/X11/include
SOURCES = $(wildcard *.cc)
OBJECTS = ${SOURCES:.cc=.o}
DEPENDS = ${OBJECTS:.o=.d}
EXEC = biquadris

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} -lX11 -L/usr/X11/lib

%.o: %.cc
	$(CXX) -c -o $@ $< $(CXXFLAGS)

-include ${DEPENDS}

.PHONY: clean

clean: 
	rm -f ${OBJECTS} ${DEPENDS} ${EXEC}
