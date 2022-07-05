INCLUDE := -I.
LIBS := -lpthread `pkg-config gtkmm-3.0 --libs`
FLAGS := -g -Wall -Wextra `pkg-config gtkmm-3.0 --cflags`

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
