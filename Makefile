CC := gcc
CFLAGS := -Wall -D Debug

LINKER := gcc
LFLAGS := -Wall -ldns_sd

SRC := $(wildcard src/*.c)
INCLUDES := $(wildcard src/*.h)
OBJECTS := $(SRC:src/%.c=bin/%.o)

MAIN := rps.out

all: $(MAIN)

run: $(MAIN)
	./$(MAIN)

$(MAIN): $(OBJECTS)
	$(LINKER) -o $(MAIN) $(LFLAGS) $(OBJECTS)

$(OBJECTS): bin/%.o : src/%.c
	$(CC) $(CFLAGS) -c $< -o $@
	@echo "Compiled "$<" successfully!"

clean:
	$(RM) *.o *~ $(MAIN) $(OBJECTS)

depend: $(SRC)
	makedepend $(INCLUDES) $^

# DO NOT DELETE THIS LINE -- make depend needs it
