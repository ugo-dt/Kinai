ifndef __LIB_MK
__LIB_MK = 1

ifndef KINAI_PATH
	"Error: No KINAI_PATH."
endif

include $(KINAI_PATH)/make/__platform.mk

__kinai_objs_dir = $(KINAI_PATH)/$(OBJS_DIR)
__default_lib_path	= $(KINAI_PATH)/lib

# Compile the libs in a separate 'lib' folder to avoid recompiling
__lib_obj_dir		= $(__kinai_objs_dir)/lib

# Glad
__glad_path			= $(__default_lib_path)/glad
__glad_src			= $(__glad_path)/src/glad.c
__glad_objs			= $(patsubst $(__glad_path)/src/%.c,$(__lib_obj_dir)/glad/%.o,$(__glad_src))

# GLM
__glm_path			= $(__default_lib_path)/glm

# ImGui
__imgui_path		= $(__default_lib_path)/imgui
__imgui_backend		= opengl3
__imgui_platform	= sdl3
__imgui_src			= $(wildcard $(__imgui_path)/*.cpp) $(__imgui_path)/backends/imgui_impl_$(__imgui_backend).cpp  $(__imgui_path)/backends/imgui_impl_$(__imgui_platform).cpp
__imgui_objs		= $(patsubst $(__imgui_path)/%.cpp,$(__lib_obj_dir)/imgui/%.o,$(__imgui_src))

# SDL3
__sdl3_path			= $(__default_lib_path)/SDL3

# # Sokol
# __sokol_path		= $(__default_lib_path)/sokol
# __sokol_src			= $(wildcard $(__sokol_path)/*.c)
# ifeq ($(target),$(__EMSCRIPTEN__))
#   CFLAGS			+= -DSOKOL_GLES3
#   CXXFLAGS			+= -DSOKOL_GLES3
#   __sokol_src		+= $(wildcard $(__sokol_path)/wgpu/*.c)
# else
#   CFLAGS			+= -DSOKOL_GLCORE -DSOKOL_EXTERNAL_GL_LOADER
#   CXXFLAGS			+= -DSOKOL_GLCORE -DSOKOL_EXTERNAL_GL_LOADER
# endif
# __sokol_objs		= $(patsubst $(__sokol_path)/%.c,$(__lib_obj_dir)/sokol/%.o,$(__sokol_src))

# stb_image
__stb_image_path	= $(__default_lib_path)/stb
__stb_image_src		= $(__stb_image_path)/stb_image.c
__stb_image_objs	= $(patsubst $(__stb_image_path)/%.c,$(__lib_obj_dir)/stb_image/%.o,$(__stb_image_src))

__lib_include		=	-I $(__default_lib_path)	\
						-I $(__glad_path)/include	\
						-I $(__imgui_path)			\
						-I $(__imgui_path)/backends \
						-I $(__glm_path)			\
						-I $(__sdl3_path)/include

INCLUDE				+= $(__lib_include)
LIB_OBJS			= $(__glad_objs) $(__imgui_objs) $(__stb_image_objs)

ifeq ($(target),$(__MACOS__))
LDFLAGS			+= $(shell pkg-config --libs SDL3)
else ifeq ($(target),$(__WIN32__))
LDFLAGS			+= $(__sdl3_path)/bin/$(target)/libSDL3.dll.a
else
LDFLAGS			+= -L $(__sdl3_path)/bin/$(target) -lSDL3
endif

$(__lib_obj_dir)/glad/%.o: $(__glad_path)/src/%.c
	@echo "$(COLOR_GREY)Compiling $<...$(COLOR_DEFAULT)"
	$(SILENT)mkdir -p $(dir $@)
	$(SILENT)$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(__lib_obj_dir)/imgui/%.o: $(__imgui_path)/%.cpp
	@echo "$(COLOR_GREY)Compiling $<...$(COLOR_DEFAULT)"
	$(SILENT)mkdir -p $(dir $@)
	$(SILENT)$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -o $@

$(__lib_obj_dir)/sokol/%.o: $(__sokol_path)/%.c
	@echo "$(COLOR_GREY)Compiling $<...$(COLOR_DEFAULT)"
	$(SILENT)mkdir -p $(dir $@)
	$(SILENT)$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(__lib_obj_dir)/stb_image/%.o: $(__stb_image_path)/%.c
	@echo "$(COLOR_GREY)Compiling $<...$(COLOR_DEFAULT)"
	$(SILENT)mkdir -p $(dir $@)
	$(SILENT)$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

endif # __LIB_MK
