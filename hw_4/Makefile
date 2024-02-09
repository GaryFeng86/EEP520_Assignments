# Compiler
CC := g++ -std=c++17

# Directories
SRCDIR := .
BUILDDIR := ./build
TARGETDIR := ./bin

# Files
HEADERS := $(wildcard *.h)
SOURCES := $(wildcard *.cc)
OBJECTS := $(patsubst %.cc, $(BUILDDIR)/%.o, $(notdir $(SOURCES)))
TARGET := main

# Flags and libraries
CFLAGS := -ggdb
LIB := -lgtest -lpthread

# Default rule
all: directories $(TARGETDIR)/$(TARGET)

# Create necessary directories
directories:
	@mkdir -p $(TARGETDIR)
	@mkdir -p $(BUILDDIR)

# Linking
$(TARGETDIR)/$(TARGET): $(OBJECTS) $(HEADERS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIB)

# Compilation
$(BUILDDIR)/%.o: $(SRCDIR)/%.cc $(HEADERS)
	$(CC) $(CFLAGS) -c -o $@ $<

# Clean
clean:
	@$(RM) -rf $(BUILDDIR)/*.o

# Full clean
spotless: clean
	@$(RM) -rf $(TARGETDIR)/$(TARGET)

.PHONY: all directories clean spotless
