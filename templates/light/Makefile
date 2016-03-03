MY_SOURCES=main.cpp

CXX=g++
FLAGS=-std=c++11 -O3
LIBS=-pthread -L/usr/local/lib -lgflags -lglog -lsfml-system -lsfml-window -lsfml-graphics -lsfml-network -lsfml-audio -lsfgui
INC=-I .

SOURCES_COMMUNICATION=$(wildcard c24/communication/*.cpp)
OBJECTS_COMMUNICATION=$(patsubst c24/communication/%.cpp, build/%.o, $(SOURCES_COMMUNICATION))
SOURCES_TOOLBAR=$(wildcard c24/toolbar/*.cpp)
OBJECTS_TOOLBAR=$(patsubst c24/toolbar/%.cpp, build/%.o, $(SOURCES_TOOLBAR))

default: __PROJECT_NAME__

$(OBJECTS_COMMUNICATION): build/%.o : c24/communication/%.cpp
	$(CXX) $(FLAGS) -c $< $(INC) -o $@

$(OBJECTS_TOOLBAR): build/%.o : c24/toolbar/%.cpp
	$(CXX) $(FLAGS) -c $< $(INC) -o $@

__PROJECT_NAME__: $(OBJECTS_COMMUNICATION) $(OBJECTS_TOOLBAR) $(MY_SOURCES)
	$(CXX) $(FLAGS) $(MY_SOURCES) $(OBJECTS_COMMUNICATION) $(OBJECTS_TOOLBAR) $(INC) -o __PROJECT_NAME__ $(LIBS)

clean:
	rm -f build/*.o __PROJECT_NAME__
