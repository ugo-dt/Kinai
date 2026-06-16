# ==============================================================================
# User configuration
# ==============================================================================
ifndef KINAI_TARGET
  ifdef target
    KINAI_TARGET = $(target)
  else ifdef kinai_target
    KINAI_TARGET = $(kinai_target)
  else
    KINAI_TARGET = auto
  endif
endif

ifndef KINAI_BACKEND
  ifdef backend
    KINAI_BACKEND = $(backend)
  else ifdef kinai_backend
    KINAI_BACKEND = $(kinai_backend)
  else
    KINAI_BACKEND = OpenGL
  endif
endif

ifndef KINAI_BUILD
  ifdef build
    KINAI_BUILD = $(build)
  else ifdef kinai_build
    KINAI_BUILD = $(kinai_build)
  else ifdef BUILD
    KINAI_BUILD = $(BUILD)
  else
    KINAI_BUILD = dev
  endif
endif

ifndef KINAI_VERBOSE
  ifdef verbose
    KINAI_VERBOSE = $(verbose)
  else ifdef VERBOSE
    KINAI_VERBOSE = $(VERBOSE)
  else ifdef kinai_verbose
    KINAI_VERBOSE = $(kinai_verbose)
  else ifdef v
    KINAI_VERBOSE = $(v)
  else
    KINAI_VERBOSE = 0
  endif
endif

ifndef KINAI_PATH
  ifdef kinai_path
    KINAI_PATH = $(kinai_path)
  else ifdef kinai
    KINAI_PATH = $(kinai)
  else
    KINAI_PATH = $(CURDIR)
  endif
endif

# ==============================================================================
# Configuration
# ==============================================================================
ifeq ($(KINAI_VERBOSE),0)
    KINAI_Q := @
    MAKEFLAGS += --no-print-directory
endif

