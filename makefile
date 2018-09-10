# Declaration of variables
CC = g++
CC_FLAGS = -Wall -lGL -lGLU -lglut

# File names
EXEC = moteurJeu 
SOURCES = $(wildcard *.cpp)
OBJECTS = $(SOURCES:.cpp=.o)

# Main target
$(EXEC): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(EXEC) $(CC_FLAGS)

# To obtain object files
%.o: %.cpp %.h
	$(CC) -c $(CC_FLAGS) $< -o $@

# To remove generated files
clean:
	rm -f $(EXEC) $(OBJECTS)
