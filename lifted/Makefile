CXX ?= g++
AR ?= ar

BUILD_DIR ?= build

SDL2_DIR ?= third_party/SDL2/x86_64-w64-mingw32
SDL2_INC = -I$(SDL2_DIR)/include -I$(SDL2_DIR)/include/SDL2
SDL2_LIB = -L$(SDL2_DIR)/lib -lmingw32 -lSDL2main -lSDL2

INCLUDES = -Isrc -Isrc/core -Isrc/gameplay -Isrc/data -Isrc/graphics -Isrc/app -I. $(SDL2_INC)
CXXFLAGS ?= -std=c++20 -Wall -Wextra -O2 -MMD -MP $(INCLUDES)

ifeq ($(OS),Windows_NT)
    ifneq ($(wildcard C:/msys64/usr/bin/rm.exe),)
        RM = C:/msys64/usr/bin/rm.exe -f
    else
        RM = cmd /c del /Q /F
    endif
define MKDIR_BUILD
	@if not exist "$(BUILD_DIR)" mkdir "$(BUILD_DIR)"
endef
define COPY_SDL_DLL
	@if not exist "$(BUILD_DIR)\SDL2.dll" if exist "$(subst /,\,$(SDL2_DIR)\bin\SDL2.dll)" copy /Y "$(subst /,\,$(SDL2_DIR)\bin\SDL2.dll)" "$(BUILD_DIR)\SDL2.dll" >nul 2>&1 || (exit 0)
endef
define NOTICE_DATA
	@if not exist "$(BUILD_DIR)\data" ( \
		echo. && \
		echo ====================================================================== && \
		echo [LF2 BUILD] Executable successfully compiled: $(TARGET_APP) && \
		echo. && \
		echo [LF2 NOTICE] Authentic game data not detected in '$(BUILD_DIR)'! && \
		echo Please place the Little Fighter 2 data folders into '$(BUILD_DIR)': && \
		echo   - $(BUILD_DIR)\data\ && \
		echo   - $(BUILD_DIR)\bg\ && \
		echo   - $(BUILD_DIR)\sprite\ && \
		echo. && \
		echo You can then run the game with: .\$(TARGET_APP) && \
		echo ====================================================================== && \
		echo. \
	)
endef
else
    RM ?= rm -f
define MKDIR_BUILD
	@mkdir -p "$(BUILD_DIR)"
endef
define COPY_SDL_DLL
	@cp -u $(SDL2_DIR)/bin/SDL2.dll $(BUILD_DIR)/ 2>/dev/null || true
endef
define NOTICE_DATA
	@if [ ! -d "$(BUILD_DIR)/data" ]; then \
		echo ""; \
		echo "======================================================================"; \
		echo "[LF2 BUILD] Executable successfully compiled: $(TARGET_APP)"; \
		echo ""; \
		echo "[LF2 NOTICE] Authentic game data not detected in '$(BUILD_DIR)'!"; \
		echo "Please place the Little Fighter 2 data folders into '$(BUILD_DIR)':"; \
		echo "  - $(BUILD_DIR)/data/"; \
		echo "  - $(BUILD_DIR)/bg/"; \
		echo "  - $(BUILD_DIR)/sprite/"; \
		echo ""; \
		echo "You can then run the game with: ./$(TARGET_APP)"; \
		echo "======================================================================"; \
		echo ""; \
	fi
endef
endif

LIB_SRCS = \
	src/core/random.cpp \
	src/core/replay.cpp \
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
	src/graphics/embedded_ui.cpp \
	src/audio/audio.cpp \
	src/net/network.cpp \
	src/app/menu.cpp \
	src/app/stage.cpp \
	src/app/tournament.cpp \
	src/app/battle.cpp \
	src/app/survival.cpp \
	src/app/options.cpp \
	src/app/app.cpp

LIB_OBJS = $(LIB_SRCS:.cpp=.o)
TARGET_LIB = $(BUILD_DIR)/liblf2.a

APP_SRCS = src/app/main.cpp
APP_OBJS = $(APP_SRCS:.cpp=.o)
TARGET_APP = $(BUILD_DIR)/lf2.exe

