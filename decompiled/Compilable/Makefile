# Makefile for Decompiled Compilable Legacy C Suite
# Compiles all 46 authentic disassembled C translation units into a static library and test harness.

CC ?= gcc
AR ?= ar
CFLAGS ?= -std=c11 -O2 -Wall -Wextra -Wno-unused-parameter -Wno-unused-variable -Wno-int-conversion -Wno-incompatible-pointer-types -Iinclude
LDFLAGS ?= -lz

BUILD_DIR ?= build
OBJ_DIR = $(BUILD_DIR)/obj

# All compilable translation units
SRCS = $(wildcard app/*.c) \
       $(wildcard audio/*.c) \
       $(wildcard core/*.c) \
       $(wildcard data/*.c) \
       $(wildcard gameplay/*.c) \
       $(wildcard graphics/*.c) \
       $(wildcard net/*.c)

OBJS = $(patsubst %.c, $(OBJ_DIR)/%.o, $(SRCS))

LIB_TARGET = $(BUILD_DIR)/liblf2_legacy.a
TEST_TARGET = $(BUILD_DIR)/test_legacy.exe

ifeq ($(OS),Windows_NT)
    ifneq ($(wildcard C:/msys64/usr/bin/rm.exe),)
        RM = C:/msys64/usr/bin/rm.exe -rf
    else
        RM = cmd /c "if exist $(subst /,\,$(BUILD_DIR)) rmdir /s /q $(subst /,\,$(BUILD_DIR))"
    endif
define MKDIR_OBJ
	@if not exist "$(@D)" mkdir "$(@D)"
endef
define NOTICE_DATA
	@if not exist "$(BUILD_DIR)\data" if not exist "..\..\build\data" if not exist "..\..\data" ( \
		echo. && \
		echo ====================================================================== && \
		echo [LF2 NOTICE] Authentic game assets missing in '$(BUILD_DIR)'! && \
		echo Place 'data\', 'bg\', and 'sprite\' folders into '$(BUILD_DIR)' or root. && \
		echo ====================================================================== && \
		echo. \
	)
endef
else
    RM ?= rm -rf
define MKDIR_OBJ
	@mkdir -p "$(@D)"
endef
define NOTICE_DATA
	@if [ ! -d "$(BUILD_DIR)/data" ] && [ ! -d "../../build/data" ] && [ ! -d "../../data" ]; then \
		echo ""; \
		echo "======================================================================"; \
		echo "[LF2 NOTICE] Authentic game assets missing in '$(BUILD_DIR)'!"; \
		echo "Place 'data/', 'bg/', and 'sprite/' folders into '$(BUILD_DIR)' or root."; \
		echo "======================================================================"; \
		echo ""; \
	fi
endef
endif

.PHONY: all check_resources test clean

all: check_resources $(LIB_TARGET) $(TEST_TARGET)

check_resources:
	$(NOTICE_DATA)

$(LIB_TARGET): $(OBJS)
	@echo [AR] Creating legacy static library $@...
	@$(AR) rcs $@ $(OBJS)

$(OBJ_DIR)/%.o: %.c
	$(MKDIR_OBJ)
	@echo [CC] $<
	@$(CC) $(CFLAGS) -c $< -o $@

$(TEST_TARGET): test_legacy.c $(LIB_TARGET)
	@echo [LD] Building decompiled suite test harness $@...
	@$(CC) $(CFLAGS) test_legacy.c -L$(BUILD_DIR) -llf2_legacy $(LDFLAGS) -o $@

test: $(TEST_TARGET)
	@echo ======================================================================
	@echo  Running Decompiled Compilable Test Suite...
	@echo ======================================================================
	./$(TEST_TARGET)

clean:
	@echo [CLEAN] Removing $(BUILD_DIR)...
	@$(RM)
