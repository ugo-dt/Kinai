ifndef __CORE_MK
__CORE_MK = 1

ifndef __PLATFORM_MK
	Do not include make/__core.mk directly. Use make/lib.mk.
endif

# CC
CC				= gcc-14
CXX				= g++
CFLAGS			= -Wall -Werror -Wextra
CXXFLAGS		= -Wall -Werror -Wextra -std=c++20
AR				= ar
ARFLAGS			= rcs

# Colors
COLOR_DEFAULT	= \033[39m
COLOR_GREEN		= \033[92m
COLOR_YELLOW	= \033[33m
COLOR_GREY		= \033[90m
COLOR_RED		= \033[91m

ifndef verbose
  SILENT = @
  NO_PRINT_DIRECTORY = --no-print-directory
endif

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
# Debug
ifeq ($(build),$(__build_debug))
  CFLAGS += -DEG_DEBUG -g
  CXXFLAGS += -DEG_DEBUG -g

# Dev
else ifeq ($(build),$(__build_dev))
  CFLAGS += -DEG_DEV -g
  CXXFLAGS += -DEG_DEV -g

# Release
else ifeq ($(build),$(__build_release))
  CFLAGS += -DEG_RELEASE -O3
  CXXFLAGS += -DEG_RELEASE -O3

else
  __unknown_build:
	@echo "Unknown build '$(build)'."
	@exit 1
endif

ifeq ($(build),)
  __empty_build:
	@echo "Empty build."
	@exit 1
endif

endif # __CORE_MK
