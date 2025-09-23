#include "Kinai/Renderer/Shader.hpp"
#include "Kinai/Renderer/Renderer.hpp"

#if defined(KINAI_HEADLESS)
	#include "Kinai/Platform/Headless/HeadlessShader.hpp"
#elif defined(KINAI_OPENGL)
	#include "Kinai/Platform/OpenGL/OpenGLShader.hpp"
#endif

namespace Kinai
{

uint32_t	ShaderDataTypeSize(ShaderDataType type)
{
	switch (type)
	{
		case ShaderDataType::None:		return 0;
		case ShaderDataType::Float:		return sizeof(float) * 1;
		case ShaderDataType::Float2:	return sizeof(float) * 2;
		case ShaderDataType::Float3:	return sizeof(float) * 3;
		case ShaderDataType::Float4:	return sizeof(float) * 4;
		case ShaderDataType::Mat3:		return sizeof(float) * 3 * 3;
		case ShaderDataType::Mat4:		return sizeof(float) * 4 * 4;
		case ShaderDataType::Int:		return sizeof(int) * 1;
		case ShaderDataType::Int2:		return sizeof(int) * 2;
		case ShaderDataType::Int3:		return sizeof(int) * 3;
		case ShaderDataType::Int4:		return sizeof(int) * 4;
		case ShaderDataType::Bool:		return sizeof(bool);
		case ShaderDataType::UByte:		return sizeof(unsigned char) * 1;
		case ShaderDataType::UByte2:	return sizeof(unsigned char) * 2;
		case ShaderDataType::UByte3:	return sizeof(unsigned char) * 3;
		case ShaderDataType::UByte4:	return sizeof(unsigned char) * 4;
		case ShaderDataType::UInt:		return sizeof(unsigned int) * 1;
		case ShaderDataType::UInt2:		return sizeof(unsigned int) * 2;
		case ShaderDataType::UInt3:		return sizeof(unsigned int) * 3;
		case ShaderDataType::UInt4:		return sizeof(unsigned int) * 4;
	}

	Log::Critical("Unknown ShaderDataType");
	return 0;
}

Ref<Shader> Shader::Create(const std::string& filepath, const std::string& program_name)
{
	KN_PRINT_FUNC();

#if defined(KINAI_HEADLESS)
	return CreateRef<HeadlessShader>(filepath, program_name);
#elif defined(KINAI_OPENGL)
	return CreateRef<OpenGLShader>(filepath, program_name);
#endif

	Log::Critical("Unknown RendererAPI!");
	return nullptr;
}

Ref<Shader> Shader::Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
{
	KN_PRINT_FUNC();

#if defined(KINAI_HEADLESS)
	return CreateRef<HeadlessShader>(name, vertexSrc, fragmentSrc);
#elif defined(KINAI_OPENGL)
	return CreateRef<OpenGLShader>(name, vertexSrc, fragmentSrc);
#endif

	Log::Critical("Unknown RendererAPI!");
	return nullptr;
}

Ref<Shader> Shader::Create(const ShaderConfig& config)
{
	KN_PRINT_FUNC();

#if defined(KINAI_HEADLESS)
	return CreateRef<HeadlessShader>(config);
#elif defined(KINAI_OPENGL)
	return CreateRef<OpenGLShader>(config);
#endif

	Log::Critical("Unknown RendererAPI!");
	return nullptr;
}

void ShaderLibrary::Add(const std::string& name, const Ref<Shader>& shader)
{
	KN_PRINT_FUNC();

	KN_ASSERT(!Exists(name), "Shader {} already exists!", name);
	_shaders[name] = shader;
}

void ShaderLibrary::Add(const Ref<Shader>& shader)
{
	KN_PRINT_FUNC();

	auto& name = shader->GetName();
	Add(name, shader);
}

Ref<Shader> ShaderLibrary::Load(const std::string& filepath, const std::string& name)
{
	KN_PRINT_FUNC();

	auto shader = Shader::Create(filepath, name);
	Add(name, shader);
	return shader;
}

Ref<Shader> ShaderLibrary::Load(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
{
	KN_PRINT_FUNC();

	auto shader = Shader::Create(name, vertexSrc, fragmentSrc);
	Add(name, shader);
	return shader;
}

Ref<Shader> ShaderLibrary::Get(const std::string& name)
{
	KN_PRINT_FUNC();

	KN_ASSERT(Exists(name) && "Shader not found!");
	return _shaders[name];
}

bool ShaderLibrary::Exists(const std::string& name) const
{
	KN_PRINT_FUNC();

	return _shaders.find(name) != _shaders.end();
}

} // Kinai
