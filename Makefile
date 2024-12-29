# Varialbes
CC = gcc
CFLAGS = -Wall -Wextra -Werror
LDFLAGS = -lm
TARGET = main
SRC = main.c

# Default rule to build the target
all: $(TARGET)

# Rule to build the exectuable
$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC) $(LDFLAGS)

# Rule to build the exectuable
debug:
	$(CC) $(CFLAGS) -g -o $(TARGET) $(SRC) $(LDFLAGS)

# Clean up generated files
clean:
	rm -f $(TARGET)

# Phony targets to avoid conflict with file names
.PHONY: all clean
