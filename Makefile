# Compiler and flags
CC = gcc
CFLAGS = -Wall -pthread

# Directories
SRC_DIR = src
INCLUDE_DIR = include
OBJ_DIR = obj
BIN_DIR = bin

# Source files
SRCS = $(SRC_DIR)/main.c $(SRC_DIR)/queue.c $(SRC_DIR)/producer.c $(SRC_DIR)/consumer.c

# Object files
OBJS = $(OBJ_DIR)/main.o $(OBJ_DIR)/queue.o $(OBJ_DIR)/producer.o $(OBJ_DIR)/consumer.o

# Output binary
TARGET = $(BIN_DIR)/prod-con

# Include paths
INCLUDES = -I$(INCLUDE_DIR)

# Rules
all: $(TARGET)

$(TARGET): $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

.PHONY: all clean