#pragma once

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

	using Entity::Update;
	bool Update(const char* text);
	void Render() const override;

	float GetWidth() const override;
	float GetHeight() const override;

private:
	std::string _text;
};

void Text(const char* str);

template <class... Args>
static void Text(const char* fmt, ...)
{
	char s[4096];
	va_list args;
	va_start(args, fmt);
	std::vsnprintf(const_cast<char*>(s), sizeof(s), fmt, args);
	va_end(args);
	s[sizeof(s) - 1] = '\0';
	Text(s);
}

} // GUI

} // Kinai
