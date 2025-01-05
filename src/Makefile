CC = gcc
CFLAGS = -Wall -Wextra -g -lm

TARGET = lorenz.elf

SRCS = main.c lorenz.c gnuplot_i.c
OBJS = $(SRCS:.c=.o)

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS) $(CFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
