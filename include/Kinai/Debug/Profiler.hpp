#pragma once

#include "Kinai/Core/Core.hpp"
#include "Kinai/Core/Application.hpp"
#include "Kinai/Core/Timer.hpp"

namespace Kinai
{

class Profiler
{
public:
	class Scoped
	{
	public:
		Scoped(const std::string& name);
		~Scoped();

	private:
		std::string _name;
		Timer _timer;
	};

private:
	struct ScopedResults
	{
		std::string name;
		float ms = 0.0f;
	};
	static void EndScoped(const std::string& name, float ms);

	friend class Application;
	static void Start(const std::string& name);
	static void End();

private:
	static std::string _name;
	static std::vector<ScopedResults> _results;
};

} // Kinai
