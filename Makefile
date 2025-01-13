CXX = g++
CXXFLAGS = -Wall -Wextra -pedantic
LDFLAGS = -lncurses
BUILD_DIR = ./build

SOURCES = main.cpp ui/uihandler.cpp
OBJECTS = $(SOURCES:.cpp=.o)

main: $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(BUILD_DIR)/torrential $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(BUILD_DIR)/torrential