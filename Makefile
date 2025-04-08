CC = gcc
CFLAGS = -Wall -Wextra -Iinclude
SRC_DIR = src
OBJ_DIR = obj
BIN = quiz_system.exe

SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

.PHONY: all clean run

all: $(BIN)

$(BIN): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@if not exist $(OBJ_DIR) mkdir $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@if exist $(BIN) del /Q /F $(BIN)
	@if exist $(OBJ_DIR) rmdir /S /Q $(OBJ_DIR)
	@if exist student_data.txt del /Q /F student_data.txt
	@if exist student_progress.dat del /Q /F student_progress.dat

run: $(BIN)
	$(BIN)
