#include <Kinai/Kinai.hpp>
#include <Kinai/EntryPoint.hpp>

class HelloApplication : public Kinai::Application
{
public:
	HelloApplication(const Kinai::ApplicationConfig &config)
		: Kinai::Application(config)
	{
		std::cout << "Hello Kinai!" << std::endl;
	}

	~HelloApplication() = default;
};

Kinai::Application*	Kinai::CreateApplication(int argc, char **argv)
{
	KN_NOTUSED(argc);
	KN_NOTUSED(argv);

	return new HelloApplication(Kinai::ApplicationConfig{
		.name = "Hello Kinai",
		.window_width = 500,
		.window_height = 500,
	});
}