TEST_MAP_SRCS = tests/verify_memory_maps.cpp
TEST_MAP_EXE = $(BUILD_DIR)/verify_memory_maps.exe

TEST_DAT_SRCS = tests/test_data_loader.cpp
TEST_DAT_EXE = $(BUILD_DIR)/test_data_loader.exe

TEST_GFX_SRCS = tests/test_graphics.cpp
TEST_GFX_EXE = $(BUILD_DIR)/test_graphics.exe

TEST_ENT_SRCS = tests/test_entity_physics.cpp
TEST_ENT_EXE = $(BUILD_DIR)/test_entity_physics.exe

TEST_CBT_SRCS = tests/test_combat_system.cpp
TEST_CBT_EXE = $(BUILD_DIR)/test_combat_system.exe

TEST_GRP_SRCS = tests/test_grapple_weapon.cpp
TEST_GRP_EXE = $(BUILD_DIR)/test_grapple_weapon.exe

TEST_AI_SRCS = tests/test_ai_controller.cpp
TEST_AI_EXE = $(BUILD_DIR)/test_ai_controller.exe

TEST_AUD_SRCS = tests/test_audio_system.cpp
TEST_AUD_EXE = $(BUILD_DIR)/test_audio_system.exe

TEST_STG_SRCS = tests/test_stage_menu.cpp
TEST_STG_EXE = $(BUILD_DIR)/test_stage_menu.exe

TEST_NET_SRCS = tests/test_network_sync.cpp
TEST_NET_EXE = $(BUILD_DIR)/test_network_sync.exe

TEST_RPL_SRCS = tests/test_replay_system.cpp
TEST_RPL_EXE = $(BUILD_DIR)/test_replay_system.exe

TEST_TRN_SRCS = tests/test_tournament.cpp
TEST_TRN_EXE = $(BUILD_DIR)/test_tournament.exe

TEST_BTL_SRCS = tests/test_battle_mode.cpp
TEST_BTL_EXE = $(BUILD_DIR)/test_battle_mode.exe

TEST_SRV_SRCS = tests/test_survival_mode.cpp
TEST_SRV_EXE = $(BUILD_DIR)/test_survival_mode.exe

TEST_OPT_SRCS = tests/test_options_control.cpp
TEST_OPT_EXE = $(BUILD_DIR)/test_options_control.exe

TEST_EXES = $(TEST_MAP_EXE) $(TEST_DAT_EXE) $(TEST_GFX_EXE) $(TEST_ENT_EXE) $(TEST_CBT_EXE) $(TEST_GRP_EXE) $(TEST_AI_EXE) $(TEST_AUD_EXE) $(TEST_STG_EXE) $(TEST_NET_EXE) $(TEST_RPL_EXE) $(TEST_TRN_EXE) $(TEST_BTL_EXE) $(TEST_SRV_EXE) $(TEST_OPT_EXE)

.PHONY: all test clean $(BUILD_DIR)

all: $(BUILD_DIR) $(TARGET_LIB) $(TARGET_APP)

$(BUILD_DIR):
	$(MKDIR_BUILD)

$(TARGET_LIB): $(LIB_OBJS) | $(BUILD_DIR)
	$(AR) rcs $@ $^

$(TARGET_APP): $(APP_OBJS) $(TARGET_LIB) | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(APP_OBJS) -L$(BUILD_DIR) -llf2 $(SDL2_LIB) -lws2_32 -o $@
	$(COPY_SDL_DLL)
	$(NOTICE_DATA)

$(TEST_MAP_EXE): $(TEST_MAP_SRCS) $(TARGET_LIB) | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(TEST_MAP_SRCS) -L$(BUILD_DIR) -llf2 $(SDL2_LIB) -lws2_32 -o $@

$(TEST_DAT_EXE): $(TEST_DAT_SRCS) $(TARGET_LIB) | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(TEST_DAT_SRCS) -L$(BUILD_DIR) -llf2 $(SDL2_LIB) -lws2_32 -o $@

