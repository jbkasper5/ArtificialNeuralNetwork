CURR_SRC_DIR=src
CURR_BIN_DIR=bin
CURR_DEBUG_BIN_DIR=$(CURR_BIN_DIR)/debug
MAT_SRC_DIR=../matrixops/src
MAT_BIN_DIR=../matrixops/bin
MAT_DEBUG_BIN_DIR=$(MAT_BIN_DIR)/debug
SRCS=$(shell find $(CURR_SRC_DIR)/*.c) $(shell find $(MAT_SRC_DIR)/*.c)
TOBJS=$(patsubst %.c, %.o, $(SRCS))
OBJS=$(subst src,bin,$(TOBJS))
DOBJS=$(subst bin/,bin/debug/d_, $(OBJS))
DEBUG=-DDEBUG
INCLUDES= -I include/ -I ../matrixops/include/

CC=				gcc
OPT=			-O3
CFLAGS=			-g -std=c11
TARGET=			exe
DTARGET=		d$(TARGET)

all: $(MAT_BIN_DIR) $(CURR_BIN_DIR) $(TARGET)

.PHONY: re
re: clean all

.PHONY: debug
debug: $(CURR_DEBUG_BIN_DIR) $(MAT_DEBUG_BIN_DIR) $(DTARGET)

$(TARGET): $(OBJS)
	$(CC) $^ -o $@ $(CFLAGS) $(INCLUDES)

$(DTARGET): $(DOBJS)
	$(CC) $^ -o $@ $(CFLAGS) $(INCLUDES)

$(CURR_BIN_DIR)/%.o: $(CURR_SRC_DIR)/%.c
	$(CC) -c $< -o $@ $(CFLAGS) $(INCLUDES)

$(MAT_BIN_DIR)/%.o: $(MAT_SRC_DIR)/%.c
	$(CC) -c $< -o $@ $(CFLAGS) $(INCLUDES)

$(CURR_DEBUG_BIN_DIR)/d_%.o: $(CURR_SRC_DIR)/%.c
	$(CC) -c $< -o $@ $(CFLAGS) $(DEBUG) $(INCLUDES)

$(MAT_DEBUG_BIN_DIR)/d_%.o: $(MAT_SRC_DIR)/%.c
	$(CC) -c $< -o $@ $(CFLAGS) $(DEBUG) $(INCLUDES)

$(CURR_BIN_DIR) $(MAT_BIN_DIR) $(CURR_DEBUG_BIN_DIR) $(MAT_DEBUG_BIN_DIR):
	mkdir -p $@

.PHONY: clean
clean:
	$(RM) -rf $(TARGET)
	$(RM) -rf $(DTARGET)
	$(RM) -rf $(CURR_BIN_DIR)
	$(RM) -rf $(MAT_BIN_DIR)