KINAI_COLOR_DEFAULT := \033[39m
KINAI_COLOR_GREEN := \033[92m
KINAI_COLOR_YELLOW := \033[33m
KINAI_COLOR_GREY := \033[90m
KINAI_COLOR_RED := \033[91m

.DEFAULT_GOAL := all

# ==============================================================================
# Host Detection
# ==============================================================================
KINAI_HOST_PLATFORM := $(shell uname | tr '[:upper:]' '[:lower:]')
KINAI_ARCH          := $(shell uname -m)

TARGET_WIN32      := win32
TARGET_LINUX      := linux
TARGET_MACOS      := darwin
TARGET_EMSCRIPTEN := emscripten

# Normalize aliases
TARGET_LC := $(shell echo $(KINAI_TARGET) | tr '[:upper:]' '[:lower:]')

# Windows
ifneq ($(filter $(TARGET_LC),windows win win32 win64),)
  KINAI_TARGET := $(TARGET_WIN32)
# Linux
else ifneq ($(filter $(TARGET_LC),linux),)
  KINAI_TARGET := $(TARGET_LINUX)
# MacOS
else ifneq ($(filter $(TARGET_LC),mac macos osx darwin),)
  KINAI_TARGET := $(TARGET_MACOS)
# Emscripten
else ifneq ($(filter $(TARGET_LC),web wgpu emsc emscripten wasm),)
  KINAI_TARGET := $(TARGET_EMSCRIPTEN)

else ifeq ($(KINAI_TARGET),auto)
  ifeq ($(KINAI_HOST_PLATFORM),linux)
    ifneq (,$(findstring microsoft-standard-WSL2,$(shell uname -r)))
      KINAI_TARGET := $(TARGET_WIN32)
    else
      KINAI_TARGET := $(TARGET_LINUX)
    endif
  else ifeq ($(KINAI_HOST_PLATFORM),darwin)
    KINAI_TARGET := $(TARGET_MACOS)
  else
    KINAI_TARGET := $(KINAI_HOST_PLATFORM)
  endif
else
  $(error Unknown target '$(KINAI_TARGET)')
endif

# ==============================================================================
# Build Configuration
# ==============================================================================
KINAI_CFLAGS   := -Wall -Wextra -Werror
KINAI_CXXFLAGS := -Wall -Wextra -Werror -std=c++14 -Wno-missing-field-initializers
KINAI_LDFLAGS  :=

ifeq ($(KINAI_BUILD),debug)
    KINAI_CFLAGS   += -DKINAI_DEBUG -ggdb -O0
    KINAI_CXXFLAGS += -DKINAI_DEBUG -ggdb -O0
else ifeq ($(KINAI_BUILD),dev)
  KINAI_CFLAGS   += -O2 -DKINAI_DEV
  KINAI_CXXFLAGS += -O2 -DKINAI_DEV
else ifeq ($(KINAI_BUILD),release)
  KINAI_CFLAGS   += -O3 -DKINAI_RELEASE
  KINAI_CXXFLAGS += -O3 -DKINAI_RELEASE
else
  $(error Unknown build '$(KINAI_BUILD)')
endif

ifdef KINAI_BUILD_SHARED_LIB
  KINAI_CFLAGS += -fPIC
  KINAI_CXXFLAGS += -fPIC
endif

# ==============================================================================
# Backend
# ==============================================================================
BACKEND_LC := $(shell echo $(KINAI_BACKEND) | tr '[:upper:]' '[:lower:]')

ifneq ($(filter $(BACKEND_LC),opengl gl),)
 KINAI_BACKEND := OpenGL
 KINAI_CXXFLAGS += -DKINAI_OPENGL
else ifneq ($(filter $(BACKEND_LC),headless null none),)
  KINAI_BACKEND := Headless
  KINAI_CXXFLAGS += -DKINAI_HEADLESS
else
  $(error Unknown backend '$(KINAI_BACKEND)')
endif

# ==============================================================================
# Directories
# ==============================================================================
OBJ_ROOT          := $(KINAI_PATH)/.obj
KINAI_OBJ_DIR     := $(OBJ_ROOT)/$(KINAI_TARGET)/$(KINAI_ARCH)/$(KINAI_BACKEND)/$(KINAI_BUILD)
KINAI_LIB_OBJ_DIR := $(KINAI_OBJ_DIR)/lib
KINAI_BIN_DIR     := $(KINAI_PATH)/bin/$(KINAI_TARGET)/$(KINAI_ARCH)/$(KINAI_BACKEND)/$(KINAI_BUILD)

# ==============================================================================
# Toolchain
# ==============================================================================
CC      := gcc-14
CXX     := g++
AR      := ar
ARFLAGS := rcs
CMAKE   := cmake
KINAI_INCLUDE := -I $(KINAI_PATH)/include -I $(KINAI_PATH)/include/Kinai -I $(KINAI_PATH)

# Platform overrides
ifeq ($(KINAI_TARGET),$(TARGET_WIN32))
  EXE := .exe
  DLL := .dll
  KINAI_SHARED := -s -shared -Wl,--subsystem,windows,--out-implib,$(notdir $@).a
  CC  := $(KINAI_ARCH)-w64-mingw32-gcc
  CXX := $(KINAI_ARCH)-w64-mingw32-g++
  AR  := $(KINAI_ARCH)-w64-mingw32-ar
  KINAI_LDFLAGS += \
    -lmingw32 \
    -lopengl32 \
    -lglu32 \
    -static
else ifeq ($(KINAI_TARGET),$(TARGET_LINUX))
  EXE := .out
  DLL := .so
  KINAI_SHARED := -shared -fPIC -Wl,-rpath,$(KINAI_BIN_DIR)
  KINAI_LDFLAGS += -lm -lGL
else ifeq ($(KINAI_TARGET),$(TARGET_MACOS))
  CC  := clang
  CXX := clang++
  DLL := .dylib
  KINAI_SHARED := -shared -fPIC
  KINAI_INCLUDE += -I/opt/homebrew/include
  KINAI_LDFLAGS += \
    -framework OpenGL \
    -framework Cocoa \
    -framework IOKit \
    -framework CoreVideo
else ifeq ($(KINAI_TARGET),$(TARGET_EMSCRIPTEN))
  EXE := .html
  CC  := emcc
  CXX   := em++
  AR  := emar
  CMAKE := emcmake cmake
  KINAI_CXXFLAGS += -Wno-experimental -DIMGUI_IMPL_OPENGL_ES3
  KINAI_LDFLAGS += \
    -sUSE_SDL=3 \
    -sALLOW_MEMORY_GROWTH \
    -sWASM=1 \
    -sUSE_WEBGL2=1 \
    -sMIN_WEBGL_VERSION=2
endif

# ==============================================================================
# Dependencies
# ==============================================================================
KINAI_LIB_DIR := $(KINAI_PATH)/lib

KINAI_GLAD_DIR  := $(KINAI_LIB_DIR)/glad
KINAI_SDL3_DIR  := $(KINAI_LIB_DIR)/SDL3
KINAI_IMGUI_DIR := $(KINAI_LIB_DIR)/imgui
KINAI_FMT_DIR   := $(KINAI_LIB_DIR)/fmt
KINAI_STB_DIR   := $(KINAI_LIB_DIR)/stb
KINAI_GLM_DIR   := $(KINAI_LIB_DIR)/glm

# Includes
KINAI_INCLUDE += \
  -I$(KINAI_LIB_DIR) \
  -I$(KINAI_GLAD_DIR)/include \
  -I$(KINAI_SDL3_DIR)/include \
  -I$(KINAI_IMGUI_DIR) \
  -I$(KINAI_IMGUI_DIR)/backends \
  -I$(KINAI_FMT_DIR)/include \
  -I$(KINAI_GLM_DIR)

# Compile the libs in a separate 'lib' folder to avoid recompiling
KINAI_LIB_OBJ_DIR := $(KINAI_OBJ_DIR)/lib

# Glad
KINAI_GLAD_SRC = $(KINAI_GLAD_DIR)/src/glad.c
KINAI_GLAD_OBJ = $(patsubst $(KINAI_GLAD_DIR)/src/%.c,$(KINAI_LIB_OBJ_DIR)/glad/%.o,$(KINAI_GLAD_SRC))
KINAI_LIB_OBJS += $(KINAI_GLAD_OBJ)

$(KINAI_LIB_OBJ_DIR)/glad/%.o: $(KINAI_GLAD_DIR)/src/%.c
	@echo "[ CC] $<"
	$(KINAI_Q)mkdir -p $(dir $@)
	$(KINAI_Q)$(CC) $(KINAI_CFLAGS) $(KINAI_INCLUDE) -c $< -o $@

# ImGui
ifeq ($(KINAI_BACKEND),Headless)
  KINAI_IMGUI_SRC = $(wildcard $(KINAI_IMGUI_DIR)/*.cpp)
else
  IMGUI_BACKEND	= opengl3
  IMGUI_PLATFORM = sdl3
  KINAI_IMGUI_SRC = $(wildcard $(KINAI_IMGUI_DIR)/*.cpp) $(KINAI_IMGUI_DIR)/backends/imgui_impl_$(IMGUI_BACKEND).cpp  $(KINAI_IMGUI_DIR)/backends/imgui_impl_$(IMGUI_PLATFORM).cpp
endif
KINAI_IMGUI_OBJS = $(patsubst $(KINAI_IMGUI_DIR)/%.cpp,$(KINAI_LIB_OBJ_DIR)/imgui/%.o,$(KINAI_IMGUI_SRC))

$(KINAI_LIB_OBJ_DIR)/imgui/%.o: $(KINAI_IMGUI_DIR)/%.cpp
	@echo "[CXX] $<"
	$(KINAI_Q)mkdir -p $(dir $@)
	$(KINAI_Q)$(CXX) $(KINAI_CXXFLAGS) $(KINAI_INCLUDE) -c $< -o $@
KINAI_LIB_OBJS += $(KINAI_IMGUI_OBJS)

# SDL3
SDL3_BUILD_DIR = $(KINAI_SDL3_DIR)/build_$(KINAI_TARGET)_$(KINAI_ARCH)_$(KINAI_BUILD)

ifeq ($(KINAI_BACKEND),OpenGL)
	ifeq ($(KINAI_TARGET),$(TARGET_MACOS))
    KINAI_LDFLAGS += $(shell pkgconf --libs SDL3)
	else ifeq ($(KINAI_TARGET),$(TARGET_WIN32))
    KINAI_LDFLAGS += $(KINAI_SDL3_DIR)/bin/$(KINAI_TARGET)/libSDL3.dll.a
	else ifeq ($(KINAI_TARGET),$(TARGET_LINUX))
    LIB_SDL3 = $(SDL3_BUILD_DIR)/libSDL3.so
    KINAI_LDFLAGS += -L $(SDL3_BUILD_DIR) -lSDL3
	endif
endif

$(SDL3_BUILD_DIR): $(KINAI_SDL3_DIR)/CMakeLists.txt
	@echo "$(COLOR_GREY)Configuring SDL3...$(COLOR_DEFAULT)"
	$(KINAI_Q)mkdir -p $(SDL3_BUILD_DIR)
	$(KINAI_Q)$(CMAKE) -S $(KINAI_SDL3_DIR) -B $(SDL3_BUILD_DIR)

$(LIB_SDL3): $(SDL3_BUILD_DIR)
	@echo "$(COLOR_GREY)Building SDL3...$(COLOR_DEFAULT)"
	$(KINAI_Q)$(CMAKE) --build $(SDL3_BUILD_DIR)

# stb_image
STB_IMAGE_SRC = $(KINAI_STB_DIR)/stb_image.c
STB_IMAGE_OBJS = $(patsubst $(KINAI_STB_DIR)/%.c,$(KINAI_LIB_OBJ_DIR)/stb_image/%.o,$(STB_IMAGE_SRC))

$(KINAI_LIB_OBJ_DIR)/stb_image/%.o: $(KINAI_STB_DIR)/%.c
	@echo "[ CC] $<"
	$(KINAI_Q)mkdir -p $(dir $@)
	$(KINAI_Q)$(CC) $(KINAI_CFLAGS) $(KINAI_INCLUDE) -c $< -o $@
KINAI_LIB_OBJS += $(STB_IMAGE_OBJS)

# fmt
ifdef KINAI_BUILD_SHARED_LIB
  FMT_BUILD_DIR = $(KINAI_FMT_DIR)/build_$(KINAI_TARGET)_$(KINAI_ARCH)_$(KINAI_BUILD)/shared
  LIB_FMT = $(FMT_BUILD_DIR)/libfmt$(DLL)
  LIB_FMT_FLAGS = -DBUILD_SHARED_LIBS=ON
  KINAI_LDFLAGS += -L $(FMT_BUILD_DIR) -lfmt -Wl,-rpath,$(FMT_BUILD_DIR)
else
  FMT_BUILD_DIR = $(KINAI_FMT_DIR)/build_$(KINAI_TARGET)_$(KINAI_ARCH)_$(KINAI_BUILD)/static
  LIB_FMT = $(FMT_BUILD_DIR)/libfmt.a
  KINAI_LDFLAGS += $(LIB_FMT)
endif
FMT_MAKEFILE  = $(FMT_BUILD_DIR)/Makefile

$(FMT_MAKEFILE): $(KINAI_FMT_DIR)/CMakeLists.txt
	@echo "$(COLOR_GREY)Configuring fmt...$(COLOR_DEFAULT)"
	$(KINAI_Q)mkdir -p $(FMT_BUILD_DIR)
	$(KINAI_Q)$(CMAKE) -S $(KINAI_FMT_DIR) -B $(FMT_BUILD_DIR) -DFMT_TEST=OFF $(LIB_FMT_FLAGS)

$(LIB_FMT): $(FMT_MAKEFILE)
	@echo "$(COLOR_GREY)Building fmt...$(COLOR_DEFAULT)"
	$(KINAI_Q)$(MAKE) -C $(FMT_BUILD_DIR)

# ==============================================================================
# Source Files
# ==============================================================================
KINAI_SRC = $(wildcard					\
	$(KINAI_PATH)/src/Core/*.cpp		\
	$(KINAI_PATH)/src/Debug/*.cpp		\
	$(KINAI_PATH)/src/ImGui/*.cpp		\
	$(KINAI_PATH)/src/Renderer/*.cpp	\
	$(KINAI_PATH)/src/Renderer/2D/*.cpp	\
)

# Backend-specific additions
ifeq ($(KINAI_BACKEND),OpenGL)
  KINAI_SRC += $(wildcard $(KINAI_PATH)/src/Platform/OpenGL/*.cpp)
  ifeq ($(KINAI_TARGET),$(TARGET_EMSCRIPTEN))
    KINAI_SRC += $(wildcard $(KINAI_PATH)/src/Platform/Emscripten/*.cpp)
  else
    KINAI_SRC += $(wildcard $(KINAI_PATH)/src/Platform/SDL/*.cpp)
  endif
else ifeq ($(KINAI_BACKEND),Headless)
  KINAI_SRC += $(wildcard $(KINAI_PATH)/src/Platform/Headless/*.cpp)
endif

# Object generation	
KINAI_OBJS = $(patsubst $(KINAI_PATH)/src/%.cpp,$(KINAI_OBJ_DIR)/%.o,$(KINAI_SRC))

# ==============================================================================
# Build Rules
# ==============================================================================
# === Shared library ===
ifdef KINAI_BUILD_SHARED_LIB
KINAI := $(KINAI_BIN_DIR)/libKinai$(DLL)

$(KINAI_OBJ_DIR)/%.o: $(KINAI_PATH)/src/%.cpp
	@echo "[CXX] $<"
	$(KINAI_Q)mkdir -p $(dir $@)
	$(KINAI_Q)$(CXX) $(KINAI_CXXFLAGS) $(KINAI_INCLUDE) -c $< -o $@

all: $(KINAI)

$(KINAI): $(LIB_FMT) $(LIB_SDL3) $(KINAI_LIB_OBJS) $(KINAI_OBJS)
	@echo "[ LD] $@"
	$(KINAI_Q)mkdir -p $(dir $@)
	$(KINAI_Q)$(CXX) -o $@ $(KINAI_OBJS) $(KINAI_LIB_OBJS) $(KINAI_LDFLAGS) $(KINAI_SHARED)
	@echo "$(KINAI_COLOR_GREEN)Successfully built shared library '$(notdir $(KINAI))' ($(KINAI_BACKEND) - $(KINAI_TARGET) - $(KINAI_BUILD))$(KINAI_COLOR_DEFAULT)"
# === Static library ===
else
KINAI := $(KINAI_BIN_DIR)/libKinai.a

$(KINAI_OBJ_DIR)/%.o: $(KINAI_PATH)/src/%.cpp
	@echo "[CXX] $<"
	$(KINAI_Q)mkdir -p $(dir $@)
	$(KINAI_Q)$(CXX) $(KINAI_CXXFLAGS) $(KINAI_INCLUDE) -c $< -o $@

all: $(KINAI)

$(KINAI): $(LIB_FMT) $(LIB_SDL3) $(KINAI_LIB_OBJS) $(KINAI_OBJS)
	@echo "[ AR] $@"
	$(KINAI_Q)mkdir -p $(dir $@)
	$(KINAI_Q)$(AR) $(ARFLAGS) $(KINAI) $(KINAI_OBJS) $(KINAI_LIB_OBJS)
	@echo "$(KINAI_COLOR_GREEN)Successfully built $(notdir $(KINAI)) ($(KINAI_BACKEND) - $(KINAI_TARGET) - $(KINAI_BUILD))$(KINAI_COLOR_DEFAULT)"
endif

# ==============================================================================
# Utility
# ==============================================================================
ifneq (,$(filter $(KINAI_VERBOSE),1 true yes))
$(info ===== Kinai Build =====)
$(info Target  | $(KINAI_TARGET))
$(info Arch    | $(KINAI_ARCH))
$(info Backend | $(KINAI_BACKEND))
$(info Build   | $(KINAI_BUILD))
$(info Shared  | $(KINAI_BUILD_SHARED_LIB))
$(info KINAI_PATH     | $(KINAI_PATH))
$(info KINAI_INCLUDE  | $(KINAI_INCLUDE))
$(info KINAI_CFLAGS   | $(KINAI_CFLAGS))
$(info KINAI_CXXFLAGS | $(KINAI_CXXFLAGS))
$(info KINAI_LDFLAGS  | $(KINAI_LDFLAGS))
$(info KINAI_OBJ_DIR  | $(KINAI_OBJ_DIR))
$(info KINAI_BIN_DIR  | $(KINAI_BIN_DIR))
$(info Kinai    | $(KINAI))
$(info =======================)
endif

clean::
	@echo "Cleaning objects..."
	$(KINAI_Q)rm -rf $(KINAI_OBJ_DIR)

fclean:: clean
	@echo "Cleaning binaries..."
	$(KINAI_Q)rm -rf $(KINAI_BIN_DIR)

re:: fclean all

.PHONY: all clean fclean re

ifdef KINAI_REMOVE_PREFIX
  TARGET := $(KINAI_TARGET)
  ARCH := $(KINAI_ARCH)
  BACKEND := $(KINAI_BACKEND)
  BUILD := $(KINAI_BUILD)
  INCLUDE := $(KINAI_INCLUDE)
  LDFLAGS := $(KINAI_LDFLAGS)
  CXXFLAGS := $(KINAI_CXXFLAGS)
  SHARED := $(KINAI_SHARED)
  Q := $(KINAI_Q)
  COLOR_DEFAULT := $(KINAI_COLOR_DEFAULT)
  COLOR_GREEN := $(KINAI_COLOR_GREEN)
  COLOR_YELLOW := $(KINAI_COLOR_YELLOW)
  COLOR_GREY := $(KINAI_COLOR_GREY)
  COLOR_RED := $(KINAI_COLOR_RED)
endif
