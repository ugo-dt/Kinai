#include "Kinai/Renderer/Shader.hpp"
#include "Kinai/Renderer/Renderer.hpp"
#include "Kinai/Platform/OpenGL/OpenGLShader.hpp"

#if defined(KINAI_HEADLESS)
#include "Kinai/Platform/Headless/HeadlessShader.hpp"
#elif defined(KINAI_OPENGL)
#include "Kinai/Platform/OpenGL/OpenGLShader.hpp"
#endif

namespace Kinai
{

Ref<Shader> Shader::Create(const std::string& filepath, const std::string& program_name)
{
	KN_PRINT_FUNC();

#if defined(KINAI_HEADLESS)
	return CreateRef<HeadlessShader>(filepath, program_name);
#elif defined(KINAI_OPENGL)
	return CreateRef<OpenGLShader>(filepath, program_name);
#endif

	KN_ASSERT(false, "Unknown RendererAPI!");
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

	KN_ASSERT(false, "Unknown RendererAPI!");
	return nullptr;
}

void ShaderLibrary::Add(const std::string& name, const Ref<Shader>& shader)
{
	KN_PRINT_FUNC();

	KN_ASSERT(!Exists(name) && "Shader already exists!");
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
