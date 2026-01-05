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
__glm_path			= $(__default_lib_path)/../../glm

# SDL3
__sdl3_path			= $(__default_lib_path)/SDL3

# Sokol
__sokol_path		= $(__default_lib_path)/sokol
__sokol_src			= $(wildcard $(__sokol_path)/*.c)
ifeq ($(target),$(__EMSCRIPTEN__))
  CFLAGS			+= -DSOKOL_GLES3
  CXXFLAGS			+= -DSOKOL_GLES3
  __sokol_src		+= $(wildcard $(__sokol_path)/wgpu/*.c)
  SOKOL_SLANG		= glsl300es
else
  CFLAGS			+= -DSOKOL_GLCORE -DSOKOL_EXTERNAL_GL_LOADER
  CXXFLAGS			+= -DSOKOL_GLCORE -DSOKOL_EXTERNAL_GL_LOADER
  SOKOL_SLANG		= glsl410
endif
__sokol_objs		= $(patsubst $(__sokol_path)/%.c,$(__lib_obj_dir)/sokol/%.o,$(__sokol_src))

__lib_include		=	-I $(__default_lib_path)	\
						-I $(__glm_path)			\
						-I $(__glad_path)/include	\
						-I $(__sdl3_path)/include

INCLUDE				+= $(__lib_include)
LIB_OBJS			= $(__glad_objs) $(__sokol_objs)

ifdef __kinai_backend_opengl
	ifeq ($(target),$(__MACOS__))
		LDFLAGS += $(shell pkg-config --libs SDL3)
	else ifeq ($(target),$(__WIN32__))
		LDFLAGS += $(__sdl3_path)/bin/$(target)/libSDL3.dll.a
	else
		LDFLAGS += -L $(__sdl3_path)/bin/$(target) -lSDL3
	endif
endif

$(__lib_obj_dir)/glad/%.o: $(__glad_path)/src/%.c
	@echo "$(COLOR_GREY)Compiling $<...$(COLOR_DEFAULT)"
	$(SILENT)mkdir -p $(dir $@)
	$(SILENT)$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(__lib_obj_dir)/sokol/%.o: $(__sokol_path)/%.c
	@echo "$(COLOR_GREY)Compiling $<...$(COLOR_DEFAULT)"
	$(SILENT)mkdir -p $(dir $@)
	$(SILENT)$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

endif # __LIB_MK
