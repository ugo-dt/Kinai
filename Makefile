ifndef __KINAI_MK
__KINAI_MK = 1

ifndef KINAI_PATH
  KINAI_PATH = $(CURDIR)
endif

include $(KINAI_PATH)/make/lib.mk

KINAI = $(KINAI_PATH)/bin/$(target)/$(backend)/$(build)/libKinai.a
KINAI_SRC = $(wildcard					\
	$(KINAI_PATH)/src/Core/*.cpp		\
	$(KINAI_PATH)/src/Debug/*.cpp		\
	$(KINAI_PATH)/src/GUI/*.cpp			\
	$(KINAI_PATH)/src/GUI/Widgets/*.cpp	\
	$(KINAI_PATH)/src/Renderer/*.cpp	\
	$(KINAI_PATH)/src/Renderer/2D/*.cpp	\
)

ifdef __kinai_backend_opengl
  KINAI_SRC += $(wildcard $(KINAI_PATH)/src/Platform/OpenGL/*.cpp)
  ifdef __kinai_target_emscripten
    KINAI_SRC += $(wildcard $(KINAI_PATH)/src/Platform/Emscripten/*.cpp)
  else
    KINAI_SRC += $(wildcard $(KINAI_PATH)/src/Platform/SDL/*.cpp)
  endif
else ifdef __kinai_backend_headless
  KINAI_SRC += $(wildcard $(KINAI_PATH)/src/Platform/Headless/*.cpp)
endif

ifdef __kinai_backend_sokol
  KINAI_SRC += $(wildcard $(KINAI_PATH)/src/Sokol/*.cpp)
endif

KINAI_OBJS = $(patsubst $(KINAI_PATH)/src/%.cpp,$(__kinai_objs_dir)/%.o,$(KINAI_SRC))
INCLUDE += -I $(KINAI_PATH)/include -I $(KINAI_PATH)/include/Kinai -I $(KINAI_PATH) -I $(KINAI_PATH)/../glm

CFLAGS		+= -DKINAI_PATH=\"$(KINAI_PATH)/\"
CXXFLAGS	+= -DKINAI_PATH=\"$(KINAI_PATH)/\"

$(info Target: $(target))
$(info Rendering backend: $(backend))
$(info Build: $(build))

all: $(KINAI)

$(KINAI): $(LIB_OBJS) $(KINAI_OBJS)
	$(SILENT)mkdir -p $(dir $@)
	$(SILENT)$(AR) rcs $(KINAI) $(KINAI_OBJS) $(LIB_OBJS)
	@echo "$(COLOR_GREEN)Successfully built $(notdir $(KINAI)) ($(backend) - $(target) - $(build)) $(COLOR_DEFAULT)"

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