$(TEST_GFX_EXE): $(TEST_GFX_SRCS) $(TARGET_LIB) | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(TEST_GFX_SRCS) -L$(BUILD_DIR) -llf2 $(SDL2_LIB) -lws2_32 -o $@

$(TEST_ENT_EXE): $(TEST_ENT_SRCS) $(TARGET_LIB) | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(TEST_ENT_SRCS) -L$(BUILD_DIR) -llf2 $(SDL2_LIB) -lws2_32 -o $@

$(TEST_CBT_EXE): $(TEST_CBT_SRCS) $(TARGET_LIB) | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(TEST_CBT_SRCS) -L$(BUILD_DIR) -llf2 $(SDL2_LIB) -lws2_32 -o $@

$(TEST_GRP_EXE): $(TEST_GRP_SRCS) $(TARGET_LIB) | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(TEST_GRP_SRCS) -L$(BUILD_DIR) -llf2 $(SDL2_LIB) -lws2_32 -o $@

$(TEST_AI_EXE): $(TEST_AI_SRCS) $(TARGET_LIB) | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(TEST_AI_SRCS) -L$(BUILD_DIR) -llf2 $(SDL2_LIB) -lws2_32 -o $@

$(TEST_AUD_EXE): $(TEST_AUD_SRCS) $(TARGET_LIB) | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(TEST_AUD_SRCS) -L$(BUILD_DIR) -llf2 $(SDL2_LIB) -lws2_32 -o $@

$(TEST_STG_EXE): $(TEST_STG_SRCS) $(TARGET_LIB) | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(TEST_STG_SRCS) -L$(BUILD_DIR) -llf2 $(SDL2_LIB) -lws2_32 -o $@

$(TEST_NET_EXE): $(TEST_NET_SRCS) $(TARGET_LIB) | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(TEST_NET_SRCS) -L$(BUILD_DIR) -llf2 $(SDL2_LIB) -lws2_32 -o $@

$(TEST_RPL_EXE): $(TEST_RPL_SRCS) $(TARGET_LIB) | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(TEST_RPL_SRCS) -L$(BUILD_DIR) -llf2 $(SDL2_LIB) -lws2_32 -o $@

$(TEST_TRN_EXE): $(TEST_TRN_SRCS) $(TARGET_LIB) | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(TEST_TRN_SRCS) -L$(BUILD_DIR) -llf2 $(SDL2_LIB) -lws2_32 -o $@

$(TEST_BTL_EXE): $(TEST_BTL_SRCS) $(TARGET_LIB) | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(TEST_BTL_SRCS) -L$(BUILD_DIR) -llf2 $(SDL2_LIB) -lws2_32 -o $@

$(TEST_SRV_EXE): $(TEST_SRV_SRCS) $(TARGET_LIB) | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(TEST_SRV_SRCS) -L$(BUILD_DIR) -llf2 $(SDL2_LIB) -lws2_32 -o $@

$(TEST_OPT_EXE): $(TEST_OPT_SRCS) $(TARGET_LIB) | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(TEST_OPT_SRCS) -L$(BUILD_DIR) -llf2 $(SDL2_LIB) -lws2_32 -o $@

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
	./$(TEST_AUD_EXE)
	./$(TEST_STG_EXE)
	./$(TEST_NET_EXE)
	./$(TEST_RPL_EXE)
	./$(TEST_TRN_EXE)
	./$(TEST_BTL_EXE)
	./$(TEST_SRV_EXE)
	./$(TEST_OPT_EXE)
	./$(TARGET_APP) --test --frames 30
	$(RM) $(TEST_EXES) $(TEST_EXES:.exe=.d) *.d test_*_debug.exe $(TARGET_LIB)

decompiled-suite:
	$(MAKE) -C ../decompiled/Compilable all test

clean:
	$(RM) $(LIB_OBJS) $(APP_OBJS) $(LIB_OBJS:.o=.d) $(APP_OBJS:.o=.d) $(TARGET_LIB) $(TARGET_APP) $(TEST_EXES) $(TEST_EXES:.exe=.d) *.d test_*_debug.exe liblf2.a lf2.exe
	$(MAKE) -C ../decompiled/Compilable clean
