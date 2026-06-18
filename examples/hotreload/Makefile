BUILD = release
KINAI_PATH = ../..
KINAI_VERBOSE = 1
KINAI_REMOVE_PREFIX = 1
KINAI_BUILD_SHARED_LIB = 1
include $(KINAI_PATH)/Makefile

# Game
GAME_DIR = .
BIN_DIR = $(GAME_DIR)/bin/$(TARGET)/$(ARCH)/$(BACKEND)/$(BUILD)
GAME_NAME = libgame
GAME = $(BIN_DIR)/$(GAME_NAME)_$(BUILD).0$(DLL)
# ifeq ($(BUILD),release)
  GAME_LINK = $(GAME_DIR)/libgame$(DLL)
# else
#   GAME_LINK = $(GAME_DIR)/$(GAME_NAME)_$(BUILD)$(DLL)
# endif
OBJ_DIR = $(GAME_DIR)/.obj/$(TARGET)/$(ARCH)/$(BACKEND)/$(BUILD)
GAME_SRC = $(wildcard source/$(GAME_DIR)/*.cpp source/$(GAME_DIR)/*/*.cpp source/$(GAME_DIR)/*/*/*.cpp)
GAME_OBJS = $(patsubst source/%.cpp,$(OBJ_DIR)/%.o,$(GAME_SRC))

ASSETS_DIR = $(GAME_DIR)/../assets
CXXFLAGS += -DASSETS_DIR=\"$(ASSETS_DIR)\" -DLIBRARY_NAME=\"$(GAME_LINK)\"
INCLUDE += -I include/$(GAME_DIR) -I $(ASSETS_DIR)/shaders -I $(GAME_DIR)/source

SHADERS_SRC = $(wildcard $(ASSETS_DIR)/shaders/*.glsl)
SHADERS_INCLUDE = $(SHADERS_SRC:.glsl=.glsl.hpp)

ifeq ($(TARGET),$(TARGET_EMSCRIPTEN))
  LDFLAGS += --preload-file $(ASSETS_DIR) -sEXPORTED_RUNTIME_METHODS=requestFullscreen
endif

# Game (executable)
RELOAD = $(BIN_DIR)/reload$(EXE)
RELOAD_SRC = $(GAME_DIR)/main.cpp
RELOAD_OBJ = $(patsubst %.cpp,$(OBJ_DIR)/reload/%.o,$(RELOAD_SRC))
RELOAD_LINK = $(GAME_DIR)/reload$(EXE)

all: $(GAME) $(GAME_LINK) $(RELOAD) $(RELOAD_LINK)

clean::
	$(Q)rm -rf $(GAME_OBJS)
	@echo "Cleaned target '$(TARGET)'"

fclean::
	$(Q)$(MAKE) $(NO_PRINT_DIRECTORY) clean
	$(Q)rm -rf ./bin/$(TARGET) $(KINAI) $(GAME)

re::
	$(Q)$(MAKE) $(NO_PRINT_DIRECTORY) fclean
	$(Q)$(MAKE) $(NO_PRINT_DIRECTORY) all

$(GAME): $(KINAI) $(SHADERS_INCLUDE) $(GAME_OBJS)
	$(Q)mkdir -p $(dir $@)
	@echo "[CXX] $(GAME)"
	$(Q)$(CXX) -o $@ $(GAME_OBJS) $(LDFLAGS) $(SHARED) -L $(KINAI_BIN_DIR) -lKinai
	@echo "$(COLOR_GREEN)Successfully built $(GAME)$(COLOR_DEFAULT)"

$(GAME_LINK): $(GAME)
	@echo "[ LN] $@"
	$(Q)ln -sf $(GAME) $@

$(OBJ_DIR)/$(GAME_DIR)/%.o: source/$(GAME_DIR)/%.cpp $(SHADERS_INCLUDE)
	@echo "[CXX] $<"
	$(Q)mkdir -p $(dir $@)
	$(Q)$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -o $@

$(ASSETS_DIR)/shaders/%.glsl.hpp: $(ASSETS_DIR)/shaders/%.glsl
	@echo "[SHDC] $<"
	$(Q)$(SHDC) -i $< -o $@ --slang glsl410:glsl300es -y

$(OBJ_DIR)/reload/%.o: $(GAME_DIR)/%.cpp
	@echo "[CXX] $<"
	$(Q)mkdir -p $(dir $@)
	$(Q)$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -o $@

$(RELOAD): $(KINAI) $(GAME) $(GAME_LINK) $(RELOAD_OBJ)
	$(Q)mkdir -p $(dir $@)
	@echo "[CXX] $(RELOAD)"
	$(Q)$(CXX) -o $@ $(RELOAD_OBJ) $(KINAI) $(LDFLAGS) -L $(BIN_DIR) -lgame_$(BUILD).0 -Wl,-rpath,$(GAME_DIR)
	@echo "$(COLOR_GREEN)Successfully built $(RELOAD)$(COLOR_DEFAULT)"

$(RELOAD_LINK): $(RELOAD)
	@echo "[ LN] $@"
	$(Q)ln -sf $(RELOAD) $@

run: $(RELOAD_LINK)
	$(Q)$(RELOAD_LINK)
