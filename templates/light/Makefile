MY_SOURCES=main.cpp

CXX=g++
FLAGS=-std=c++11 -O3 -pthread
LIBS=-lgflags -lglog -lsfml-system -lsfml-window -lsfml-graphics -lsfml-network -lsfml-audio -lsfgui
INC=-I .

SOURCES_COMMUNICATION=$(wildcard c24/communication/*.cpp)
OBJECTS_COMMUNICATION=$(patsubst c24/communication/%.cpp, %.o, $(SOURCES_COMMUNICATION))
SOURCES_TOOLBAR=$(wildcard c24/toolbar/*.cpp)
OBJECTS_TOOLBAR=$(patsubst c24/toolbar/%.cpp, %.o, $(SOURCES_TOOLBAR))

default: __PROJECT_NAME__

$(OBJECTS_COMMUNICATION): %.o : c24/communication/%.cpp
	$(CXX) $(FLAGS) $(SOURCES_COMMUNICATION) $(INC) -c

$(OBJECTS_TOOLBAR): %.o : c24/toolbar/%.cpp
	$(CXX) $(FLAGS) $(SOURCES_TOOLBAR) $(INC) -c

__PROJECT_NAME__: $(OBJECTS_COMMUNICATION) $(OBJECTS_TOOLBAR) $(MY_SOURCES)
	$(CXX) $(FLAGS) $(MY_SOURCES) $(OBJECTS_COMMUNICATION) $(OBJECTS_TOOLBAR) $(INC) -o __PROJECT_NAME__ $(LIBS)

clean:
	rm -f *.o __PROJECT_NAME__
