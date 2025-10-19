#include "Kinai/Platform/Emscripten/Emscripten.hpp"
#include "Kinai/Core/Input.hpp"

namespace Kinai
{

#define EM_KEYCODE(_name, _key) if (!std::strcmp(e->code, _name)) { return _key; }

KeyCode	Em_KeyEventToKeyCode(const EmscriptenKeyboardEvent* e)
{
	// switch (e->keyCode)
	// {
	// 	// case DOM_VK_CANCEL: return Key::;
	// 	// case DOM_VK_HELP: return Key::;
	// 	case DOM_VK_BACK_SPACE: return Key::Backspace;
	// 	case DOM_VK_TAB: return Key::Tab;
	// 	// case DOM_VK_CLEAR: return Key::;
	// 	case DOM_VK_RETURN: return Key::Return;
	// 	case DOM_VK_ENTER: return Key::KPEnter;
	// 	case DOM_VK_SHIFT: return e->location == 1 ? Key::LeftShift : Key::RightShift;
	// 	case DOM_VK_CONTROL: return e->location == 1 ? Key::LeftCtrl : Key::RightCtrl;
	// 	case DOM_VK_ALT: return e->location == 1 ? Key::LeftAlt : Key::RightAlt;
	// 	case DOM_VK_PAUSE: return Key::Pause;
	// 	case DOM_VK_CAPS_LOCK: return Key::CapsLock;
	// 	// case DOM_VK_KANA: return Key::;
	// 	// case DOM_VK_HANGUL: return Key::;
	// 	// case DOM_VK_EISU: return Key::;
	// 	// case DOM_VK_JUNJA: return Key::;
	// 	// case DOM_VK_FINAL: return Key::;
	// 	// case DOM_VK_HANJA: return Key::;
	// 	// case DOM_VK_KANJI: return Key::;
	// 	case DOM_VK_ESCAPE: return Key::Escape;
	// 	// case DOM_VK_CONVERT: return Key::;
	// 	// case DOM_VK_NONCONVERT: return Key::;
	// 	// case DOM_VK_ACCEPT: return Key::;
	// 	// case DOM_VK_MODECHANGE: return Key::;
	// 	case DOM_VK_SPACE: return Key::Space;
	// 	case DOM_VK_PAGE_UP: return Key::PageUp;
	// 	case DOM_VK_PAGE_DOWN: return Key::PageDown;
	// 	case DOM_VK_END: return Key::End;
	// 	case DOM_VK_HOME: return Key::Home;
	// 	case DOM_VK_LEFT: return Key::Left;
	// 	case DOM_VK_UP: return Key::Up;
	// 	case DOM_VK_RIGHT: return Key::Right;
	// 	case DOM_VK_DOWN: return Key::Down;
	// 	// case DOM_VK_SELECT: return Key::;
	// 	// case DOM_VK_PRINT: return Key::;
	// 	// case DOM_VK_EXECUTE: return Key::;
	// 	case DOM_VK_PRINTSCREEN: return Key::PrintScreen;
	// 	case DOM_VK_INSERT: return Key::Insert;
	// 	case DOM_VK_DELETE: return Key::Delete;
	// 	case DOM_VK_0: return Key::D0;
	// 	case DOM_VK_1: return Key::D1;
	// 	case DOM_VK_2: return Key::D2;
	// 	case DOM_VK_3: return Key::D3;
	// 	case DOM_VK_4: return Key::D4;
	// 	case DOM_VK_5: return Key::D5;
	// 	case DOM_VK_6: return Key::D6;
	// 	case DOM_VK_7: return Key::D7;
	// 	case DOM_VK_8: return Key::D8;
	// 	case DOM_VK_9: return Key::D9;
	// 	// case DOM_VK_COLON: return Key::;
	// 	case DOM_VK_SEMICOLON: return Key::Semicolon;
	// 	case DOM_VK_LESS_THAN: return Key::LeftBracket;
	// 	case DOM_VK_EQUALS: return Key::Equals;
	// 	case DOM_VK_GREATER_THAN: return Key::RightBracket;
	// 	// case DOM_VK_QUESTION_MARK: return Key::;
	// 	// case DOM_VK_AT: return Key::;
	// 	case DOM_VK_A: return Key::A;
	// 	case DOM_VK_B: return Key::B;
	// 	case DOM_VK_C: return Key::C;
	// 	case DOM_VK_D: return Key::D;
	// 	case DOM_VK_E: return Key::E;
	// 	case DOM_VK_F: return Key::F;
	// 	case DOM_VK_G: return Key::G;
	// 	case DOM_VK_H: return Key::H;
	// 	case DOM_VK_I: return Key::I;
	// 	case DOM_VK_J: return Key::J;
	// 	case DOM_VK_K: return Key::K;
	// 	case DOM_VK_L: return Key::L;
	// 	case DOM_VK_M: return Key::M;
	// 	case DOM_VK_N: return Key::N;
	// 	case DOM_VK_O: return Key::O;
	// 	case DOM_VK_P: return Key::P;
	// 	case DOM_VK_Q: return Key::Q;
	// 	case DOM_VK_R: return Key::R;
	// 	case DOM_VK_S: return Key::S;
	// 	case DOM_VK_T: return Key::T;
	// 	case DOM_VK_U: return Key::U;
	// 	case DOM_VK_V: return Key::V;
	// 	case DOM_VK_W: return Key::W;
	// 	case DOM_VK_X: return Key::X;
	// 	case DOM_VK_Y: return Key::Y;
	// 	case DOM_VK_Z: return Key::Z;
	// 	case DOM_VK_WIN: return e->location == 1 ? Key::LeftSuper : Key::RightSuper;
	// 	case DOM_VK_CONTEXT_MENU: return Key::Menu;
	// 	// case DOM_VK_SLEEP: return Key::;
	// 	case DOM_VK_NUMPAD0: return Key::KP0;
	// 	case DOM_VK_NUMPAD1: return Key::KP1;
	// 	case DOM_VK_NUMPAD2: return Key::KP2;
	// 	case DOM_VK_NUMPAD3: return Key::KP3;
	// 	case DOM_VK_NUMPAD4: return Key::KP4;
	// 	case DOM_VK_NUMPAD5: return Key::KP5;
	// 	case DOM_VK_NUMPAD6: return Key::KP6;
	// 	case DOM_VK_NUMPAD7: return Key::KP7;
	// 	case DOM_VK_NUMPAD8: return Key::KP8;
	// 	case DOM_VK_NUMPAD9: return Key::KP9;
	// 	case DOM_VK_MULTIPLY: return Key::KPMultiply;
	// 	case DOM_VK_ADD: return Key::KPAdd;
	// 	// case DOM_VK_SEPARATOR: return Key::;
	// 	case DOM_VK_SUBTRACT: return Key::KPSubtract;
	// 	case DOM_VK_DECIMAL: return Key::KPPeriod;
	// 	case DOM_VK_DIVIDE: return Key::KPDivide;
	// 	case DOM_VK_F1: return Key::F1;
	// 	case DOM_VK_F2: return Key::F2;
	// 	case DOM_VK_F3: return Key::F3;
	// 	case DOM_VK_F4: return Key::F4;
	// 	case DOM_VK_F5: return Key::F5;
	// 	case DOM_VK_F6: return Key::F6;
	// 	case DOM_VK_F7: return Key::F7;
	// 	case DOM_VK_F8: return Key::F8;
	// 	case DOM_VK_F9: return Key::F9;
	// 	case DOM_VK_F10: return Key::F10;
	// 	case DOM_VK_F11: return Key::F11;
	// 	case DOM_VK_F12: return Key::F12;
	// 	case DOM_VK_F13: return Key::F13;
	// 	case DOM_VK_F14: return Key::F14;
	// 	case DOM_VK_F15: return Key::F15;
	// 	case DOM_VK_F16: return Key::F16;
	// 	case DOM_VK_F17: return Key::F17;
	// 	case DOM_VK_F18: return Key::F18;
	// 	case DOM_VK_F19: return Key::F19;
	// 	case DOM_VK_F20: return Key::F20;
	// 	case DOM_VK_F21: return Key::F21;
	// 	case DOM_VK_F22: return Key::F22;
	// 	case DOM_VK_F23: return Key::F23;
	// 	case DOM_VK_F24: return Key::F24;
	// 	case DOM_VK_NUM_LOCK: return Key::NumLockClear;
	// 	case DOM_VK_SCROLL_LOCK: return Key::ScrollLock;
	// 	// case DOM_VK_WIN_OEM_FJ_JISHO: return Key::;
	// 	// case DOM_VK_WIN_OEM_FJ_MASSHOU: return Key::;
	// 	// case DOM_VK_WIN_OEM_FJ_TOUROKU: return Key::;
	// 	// case DOM_VK_WIN_OEM_FJ_LOYA: return Key::;
	// 	// case DOM_VK_WIN_OEM_FJ_ROYA: return Key::;
	// 	// case DOM_VK_CIRCUMFLEX: return Key::;
	// 	// case DOM_VK_EXCLAMATION: return Key::;
	// 	// case DOM_VK_DOUBLE_QUOTE: return Key::;
	// 	// case DOM_VK_HASH: return Key::;
	// 	// case DOM_VK_DOLLAR: return Key::;
	// 	// case DOM_VK_PERCENT: return Key::;
	// 	// case DOM_VK_AMPERSAND: return Key::;
	// 	// case DOM_VK_UNDERSCORE: return Key::;
	// 	// case DOM_VK_OPEN_PAREN: return Key::;
	// 	// case DOM_VK_CLOSE_PAREN: return Key::;
	// 	case DOM_VK_ASTERISK: return Key::KPMultiply;
	// 	case DOM_VK_PLUS: return Key::KPAdd;
	// 	// case DOM_VK_PIPE: return Key::;
	// 	case DOM_VK_HYPHEN_MINUS: return Key::Minus;
	// 	case DOM_VK_OPEN_CURLY_BRACKET: return Key::LeftBracket;
	// 	case DOM_VK_CLOSE_CURLY_BRACKET: return Key::RightBracket;
	// 	// case DOM_VK_TILDE: return Key::;
	// 	// case DOM_VK_VOLUME_MUTE: return Key::;
	// 	// case DOM_VK_VOLUME_DOWN: return Key::;
	// 	// case DOM_VK_VOLUME_UP: return Key::;
	// 	case DOM_VK_COMMA: return Key::Comma;
	// 	case DOM_VK_PERIOD: return Key::Period;
	// 	case DOM_VK_SLASH: return Key::Slash;
	// 	// case DOM_VK_BACK_QUOTE: return Key::;
	// 	case DOM_VK_OPEN_BRACKET: return Key::LeftBracket;
	// 	case DOM_VK_BACK_SLASH: return Key::Backslash;
	// 	case DOM_VK_CLOSE_BRACKET: return Key::RightBracket;
	// 	// case DOM_VK_QUOTE: return Key::;
	// 	case DOM_VK_META: return e->location == 1 ? Key::LeftSuper : Key::RightSuper;
	// 	case DOM_VK_ALTGR: return Key::RightAlt;
	// 	// case DOM_VK_WIN_ICO_HELP: return Key::;
	// 	// case DOM_VK_WIN_ICO_00: return Key::;
	// 	// case DOM_VK_WIN_ICO_CLEAR: return Key::;
	// 	// case DOM_VK_WIN_OEM_RESET: return Key::;
	// 	// case DOM_VK_WIN_OEM_JUMP: return Key::;
	// 	// case DOM_VK_WIN_OEM_PA1: return Key::;
	// 	// case DOM_VK_WIN_OEM_PA2: return Key::;
	// 	// case DOM_VK_WIN_OEM_PA3: return Key::;
	// 	// case DOM_VK_WIN_OEM_WSCTRL: return Key::;
	// 	// case DOM_VK_WIN_OEM_CUSEL: return Key::;
	// 	// case DOM_VK_WIN_OEM_ATTN: return Key::;
	// 	// case DOM_VK_WIN_OEM_FINISH: return Key::;
	// 	// case DOM_VK_WIN_OEM_COPY: return Key::;
	// 	// case DOM_VK_WIN_OEM_AUTO: return Key::;
	// 	// case DOM_VK_WIN_OEM_ENLW: return Key::;
	// 	// case DOM_VK_WIN_OEM_BACKTAB: return Key::;
	// 	// case DOM_VK_ATTN: return Key::;
	// 	// case DOM_VK_CRSEL: return Key::;
	// 	// case DOM_VK_EXSEL: return Key::;
	// 	// case DOM_VK_EREOF: return Key::;
	// 	// case DOM_VK_PLAY: return Key::;
	// 	// case DOM_VK_ZOOM: return Key::;
	// 	// case DOM_VK_PA1: return Key::;
	// 	// case DOM_VK_WIN_OEM_CLEAR: return Key::;
	// }

	EM_KEYCODE("Escape", Key::Escape);
	EM_KEYCODE("Digit1", Key::D1);
	EM_KEYCODE("Digit2", Key::D2);
	EM_KEYCODE("Digit3", Key::D3);
	EM_KEYCODE("Digit4", Key::D4);
	EM_KEYCODE("Digit5", Key::D5);
	EM_KEYCODE("Digit6", Key::D6);
	EM_KEYCODE("Digit7", Key::D7);
	EM_KEYCODE("Digit8", Key::D8);
	EM_KEYCODE("Digit9", Key::D9);
	EM_KEYCODE("Digit0", Key::D0);
	EM_KEYCODE("Minus", Key::Minus);
	EM_KEYCODE("Equal", Key::Equals);
	EM_KEYCODE("Backspace", Key::Backspace);
	EM_KEYCODE("Tab", Key::Tab);
	EM_KEYCODE("KeyQ", Key::Q);
	EM_KEYCODE("KeyW", Key::W);
	EM_KEYCODE("KeyE", Key::E);
	EM_KEYCODE("KeyR", Key::R);
	EM_KEYCODE("KeyT", Key::T);
	EM_KEYCODE("KeyY", Key::Y);
	EM_KEYCODE("KeyU", Key::U);
	EM_KEYCODE("KeyI", Key::I);
	EM_KEYCODE("KeyO", Key::O);
	EM_KEYCODE("KeyP", Key::P);
	EM_KEYCODE("BracketLeft", Key::LeftBracket);
	EM_KEYCODE("BracketRight", Key::RightBracket);
	EM_KEYCODE("Enter", Key::Return);
	EM_KEYCODE("ControlLeft", Key::LeftCtrl);
	EM_KEYCODE("KeyA", Key::A);
	EM_KEYCODE("KeyS", Key::S);
	EM_KEYCODE("KeyD", Key::D);
	EM_KEYCODE("KeyF", Key::F);
	EM_KEYCODE("KeyG", Key::G);
	EM_KEYCODE("KeyH", Key::H);
	EM_KEYCODE("KeyJ", Key::J);
	EM_KEYCODE("KeyK", Key::K);
	EM_KEYCODE("KeyL", Key::L);
	EM_KEYCODE("Semicolon", Key::Semicolon);
	// EM_KEYCODE("Quote", Key::Quote);
	// EM_KEYCODE("Backquote", Key::BackQuote);
	EM_KEYCODE("ShiftLeft", Key::LeftShift);
	EM_KEYCODE("Backslash", Key::Backslash);
	EM_KEYCODE("KeyZ", Key::Z);
	EM_KEYCODE("KeyX", Key::X);
	EM_KEYCODE("KeyC", Key::C);
	EM_KEYCODE("KeyV", Key::V);
	EM_KEYCODE("KeyB", Key::B);
	EM_KEYCODE("KeyN", Key::N);
	EM_KEYCODE("KeyM", Key::M);
	EM_KEYCODE("Comma", Key::Comma);
	EM_KEYCODE("Period", Key::Period);
	EM_KEYCODE("Slash", Key::Slash);
	EM_KEYCODE("ShiftRight", Key::RightShift);
	EM_KEYCODE("NumpadMultiply", Key::KPMultiply);
	EM_KEYCODE("AltLeft", Key::LeftAlt);
	EM_KEYCODE("Space", Key::Space);
	EM_KEYCODE("CapsLock", Key::CapsLock);
	EM_KEYCODE("F1", Key::F1);
	EM_KEYCODE("F2", Key::F2);
	EM_KEYCODE("F3", Key::F3);
	EM_KEYCODE("F4", Key::F4);
	EM_KEYCODE("F5", Key::F5);
	EM_KEYCODE("F6", Key::F6);
	EM_KEYCODE("F7", Key::F7);
	EM_KEYCODE("F8", Key::F8);
	EM_KEYCODE("F9", Key::F9);
	EM_KEYCODE("F10", Key::F10);
	EM_KEYCODE("F11", Key::F11);
	EM_KEYCODE("F12", Key::F12);
	EM_KEYCODE("F13", Key::F13);
	EM_KEYCODE("F14", Key::F14);
	EM_KEYCODE("F15", Key::F15);
	EM_KEYCODE("F16", Key::F16);
	EM_KEYCODE("F17", Key::F17);
	EM_KEYCODE("F18", Key::F18);
	EM_KEYCODE("F19", Key::F19);
	EM_KEYCODE("F20", Key::F20);
	EM_KEYCODE("F21", Key::F21);
	EM_KEYCODE("F22", Key::F22);
	EM_KEYCODE("F23", Key::F23);
	EM_KEYCODE("F24", Key::F24);
	EM_KEYCODE("Pause", Key::Pause);
	EM_KEYCODE("ScrollLock", Key::ScrollLock);
	EM_KEYCODE("Numpad7", Key::KP7);
	EM_KEYCODE("Numpad8", Key::KP8);
	EM_KEYCODE("Numpad9", Key::KP9);
	EM_KEYCODE("NumpadSubtract", Key::KPSubtract);
	EM_KEYCODE("Numpad4", Key::KP4);
	EM_KEYCODE("Numpad5", Key::KP5);
	EM_KEYCODE("Numpad6", Key::KP6);
	EM_KEYCODE("NumpadAdd", Key::KPAdd);
	EM_KEYCODE("Numpad1", Key::KP1);
	EM_KEYCODE("Numpad2", Key::KP2);
	EM_KEYCODE("Numpad3", Key::KP3);
	EM_KEYCODE("Numpad0", Key::KP0);
	EM_KEYCODE("NumpadDecimal", Key::KPPeriod);
	EM_KEYCODE("PrintScreen", Key::PrintScreen);
	// EM_KEYCODE("IntlBackslash", Key::IntlBackslash);
	EM_KEYCODE("NumpadEqual", Key::KPEquals);
	// EM_KEYCODE("KanaMode", Key::KanaMode);
	// EM_KEYCODE("Lang2", Key::Lang2);
	// EM_KEYCODE("Lang1", Key::Lang1);
	// EM_KEYCODE("IntlRo", Key::IntlRo);
	// EM_KEYCODE("Lang4", Key::Lang4);
	// EM_KEYCODE("Lang3", Key::Lang3);
	// EM_KEYCODE("Convert", Key::Convert);
	// EM_KEYCODE("NonConvert", Key::NonConvert);
	// EM_KEYCODE("IntlYen", Key::IntlYen);
	EM_KEYCODE("NumpadComma", Key::KPPeriod);
	// EM_KEYCODE("Undo", Key::Undo);
	// EM_KEYCODE("Paste", Key::Paste);
	// EM_KEYCODE("MediaTrackPrevious", Key::MediaTrackPrevious);
	// EM_KEYCODE("Cut", Key::Cut);
	// EM_KEYCODE("Copy", Key::Copy);
	// EM_KEYCODE("MediaTrackNext", Key::MediaTrackNext);
	EM_KEYCODE("NumpadEnter", Key::KPEnter);
	EM_KEYCODE("ControlRight", Key::RightCtrl);
	// EM_KEYCODE("AudioVolumeMute", Key::AudioVolumeMute);
	// EM_KEYCODE("LaunchApp2", Key::LaunchApp2);
	// EM_KEYCODE("MediaPlayPause", Key::MediaPlayPause);
	// EM_KEYCODE("MediaStop", Key::MediaStop);
	// EM_KEYCODE("Eject", Key::Eject);
	// EM_KEYCODE("AudioVolumeDown", Key::AudioVolumeDown);
	// EM_KEYCODE("AudioVolumeUp", Key::AudioVolumeUp);
	// EM_KEYCODE("BrowserHome", Key::BrowserHome);
	EM_KEYCODE("NumpadDivide", Key::KPDivide);
	EM_KEYCODE("PrintScreen", Key::PrintScreen);
	EM_KEYCODE("AltRight", Key::RightAlt);
	// EM_KEYCODE("Help", Key::Help);
	EM_KEYCODE("NumLock", Key::NumLockClear);
	EM_KEYCODE("Pause", Key::Pause);
	EM_KEYCODE("Home", Key::Home);
	EM_KEYCODE("ArrowUp", Key::Up);
	EM_KEYCODE("PageUp", Key::PageUp);
	EM_KEYCODE("ArrowLeft", Key::Left);
	EM_KEYCODE("ArrowRight", Key::Right);
	EM_KEYCODE("End", Key::End);
	EM_KEYCODE("ArrowDown", Key::Down);
	EM_KEYCODE("PageDown", Key::PageDown);
	EM_KEYCODE("Insert", Key::Insert);
	EM_KEYCODE("Delete", Key::Delete);
	EM_KEYCODE("MetaLeft", Key::LeftSuper);
	EM_KEYCODE("MetaRight", Key::RightSuper);
	EM_KEYCODE("ContextMenu", Key::Menu);
	// EM_KEYCODE("Power", Key::Power);
	// EM_KEYCODE("Sleep", Key::Sleep);
	// EM_KEYCODE("WakeUp", Key::WakeUp);
	// EM_KEYCODE("BrowserSearch", Key::BrowserSearch);
	// EM_KEYCODE("BrowserFavorites", Key::BrowserFavorites);
	// EM_KEYCODE("BrowserRefresh", Key::BrowserRefresh);
	// EM_KEYCODE("BrowserStop", Key::BrowserStop);
	// EM_KEYCODE("BrowserForward", Key::AppForward);
	// EM_KEYCODE("BrowserBack", Key::AppBack);
	// EM_KEYCODE("LaunchApp1", Key::LaunchApp1);
	// EM_KEYCODE("LaunchMail", Key::LaunchMail);
	// EM_KEYCODE("MediaSelect", Key::MediaSelect);

	return Key::None;
}

bool	Input::IsKeyPressed(KeyCode key)
{
	return EmWindow::IsKeyPressed(key);
}

bool	Input::IsMouseButtonPressed(MouseButton button)
{
	return EmWindow::IsMouseButtonPressed(button);
}

math::vec2	Input::GetMousePosition()
{
	float xpos, ypos;

	SDL_GetMouseState(&xpos, &ypos);
	return math::vec2(xpos, ypos);
}

float	Input::GetMouseX()
{
	return GetMousePosition().x;
}

float	Input::GetMouseY()
{
	return GetMousePosition().y;
}

} // Kinai
