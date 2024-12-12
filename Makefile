ifndef __KINAI_MK
__KINAI_MK = 1

include $(dir $(abspath $(lastword $(MAKEFILE_LIST))))make/lib.mk

KINAI = $(__kinai_root_dir)/bin/$(target)/libKinai.a
KINAI_SRC = $(wildcard								\
	$(__kinai_root_dir)/src/Core/*.cpp				\
	$(__kinai_root_dir)/src/ImGui/*.cpp				\
	$(__kinai_root_dir)/src/Renderer/*.cpp			\
	$(__kinai_root_dir)/src/Core/*.cpp				\
	$(__kinai_root_dir)/src/Platform/SDL/*.cpp		\
	$(__kinai_root_dir)/src/Platform/OpenGL/*.cpp	\
)

ifeq ($(target),$(__EMSCRIPTEN__))
  KINAI_SRC += $(wildcard $(__kinai_root_dir)/src/Kinai/Platform/Emscripten/*.cpp)
endif

__kinai_objs_dir = $(__kinai_root_dir)/$(OBJS_DIR)

# Backend
CFLAGS += -DEG_OPENGL
CXXFLAGS += -DEG_OPENGL

KINAI_OBJS = $(patsubst $(__kinai_root_dir)/src/%.cpp,$(__kinai_objs_dir)/%.o,$(KINAI_SRC))
INCLUDE += -I $(__kinai_root_dir)/include -I $(__kinai_root_dir)/include/Kinai

all: $(KINAI)

$(KINAI): $(LIB_OBJS) $(KINAI_OBJS)
	$(SILENT)mkdir -p $(dir $@)
	$(SILENT)$(AR) rcs $(KINAI) $(KINAI_OBJS) $(LIB_OBJS)
	@echo "$(COLOR_GREEN)Successfully built $(KINAI) $(COLOR_DEFAULT)"

$(__kinai_objs_dir)/%.o: $(__kinai_root_dir)/src/%.cpp
	@echo "$(COLOR_GREY)Compiling $<...$(COLOR_DEFAULT)"
	$(SILENT)mkdir -p $(dir $@)
	$(SILENT)$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -o $@

endif # __KINAI_MK
