CC = gcc
CFLAGS= -w -ggdb
LINKER_FLAGS = -lSDL2 
BIN = ./bin

# gets list of .c files, then removes the extension
SRC := $(basename $(wildcard *.c))
# dependencies every file here needs
DEP := lazyfoo.h $(BIN)/functions.o | $(BIN)
# files that need the img library
SPEC_SRC = 06loadPNG 07texLoad
# list of files to not attempt to build 
SRCIGNORE := functions special

.PHONY = clean all

# removes the files defined to be ignored, then adds the bin folder to them
all: $(addprefix $(BIN)/, $(filter-out $(SRCIGNORE), $(SRC))) 

# binaries that compile with the additional image lib
$(addprefix $(BIN)/, $(SPEC_SRC)): $(BIN)/%: %.c $(BIN)/special.o $(DEP)
	$(CC) $(CFLAGS) $(LINKER_FLAGS) -lSDL2_image -o $@ $< $(BIN)/functions.o $(BIN)/special.o

# recompiles the special function object
$(BIN)/special.o: special.c lazyfoo.h | $(BIN)
	$(CC) -c $(CFLAGS) $(LINKER_FLAGS) -lSDL2_image -o $@ $<

# general rule for binaries
$(BIN)/%: %.c lazyfoo.h $(DEP)
	$(CC) $(CFLAGS) $(LINKER_FLAGS) -o $@ $< $(BIN)/functions.o

# general incase i need to add more objects?
$(BIN)/%.o: %.c lazyfoo.h | $(BIN)
	$(CC) -c $(CFLAGS) $(LINKER_FLAGS) -o $@ $<


# cleanup and remaki
$(BIN):
	mkdir -p $@
	
clean:
	@$(RM) -rv $(BIN)
