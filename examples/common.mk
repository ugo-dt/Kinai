ifndef KINAI_PATH
  $(error [Kinai] Please define KINAI_PATH)
endif

BUILD = release
KINAI_VERBOSE = 1
KINAI_REMOVE_PREFIX = 1
include $(KINAI_PATH)/Makefile

ifndef GAME_DIR
  $(error [Kinai] Please define GAME_DIR)
endif
ifndef GAME_NAME
  $(error [Kinai] Please define GAME_NAME)
endif

ASSETS_DIR = $(GAME_DIR)/../assets
CXXFLAGS += -DASSETS_DIR=\"$(ASSETS_DIR)\"

# Game
BIN_DIR = $(GAME_DIR)/bin/$(TARGET)/$(ARCH)/$(BACKEND)/$(BUILD)
GAME = $(BIN_DIR)/$(GAME_NAME)$(EXE)
ifeq ($(BUILD),release)
  GAME_LINK = $(GAME_DIR)/$(GAME_NAME)$(EXE)
else
  GAME_LINK = $(GAME_DIR)/$(GAME_NAME)_$(BUILD)$(EXE)
endif
OBJ_DIR = $(GAME_DIR)/.obj/$(TARGET)/$(ARCH)/$(BACKEND)/$(BUILD)
GAME_SRC = $(wildcard $(GAME_DIR)/*.cpp $(GAME_DIR)/**/*.cpp)
GAME_OBJS = $(patsubst %.cpp,$(OBJ_DIR)/%.o,$(GAME_SRC))

INCLUDE += -I include/$(GAME_DIR) -I $(GAME_DIR)/../assets/shaders

ifeq ($(TARGET),$(TARGET_EMSCRIPTEN))
  LDFLAGS += --preload-file $(GAME_DIR)/../assets -sEXPORTED_RUNTIME_METHODS=requestFullscreen
endif

all: $(GAME) $(GAME_LINK)

clean::
	$(Q)rm -rf $(GAME_OBJS)
	@echo "Cleaned target '$(TARGET)'"

fclean::
	$(Q)$(MAKE) $(NO_PRINT_DIRECTORY) clean
	$(Q)rm -rf ./bin/$(TARGET) $(KINAI) $(GAME)

re::
	$(Q)$(MAKE) $(NO_PRINT_DIRECTORY) fclean
	$(Q)$(MAKE) $(NO_PRINT_DIRECTORY) all

$(GAME): $(KINAI) $(GAME_OBJS)
	$(Q)mkdir -p $(dir $@)
	@echo "[CXX] $(GAME)"
	$(Q)$(CXX) -o $@ $(GAME_OBJS) $(KINAI) $(LDFLAGS)
	@echo "$(COLOR_GREEN)Successfully built $(notdir $@)$(COLOR_DEFAULT)"

$(GAME_LINK): $(GAME)
	@echo "[LN] $@"
	$(Q)ln -sf $(GAME) $@

$(OBJ_DIR)/%.o: %.cpp
	@echo "[CXX] $<"
	$(Q)mkdir -p $(dir $@)
	$(Q)$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -o $@

run: $(GAME_LINK)
	$(Q)$(GAME_LINK)
