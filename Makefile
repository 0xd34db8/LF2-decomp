CXX ?= C:/msys64/ucrt64/bin/g++.exe
AR ?= C:/msys64/ucrt64/bin/ar.exe
RM = C:/msys64/usr/bin/rm.exe -f

SDL2_DIR ?= third_party/SDL2/x86_64-w64-mingw32
SDL2_INC = -I$(SDL2_DIR)/include -I$(SDL2_DIR)/include/SDL2
SDL2_LIB = -L$(SDL2_DIR)/lib -lmingw32 -lSDL2main -lSDL2

INCLUDES = -Isrc -Isrc/core -Isrc/gameplay -Isrc/data -Isrc/graphics -Isrc/app -I. $(SDL2_INC)
CXXFLAGS ?= -std=c++20 -Wall -Wextra -O2 -MMD -MP $(INCLUDES)

LIB_SRCS = \
	src/core/random.cpp \
	src/gameplay/teleport.cpp \
	src/gameplay/attack.cpp \
	src/gameplay/entity.cpp \
	src/gameplay/grapple.cpp \
	src/gameplay/weapon.cpp \
	src/gameplay/ai.cpp \
	src/data/cipher.cpp \
	src/data/data_txt.cpp \
	src/data/dat_loader.cpp \
	src/graphics/background.cpp \
	src/graphics/renderer.cpp \
	src/app/app.cpp

LIB_OBJS = $(LIB_SRCS:.cpp=.o)
TARGET_LIB = liblf2.a

APP_SRCS = src/app/main.cpp
APP_OBJS = $(APP_SRCS:.cpp=.o)
TARGET_APP = lf2.exe

TEST_MAP_SRCS = tests/verify_memory_maps.cpp
TEST_MAP_EXE = verify_memory_maps.exe

TEST_DAT_SRCS = tests/test_data_loader.cpp
TEST_DAT_EXE = test_data_loader.exe

TEST_GFX_SRCS = tests/test_graphics.cpp
TEST_GFX_EXE = test_graphics.exe

TEST_ENT_SRCS = tests/test_entity_physics.cpp
TEST_ENT_EXE = test_entity_physics.exe

TEST_CBT_SRCS = tests/test_combat_system.cpp
TEST_CBT_EXE = test_combat_system.exe

TEST_GRP_SRCS = tests/test_grapple_weapon.cpp
TEST_GRP_EXE = test_grapple_weapon.exe

TEST_AI_SRCS = tests/test_ai_controller.cpp
TEST_AI_EXE = test_ai_controller.exe

TEST_EXES = $(TEST_MAP_EXE) $(TEST_DAT_EXE) $(TEST_GFX_EXE) $(TEST_ENT_EXE) $(TEST_CBT_EXE) $(TEST_GRP_EXE) $(TEST_AI_EXE)

.PHONY: all test clean

all: $(TARGET_LIB) $(TARGET_APP) $(TEST_EXES)

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

$(TEST_ENT_EXE): $(TEST_ENT_SRCS) $(TARGET_LIB)
	$(CXX) $(CXXFLAGS) $(TEST_ENT_SRCS) -L. -llf2 -o $@

$(TEST_CBT_EXE): $(TEST_CBT_SRCS) $(TARGET_LIB)
	$(CXX) $(CXXFLAGS) $(TEST_CBT_SRCS) -L. -llf2 -o $@

$(TEST_GRP_EXE): $(TEST_GRP_SRCS) $(TARGET_LIB)
	$(CXX) $(CXXFLAGS) $(TEST_GRP_SRCS) -L. -llf2 -o $@

$(TEST_AI_EXE): $(TEST_AI_SRCS) $(TARGET_LIB)
	$(CXX) $(CXXFLAGS) $(TEST_AI_SRCS) -L. -llf2 -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

-include $(LIB_OBJS:.o=.d) $(APP_OBJS:.o=.d)

test: $(TEST_EXES) $(TARGET_APP)
	./$(TEST_MAP_EXE)
	./$(TEST_DAT_EXE)
	./$(TEST_GFX_EXE)
	./$(TEST_ENT_EXE)
	./$(TEST_CBT_EXE)
	./$(TEST_GRP_EXE)
	./$(TEST_AI_EXE)
	./$(TARGET_APP) --test --frames 30

clean:
	$(RM) $(LIB_OBJS) $(APP_OBJS) $(LIB_OBJS:.o=.d) $(APP_OBJS:.o=.d) $(TARGET_LIB) $(TARGET_APP) $(TEST_EXES)
