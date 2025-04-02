# Authors: Preston
# References: Google, youtube

# Compiler and flags
CC = gcc
CFLAGS = -Wall -ansi

# List of source files
SRC_FILES = mainFolder/main.c mainFolder/player.c slots/slots.c


# Output executable
TARGET = finalpro

# Rule to build the target
final:
	$(CC) $(SRC_FILES) -o $(TARGET)

# Clean rule to remove the executable
clean:
	rm -f $(TARGET)