#include "Kinai/Renderer/Shader.hpp"
#include "Kinai/Renderer/Renderer.hpp"
#include "Kinai/Platform/OpenGL/OpenGLShader.hpp"

#include "Kinai/Platform/Headless/HeadlessShader.hpp"
#include "Kinai/Platform/OpenGL/OpenGLShader.hpp"

namespace Kinai
{

std::shared_ptr<Shader> Shader::Create(const std::string& filepath, const std::string& program_name)
{
	EG_PRINT_FUNC();

#if defined(EG_HEADLESS)
	return std::make_shared<HeadlessShader>(filepath, program_name);
#elif defined(EG_OPENGL)
	return std::make_shared<OpenGLShader>(filepath, program_name);
#endif

	EG_ASSERT(false, "Unknown RendererAPI!");
	return nullptr;
}

std::shared_ptr<Shader> Shader::Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
{
	EG_PRINT_FUNC();

#if defined(EG_HEADLESS)
	return std::make_shared<HeadlessShader>(name, vertexSrc, fragmentSrc);
#elif defined(EG_OPENGL)
	return std::make_shared<OpenGLShader>(name, vertexSrc, fragmentSrc);
#endif

	EG_ASSERT(false, "Unknown RendererAPI!");
	return nullptr;
}

void ShaderLibrary::Add(const std::string& name, const std::shared_ptr<Shader>& shader)
{
	EG_PRINT_FUNC();

	EG_ASSERT(!Exists(name) && "Shader already exists!");
	_shaders[name] = shader;
}

void ShaderLibrary::Add(const std::shared_ptr<Shader>& shader)
{
	EG_PRINT_FUNC();

	auto& name = shader->GetName();
	Add(name, shader);
}

std::shared_ptr<Shader> ShaderLibrary::Load(const std::string& filepath, const std::string& name)
{
	EG_PRINT_FUNC();

	auto shader = Shader::Create(filepath, name);
	Add(name, shader);
	return shader;
}

std::shared_ptr<Shader> ShaderLibrary::Get(const std::string& name)
{
	EG_PRINT_FUNC();

	EG_ASSERT(Exists(name) && "Shader not found!");
	return _shaders[name];
}

bool ShaderLibrary::Exists(const std::string& name) const
{
	EG_PRINT_FUNC();

	return _shaders.find(name) != _shaders.end();
}

} // Kinai
