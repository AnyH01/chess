PROGRAM=havlaane
CC=g++
CFLAGS= -std=c++17 -pedantic -Wall -fsanitize=address -g

SRCDIR = src

SRC = $(shell find $(SRCDIR)/ -type f -name '*.cpp')
OBJ = $(patsubst $(SRCDIR)/%.cpp,$(SRCDIR)/%.o,$(SRC))
HDR = $(shell find $(SRCDIR)/ -type f -name '*.h')

all:compile doc run

compile: $(PROGRAM)

run:
	./$(PROGRAM)

doc: $(SRC) $(HDR) Doxyfile
	doxygen

clean:
	rm -f $(PROGRAM)
	rm -f $(SRCDIR)/*.o
	rm -rf doc

$(PROGRAM): $(OBJ)
	$(CC) $^ -o $@

$(OBJDIR)/%.o : $(SRCDIR)/%.cpp $(HDR)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@e