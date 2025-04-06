CC = gcc
CFLAGS = -Wall -Wextra -g -pthread
TARGET = producer_consumer

SRC_FILES = \
    main.c \
    generate_requests.c \
    print.c

OBJ_FILES = $(SRC_FILES:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJ_FILES)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c alloc.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ_FILES) $(TARGET)

run: $(TARGET)
	./$(TARGET) 10000 1000 4 3  # Example parameters

.PHONY: all clean run