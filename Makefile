CXX ?= C:/msys64/ucrt64/bin/g++.exe
AR ?= C:/msys64/ucrt64/bin/ar.exe
RM ?= C:/msys64/usr/bin/rm.exe -f

SDL2_DIR ?= third_party/SDL2/x86_64-w64-mingw32
SDL2_INC = -I$(SDL2_DIR)/include -I$(SDL2_DIR)/include/SDL2
SDL2_LIB = -L$(SDL2_DIR)/lib -lmingw32 -lSDL2main -lSDL2

CXXFLAGS ?= -std=c++20 -Wall -Wextra -O2 -I. $(SDL2_INC)

LIB_SRCS = teleport.cpp attack.cpp random.cpp app.cpp cipher.cpp data_txt.cpp dat_loader.cpp background.cpp renderer.cpp
LIB_OBJS = $(LIB_SRCS:.cpp=.o)
TARGET_LIB = liblf2.a

APP_SRCS = main.cpp
APP_OBJS = $(APP_SRCS:.cpp=.o)
TARGET_APP = lf2.exe

TEST_MAP_SRCS = verify_memory_maps.cpp
TEST_MAP_EXE = verify_memory_maps.exe

TEST_DAT_SRCS = test_data_loader.cpp
TEST_DAT_EXE = test_data_loader.exe

TEST_GFX_SRCS = test_graphics.cpp
TEST_GFX_EXE = test_graphics.exe

.PHONY: all test clean

all: $(TARGET_LIB) $(TARGET_APP) $(TEST_MAP_EXE) $(TEST_DAT_EXE) $(TEST_GFX_EXE)

$(TARGET_LIB): $(LIB_OBJS)
	$(AR) rcs $@ $^

$(TARGET_APP): $(APP_OBJS) $(TARGET_LIB)
	$(CXX) $(CXXFLAGS) $(APP_OBJS) -L. -llf2 $(SDL2_LIB) -o $@

$(TEST_MAP_EXE): $(TEST_MAP_SRCS) $(TARGET_LIB)
	$(CXX) $(CXXFLAGS) $(TEST_MAP_SRCS) -L. -llf2 -o $@

$(TEST_DAT_EXE): $(TEST_DAT_SRCS) $(TARGET_LIB)
	$(CXX) $(CXXFLAGS) $(TEST_DAT_SRCS) -L. -llf2 -o $@

$(TEST_GFX_EXE): $(TEST_GFX_SRCS) $(TARGET_LIB)
	$(CXX) $(CXXFLAGS) $(TEST_GFX_SRCS) -L. -llf2 $(SDL2_LIB) -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

test: $(TEST_MAP_EXE) $(TEST_DAT_EXE) $(TEST_GFX_EXE) $(TARGET_APP)
	./$(TEST_MAP_EXE)
	./$(TEST_DAT_EXE)
	./$(TEST_GFX_EXE)
	./$(TARGET_APP) --test --frames 30

clean:
	$(RM) $(LIB_OBJS) $(APP_OBJS) $(TARGET_LIB) $(TARGET_APP) $(TEST_MAP_EXE) $(TEST_DAT_EXE) $(TEST_GFX_EXE)
