ifndef __KINAI_MK
__KINAI_MK = 1

ifndef KINAI_PATH
  KINAI_PATH = $(CURDIR)
endif

include $(KINAI_PATH)/make/lib.mk

KINAI = $(KINAI_PATH)/bin/$(target)/libKinai.a
KINAI_SRC = $(wildcard						\
	$(KINAI_PATH)/src/Core/*.cpp			\
	$(KINAI_PATH)/src/ImGui/*.cpp			\
	$(KINAI_PATH)/src/Renderer/*.cpp		\
)

ifeq ($(target),$(__EMSCRIPTEN__))
  KINAI_SRC += $(wildcard $(KINAI_PATH)/src/Platform/Emscripten/*.cpp)
endif

ifeq ($(backend),OpenGL)
  KINAI_SRC += $(wildcard $(KINAI_PATH)/src/Platform/OpenGL/*.cpp)
  KINAI_SRC += $(wildcard $(KINAI_PATH)/src/Platform/SDL/*.cpp)
else ifeq ($(backend),Headless)
  KINAI_SRC += $(wildcard $(KINAI_PATH)/src/Platform/Headless/*.cpp)
endif

KINAI_OBJS = $(patsubst $(KINAI_PATH)/src/%.cpp,$(__kinai_objs_dir)/%.o,$(KINAI_SRC))
INCLUDE += -I $(KINAI_PATH)/include -I $(KINAI_PATH)/include/Kinai -I $(KINAI_PATH)

CFLAGS		+= -DKINAI_PATH=\"./lib/Kinai/\"
CXXFLAGS	+= -DKINAI_PATH=\"./lib/Kinai/\"

$(info Target: $(target))
$(info Rendering backend: $(backend))

all: $(KINAI)

# Examples
include $(KINAI_PATH)/make/examples.mk

$(KINAI): $(LIB_OBJS) $(KINAI_OBJS)
	$(SILENT)mkdir -p $(dir $@)
	$(SILENT)$(AR) rcs $(KINAI) $(KINAI_OBJS) $(LIB_OBJS)
	@echo "$(COLOR_GREEN)Successfully built $(notdir $(KINAI)) $(COLOR_DEFAULT)"

$(__kinai_objs_dir)/%.o: $(KINAI_PATH)/src/%.cpp
	@echo "$(COLOR_GREY)Compiling $<...$(COLOR_DEFAULT)"
	$(SILENT)mkdir -p $(dir $@)
	$(SILENT)$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -o $@

clean::
	$(SILENT)rm -rf $(KINAI_OBJS)

fclean::
	$(SILENT)$(MAKE) $(NO_PRINT_DIRECTORY) clean
	$(SILENT)rm -rf ./bin/$(target) $(KINAI)

re::
	$(SILENT)$(MAKE) $(NO_PRINT_DIRECTORY) fclean
	$(SILENT)$(MAKE) $(NO_PRINT_DIRECTORY) all

endif # __KINAI_MK
