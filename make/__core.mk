ifndef __CORE_MK
__CORE_MK = 1

ifndef __PLATFORM_MK
	Do not include make/__core.mk directly. Use make/lib.mk.
endif

ifndef verbose
  SILENT = @
  NO_PRINT_DIRECTORY = --no-print-directory
endif

.DEFAULT_GOAL := all

# CC
CC = gcc-14
CXX = g++
CFLAGS = -Wall -Wextra
CXXFLAGS = -Wall -Wextra -std=c++14
AR = ar
ARFLAGS = rcs
CMAKE = cmake

# Colors
COLOR_DEFAULT	= \033[39m
COLOR_GREEN		= \033[92m
COLOR_YELLOW	= \033[33m
COLOR_GREY		= \033[90m
COLOR_RED		= \033[91m

# Object files
__base_objs_dir		= .obj
OBJS_DIR			= $(__base_objs_dir)/$(target)/$(__arch)

__build_debug		= debug
__build_dev			= dev
__build_release		= release

# Build configuration
ifndef build
  build = $(__build_dev)
endif

ifeq ($(build),$(__build_debug)) # Debug
  CFLAGS	+= -DKINAI_DEBUG -g
  CXXFLAGS	+= -DKINAI_DEBUG -g
else ifeq ($(build),$(__build_dev)) # Dev
  CFLAGS	+= -DKINAI_DEV
  CXXFLAGS	+= -DKINAI_DEV
else ifeq ($(build),$(__build_release)) # Release
  CFLAGS	+= -DKINAI_RELEASE -O3
  CXXFLAGS	+= -DKINAI_RELEASE -O3
else ifeq ($(build),)
  $(error Empty build)
else
  $(error Unknown build '$(build)')
endif

endif # __CORE_MK
