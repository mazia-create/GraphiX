#compiler and flags

CXX = g++ 
CXXFLAGS= -Wall -std=c++17 #this and CXX tells compiler to use C++17
LDFLAGS= -lsfml-graphics -lsfml-window -lsfml-system #links SFML libraries

#source and object files
SRC = src/main.cpp src/app.cpp src/Plotter.cpp src/Button.cpp src/utils.cpp # lists all .cpp files
OBJ= $(SRC:.cpp=.o) #converts .cpp names to .o names
EXEC= GraphiX

#Default target
all: $(EXEC)

#link object files into executable
$(EXEC) : $(OBJ)
	$(CXX) $(OBJ) -o $@ $(LDFLAGS)

#compile .cpp files into .o files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -Iinclude -c $< -o $@

#clean up build files

clean:
	rm -f $(OBJ) $(EXEC)
