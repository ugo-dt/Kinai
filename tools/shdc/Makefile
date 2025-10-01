# Auto-generated Makefile

ifndef verbose
  SILENT = @
  NO_PRINT_DIRECTORY = --no-print-directory
endif

# ==============================================================================
# Platforms
# ==============================================================================
# Available platforms
__WIN32_ = win32
__LINUX_ = linux
__MACOS_ = macos
__EMSCRIPTEN_ = emscripten

# Current platform
__arch = $(shell uname -m)
__platform = $(shell uname | tr '[:upper:]' '[:lower:]')

# Helper conditions.
ifdef target
  # Compare against lowercase to make it case insensitive.
  # Use override to make sure the target name is consistent.
  __lc_target = $(shell echo $(target) | tr '[:upper:]' '[:lower:]')

  # Windows
  ifeq ($(target),windows)
    override target = $(__WIN32_)
  else ifeq ($(__lc_target),win)
    override target = $(__WIN32_)

  # Linux
  else ifeq ($(__lc_target),linux)
    override target = $(__LINUX_)

  # macOS
  else ifeq ($(__lc_target),macos)
    override target = $(__MACOS_)
  else ifeq ($(__lc_target),mac)
    override target = $(__MACOS_)
  else ifeq ($(__lc_target),osx)
    override target = $(__MACOS_)

  # Emscripten
  else ifeq ($(__lc_target),wgpu)
    override target = $(__EMSCRIPTEN_)
  else ifeq ($(__lc_target),web)
    override target = $(__EMSCRIPTEN_)
  else ifeq ($(__lc_target),emsc)
    override target = $(__EMSCRIPTEN_)

  else ifeq (,$(filter $(__lc_target),$(__WIN32_) $(__LINUX_) $(__MACOS_) $(__EMSCRIPTEN_)))
    $(error Unknown target '$(target)')
  endif
else # No specified target. Detect current platform.
  ifeq ($(__platform),linux)
    ifneq (,$(findstring microsoft-standard-WSL2,$(shell uname -r)))
      target = $(__WIN32_)
      CFLAGS += -D_WIN32_WINNT_WIN10=0x0A00 -D_WIN32_WINNT=_WIN32_WINNT_WIN10 -DPLATFORM_WSL=1
      CXXFLAGS += -D_WIN32_WINNT_WIN10=0x0A00 -D_WIN32_WINNT=_WIN32_WINNT_WIN10 -DPLATFORM_WSL=1
    else
      target = $(__LINUX_)
    endif
  else ifeq ($(__platform),darwin)
    target = $(__MACOS_)
  else
    target = $(__platform)
  endif
endif

ifeq ($(target),)
  $(error Empty target)
endif

ifeq ($(target),$(__WIN32_))
  __EXE_ = .exe
  __CC_ = $(__arch)-w64-mingw32-gcc
  __CXX_ = $(__arch)-w64-mingw32-c++
  __AR_ = $(__arch)-w64-mingw32-ar
  __LDFLAGS_ += -lmingw32 -lopengl32 -lglu32 -static
else ifeq ($(target),$(__LINUX_))
  __EXE_ = .out
  __LDFLAGS_ += -lm -lGL
else ifeq ($(target),$(__MACOS_))
  __EXE_ = .out
  __CC_ = clang
  __CXX_ = clang++
  __INCLUDE_ += -I /opt/homebrew/include
  __LDFLAGS_ += -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo -lncurses
else ifeq ($(target),$(__EMSCRIPTEN_))
  __EXE_ = .html
  __CC_ = emcc
  __CXX_ = em++
  __AR_ = emar
  __LDFLAGS_ += -sFULL_ES3=1 -sALLOW_MEMORY_GROWTH
endif

# ==============================================================================
# Variables
# ==============================================================================
__CC_ = gcc
__CFLAGS_ = -Wall -Wextra -Werror
__CXX_ = g++
__CXXFLAGS_ = -Wall -Wextra -Werror
__LDFLAGS_ = 
__AR_ = ar
__ARFLAGS_ = rcs
__RM_ = rm
__RMFLAGS_ = -rf
__NAME_ = shdc
__SRCS_ = $(wildcard source/*.c)
__INCLUDE_ = -I include -I lib
__path_objs_ = .obj
__path_lib_ = lib
__OBJS_ = $(patsubst %.c,$(__path_objs_)/%.o,$(__SRCS_))
__path_lib_objs_ = $(__path_objs_)/$(__path_lib_)

# ==============================================================================
# Libs
# ==============================================================================
# Libft
# https://github.com/ugo-dt/libft
__lib_libft_path_ = $(__path_lib_)/libft
__lib_libft_src_ = $(__path_lib_)/libft/libft.c
__lib_libft_objs_ = $(patsubst $(__lib_libft_path_)/%.c,$(__path_lib_objs_)/libft/libft.o,$(__lib_libft_src_))
__lib_objs_ += $(__lib_libft_objs_)

$(__path_lib_objs_)/libft/%.o: $(__lib_libft_path_)/%.c
	mkdir -p $(dir $@)
	$(__CC_) -c $< -o $@ $(__CFLAGS_) $(__INCLUDE_)

# ==============================================================================
# Rules
# ==============================================================================
all: $(__NAME_)

$(__NAME_): $(__lib_objs_) $(__OBJS_)
	$(__CC_) -o $(__NAME_) $(__OBJS_) $(__lib_objs_) $(__LDFLAGS_)

$(__path_objs_)/%.o: %.c
	mkdir -p $(dir $@)
	$(__CC_) -c $< -o $@ $(__CFLAGS_) $(__INCLUDE_)

clean:
	rm -rf $(__OBJS_)

fclean: clean
	rm -rf $(__NAME_)

re: fclean all

.PHONY: all clean fclean re
