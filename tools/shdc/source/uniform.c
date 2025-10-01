#include "shdc.h"

struct CType*	match_ctype(const char* type)
{
	for (size_t i = 0; i < ft_vector_size(&shdc.ctypes); i++)
	{
		struct CType* ctype = ft_vector_at(&shdc.ctypes, i);
		if (ft_strcmp(ctype->name, type) == 0)
			return ctype;
	}
	return NULL;
}

int	get_array_count(const char* name)
{
	int array_count = 1;
	const char* p = name;
	while (*p != ';' && *p != '\0')
	{
		if (*p == '[')
		{
			p++;
			shdc_expect(ft_isdigit(*p), NULL, "invalid array declaration in uniform '%s'", name);

			array_count = array_count * ft_atoi(p);
			while (ft_isdigit(*p))
				p++;

			shdc_expect(*p == ']', NULL, "invalid array declaration in uniform '%s'", name);

			if (*(++p) == '[')
				array_count = array_count * get_array_count(p);
			return array_count;
		}
		p++;
	}
	return 1;
}

static inline bool	is_sampler_type(const char* type)
{
	return (ft_strcmp(type, "sampler2D") == 0 ||
			ft_strcmp(type, "samplerCube") == 0);
}

void	add_uniform(const char* type, const char* name, ShaderStage stage, FileParse_Token* token)
{
	struct Uniform	uniform;

	uniform.original_type = type;
	if (is_sampler_type(type))
		return ;

	uniform.glsl_name = name;
	uniform.array_count = 1;
	uniform.token_used = token;
	struct CType* ctype = match_ctype(type);
	if (ctype)
		uniform.ctype = ctype->ctype;
	else
		uniform.ctype = type;
	
	uniform.array_count = get_array_count(uniform.glsl_name);
	if (stage == ShaderStage_Vertex)
		ft_vector_push_back(&shdc.vs.params, &uniform);
	else if (stage == ShaderStage_Fragment)
		ft_vector_push_back(&shdc.fs.params, &uniform);
	else
		assert(false && "invalid shader stage");
}

void	write_params(ShaderStage stage)
{
	ft_vector* params = (stage == ShaderStage_Vertex) ? &shdc.vs.params : &shdc.fs.params;
	if (ft_vector_size(params) == 0)
		return ;
	write_line("#pragma pack(push,1)");
	write_line("KINAI_SHDC_ALIGN(16) typedef struct %s_%s_params_s", shdc.program.name,
		(stage == ShaderStage_Vertex) ? "vs" : "fs");
	write_line("{");
	for (size_t i = 0; i < ft_vector_size(params); i++)
	{
		struct Uniform* uniform = ft_vector_at(params, i);
		write_line("\t%s %s;", uniform->ctype, uniform->glsl_name);
	}
	write_line("}%s_%s_params_t;", shdc.program.name,
		(stage == ShaderStage_Vertex) ? "vs" : "fs");
	write_line("#pragma pack(pop)");
}
