INCLUDE := -I.
<<<<<<< Updated upstream
LIBS := -lpthread `pkg-config gtkmm-3.0 --libs` -lgmpxx -lgmp
FLAGS := -g -Wall -Wextra -Wno-unused-parameter --std=c++17 `pkg-config gtkmm-3.0 --cflags`
=======
LIBS :=
FLAGS := -g -Wall -Wextra `pkg-config gtkmm-3.0 --cflags --libs`
>>>>>>> Stashed changes

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
