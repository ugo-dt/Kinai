ifndef __PLATFORM_MK
__PLATFORM_MK = 1

ifndef __LIB_MK
	Do not include make/__platform.mk directly. Use make/lib.mk.
endif

include $(KINAI_PATH)/make/__core.mk

# Available platforms
__WIN32__		= win32
__WIN32__		= win32
__LINUX__		= linux
__MACOS__		= darwin
__EMSCRIPTEN__	= emscripten

# Current platform
__arch				= $(shell uname -m)
__platform			= $(shell uname | tr '[:upper:]' '[:lower:]')

# Helper conditions.
# Use override to make sure the target name is consistent.
ifdef target
  # Compare against lowercase to make it case insensitive.
  __lc_target = $(shell echo $(target) | tr '[:upper:]' '[:lower:]')
  # Windows
  ifeq ($(target),windows)
    override target = $(__WIN32__)
  else ifeq ($(__lc_target),win)
    override target = $(__WIN32__)

  # Linux
  else ifeq ($(__lc_target),linux)
    override target = $(__LINUX__)

  # macOS
  else ifeq ($(__lc_target),macos)
    override target = $(__MACOS__)
  else ifeq ($(__lc_target),mac)
    override target = $(__MACOS__)
  else ifeq ($(__lc_target),osx)
    override target = $(__MACOS__)
  
  # Emscripten
  else ifeq ($(__lc_target),wgpu)
    override target = $(__EMSCRIPTEN__)
  else ifeq ($(__lc_target),web)
    override target = $(__EMSCRIPTEN__)
  else ifeq ($(__lc_target),emsc)
    override target = $(__EMSCRIPTEN__)

  else ifeq (,$(filter $(__lc_target),$(__WIN32__) $(__LINUX__) $(__MACOS__) $(__EMSCRIPTEN__)))
    $(error Unknown target '$(target)')
  endif
else # Detect current platform.
  ifeq ($(__platform),linux)
    ifneq (,$(findstring microsoft-standard-WSL2,$(shell uname -r)))
      target = $(__WIN32__)
      CFLAGS += -D_WIN32_WINNT_WIN10=0x0A00 -D_WIN32_WINNT=_WIN32_WINNT_WIN10 -DPLATFORM_WSL=1
      CXXFLAGS += -D_WIN32_WINNT_WIN10=0x0A00 -D_WIN32_WINNT=_WIN32_WINNT_WIN10 -DPLATFORM_WSL=1
    else
      target = $(__LINUX__)
    endif
  else ifeq ($(__platform),darwin)
    target = $(__MACOS__)
  else
    target = $(__platform)
  endif
endif

ifeq ($(target),)
  $(error Empty target)
endif

ifeq ($(target),$(__WIN32__))
  EXE		= .exe
  CC		= $(__arch)-w64-mingw32-gcc
  CXX		= $(__arch)-w64-mingw32-c++
  AR		= $(__arch)-w64-mingw32-ar
  LDFLAGS	+= -lmingw32 -lopengl32 -lglu32 -static
  __kinai_target_win32 = 1
else ifeq ($(target),$(__LINUX__))
  EXE 		= .out
  LDFLAGS	+= -lm -lGL
  __kinai_target_linux = 1
else ifeq ($(target),$(__MACOS__))
  EXE		=
  CC    	= clang
  CXX   	= clang++
  INCLUDE	+= -I /opt/homebrew/include
  LDFLAGS	+= -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo -lncurses
  __kinai_target_macos = 1
else ifeq ($(target),$(__EMSCRIPTEN__))
  EXE		= .html
  CC		= emcc
  CXX		= em++
  AR		= emar
  CXXFLAGS	+= -sUSE_SDL=3 -Wno-experimental
  LDFLAGS	+= -sUSE_SDL=3 -sALLOW_MEMORY_GROWTH -sWASM=1 -sUSE_WEBGL2=1 -sMIN_WEBGL_VERSION=2 -sMAXIMUM_MEMORY=1gb --shell-file $(KINAI_PATH)/kinai-shell.html
  __kinai_target_emscripten = 1
endif

# Rendering backend.
ifndef backend
  backend = OpenGL
endif

ifdef KINAI_BACKEND
  override backend = $(KINAI_BACKEND)
endif

ifeq ($(backend),)
  $(info Please select a backend between OpenGL, Sokol or Headless.)
  $(error No rendering backend selected)
endif

# Compare against lowercase to make it case insensitive.
__lc_backend = $(shell echo $(backend) | tr '[:upper:]' '[:lower:]')

ifeq ($(__lc_backend),opengl) # OpenGL
  override backend = OpenGL
  __kinai_backend_opengl = 1
  CXXFLAGS += -DKINAI_OPENGL
else ifeq ($(__lc_backend),gl)
  override backend = OpenGL
  __kinai_backend_opengl = 1
  CXXFLAGS += -DKINAI_OPENGL
else ifeq ($(__lc_backend),sokol)
  override backend = Sokol
  __kinai_backend_opengl = 1
  __kinai_backend_sokol = 1
  CXXFLAGS += -DKINAI_OPENGL -DKINAI_SOKOL
else ifeq ($(__lc_backend),null) # Headless
  override backend = Headless
  __kinai_backend_headless = 1
  CXXFLAGS += -DKINAI_HEADLESS
else ifeq ($(__lc_backend),none)
  override backend = Headless
  __kinai_backend_headless = 1
  CXXFLAGS += -DKINAI_HEADLESS
else ifeq ($(__lc_backend),headless)
  override backend = Headless
  __kinai_backend_headless = 1
  CXXFLAGS += -DKINAI_HEADLESS
else ifeq (,$(filter $(__lc_backend),$(__WIN32__) $(__LINUX__) $(__MACOS__) $(__EMSCRIPTEN__)))
  $(error Unknown backend '$(backend)')
endif

OBJS_DIR := $(OBJS_DIR)/$(backend)/$(build)

endif # __PLATFORM_MK
