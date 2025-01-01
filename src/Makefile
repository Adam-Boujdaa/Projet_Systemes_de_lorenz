# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -g

# Target executable name
TARGET = lorenz.elf

# Source and object files
SRCS = main.c lorenz.c
OBJS = $(SRCS:.c=.o)

# Default rule to build the executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)


%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@


clean:
	rm -f $(OBJS) $(TARGET)
