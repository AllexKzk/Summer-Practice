INCLUDE := -I.
LIBS := -lpthread
FLAGS := -g -Wall -Wextra -std=c++2a

SRC := $(shell find . -name "*.cpp")
OBJ := $(addsuffix .o,$(basename $(SRC)))
BIN := ga

all: $(BIN)

clean:
	rm $(OBJ)
	rm $(BIN)

$(BIN): $(OBJ)
	g++ $(OBJ) $(LIBS) $(FLAGS) -o $(BIN)

%.o: %.cpp
	g++ -c $(INCLUDE) $(FLAGS) $< -o $@
