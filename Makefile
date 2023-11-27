SRC_DIR = src
# BUILD_DIR = build/debug
BUILD_DIR = build/
CC = gcc
# SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
SRC_FILES = $(SRC_DIR)/main.c
OBJ_NAME = gui
# INCLUDE_PATHS = -Iinclude
# LIBRARY_PATHS = -Llib
COMPILER_FLAGS = -std=c11 -Wall -O0 -g -pedantic
LINKER_FLAGS = -lsdl2 -lSDL2_ttf 

all:
	$(CC) $(COMPILER_FLAGS) $(LINKER_FLAGS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(SRC_FILES) -o $(BUILD_DIR)/$(OBJ_NAME)

# # Install
# BIN = demo

# # Flags
# # CFLAGS += -std=c89 -pedantic -O0
# CFLAGS += -std=c11 -pedantic -O0
# CFLAGS += `sdl2-config --cflags`

# SRC = main.c
# OBJ = $(SRC:.c=.o)

# ifeq ($(OS),Windows_NT)
# #TODO
# #BIN := $(BIN).exe
# #LIBS = -lmingw32 -lSDL2main -lSDL2 -lopengl32 -lm -lGLU32
# else
# 	UNAME_S := $(shell uname -s)
# 	ifeq ($(UNAME_S),Darwin)
# #TODO		LIBS = -lSDL2 -framework OpenGL -lm
#         LIBS = -lSDL2
# 	else
# 		LIBS += -lm -ldl `sdl2-config --libs`
# 	endif
# endif

# $(BIN):
# 	@mkdir -p bin
# 	rm -f bin/$(BIN) $(OBJS)
# 	$(CC) $(SRC) $(CFLAGS) -o bin/$(BIN) $(LIBS)
