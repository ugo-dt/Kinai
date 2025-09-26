#include "Kinai/Debug/Profiler.hpp"

namespace Kinai
{

std::string Profiler::_name;
std::vector<Profiler::ScopedResults> Profiler::_results;

Profiler::Scoped::Scoped(const std::string& name)
	: _name(name)
{
}

Profiler::Scoped::~Scoped()
{
	Profiler::EndScoped(_name, _timer.ElapsedMS());
}

void	Profiler::Start(const std::string& name)
{
	_name = name;
	_results.clear();
}

void	Profiler::EndScoped(const std::string& name, float ms)
{
	_results.push_back({name, ms});
}

void Profiler::End()
{
	float total_time = 0.0f;
	std::unordered_map<std::string, int> counts;
	std::unordered_map<std::string, float> times;

	// Calculate total time, counts, and total times per name
	for (const auto& r : _results)
	{
		total_time += r.ms;
		counts[r.name]++;
		times[r.name] += r.ms;
	}

	// Prepare results for sorting by average time (descending)
	struct ResultEntry {
		std::string name;
		int count;
		float total_time;
		float avg_time;
	};
	std::vector<ResultEntry> entries;
	for (const auto& pair : counts)
	{
		const std::string& name = pair.first;
		int count = pair.second;
		float time = times[name];
		float avg = (count > 0) ? (time / count) : 0.0f;
		entries.push_back({name, count, time, avg});
	}

	std::sort(entries.begin(), entries.end(), [](const ResultEntry& a, const ResultEntry& b) {
		return a.avg_time > b.avg_time; // longest avg first
	});

	printf("=== Profiling results for '%s' (total %.3f ms) ===\n", _name.c_str(), total_time);
	for (const auto& entry : entries)
	{
		float percentage = (total_time > 0.0f) ? (entry.total_time / total_time * 100.0f) : 0.0f;
		printf("%s: %.3f ms (%.2f%%) over %d calls (avg %.3f ms)\n",
			entry.name.c_str(), entry.total_time, percentage, entry.count, entry.avg_time);
	}
	printf("=== End of profiling results ===\n");
}

} // Kinai
