CXX= g++
CXXFLAGS= -Wall -std=c++11 -g -lsfml-graphics -lsfml-window -lsfml-system
EXEC= maze
SRC= *.cpp 
OBJ= $(SRC:.c=.o)

$(EXEC): $(OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@

%.o: %.cpp %.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf *.o

mrproper: clean
	rm -rf $(EXEC)
