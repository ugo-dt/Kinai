#pragma once

#include "Kinai/GUI/Core.hpp"
#include "Kinai/GUI/Widgets/Widget.hpp"

namespace Kinai
{

namespace GUI
{

class WidgetText : public Widget
{
public:
	WidgetText(Point position, const char* text);
	~WidgetText() = default;

	using Widget::Update;
	bool Update(const char* text);
	void Render() const override;

	float GetWidth() const override;
	float GetHeight() const override;

private:
	std::string _text;
};

void Text(const char* str);

template <class... Args>
static void Text(std::string_view fmt, Args&&... args)
{
	const std::string s = std::vformat(fmt, std::make_format_args(args...));
	Text(s.c_str());
}

} // GUI

} // Kinai
