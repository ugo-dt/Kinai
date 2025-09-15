#pragma once

#include "Kinai/Core/Core.hpp"

namespace Kinai
{

using KeyCode = uint16_t;

namespace Key
{

// SDL3/SDL_Scancode.h
enum : KeyCode
{
	None = 0,
	A = 4,
	B = 5,
	C = 6,
	D = 7,
	E = 8,
	F = 9,
	G = 10,
	H = 11,
	I = 12,
	J = 13,
	K = 14,
	L = 15,
	M = 16,
	N = 17,
	O = 18,
	P = 19,
	Q = 20,
	R = 21,
	S = 22,
	T = 23,
	U = 24,
	V = 25,
	W = 26,
	X = 27,
	Y = 28,
	Z = 29,

	D1 = 30,
	D2 = 31,
	D3 = 32,
	D4 = 33,
	D5 = 34,
	D6 = 35,
	D7 = 36,
	D8 = 37,
	D9 = 38,
	D0 = 39,

	Return = 40,
	Escape = 41,
	Backspace = 42,
	Tab = 43,
	Space = 44,
	Minus = 45,
	Equals = 46,
	LeftBracket = 47,
	RightBracket = 48,
	Backslash = 49,
	NonUsHash = 50,
	Semicolon = 51,
	Apostrophe = 52,
	GraveAccent = 53,
	Comma = 54,
	Period = 55,
	Slash = 56,
	CapsLock = 57,

	F1 = 58,
	F2 = 59,
	F3 = 60,
	F4 = 61,
	F5 = 62,
	F6 = 63,
	F7 = 64,
	F8 = 65,
	F9 = 66,
	F10 = 67,
	F11 = 68,
	F12 = 69,

	PrintScreen = 70,
	ScrollLock = 71,
	Pause = 72,
	Insert = 73, /**< insert on PC, help on some Mac keyboards (but
								does send code 73, not 117) */
	Home = 74,
	PageUp = 75,
	Delete = 76,
	End = 77,
	PageDown = 78,
	Right = 79,
	Left = 80,
	Down = 81,
	Up = 82,

	NumLockClear = 83, /**< num lock on PC, clear on Mac keyboards
									*/
	KPDivide = 84,
	KPMultiply = 85,
	KPSubtract = 86,
	KPAdd = 87,
	KPEnter = 88,
	KP1 = 89,
	KP2 = 90,
	KP3 = 91,
	KP4 = 92,
	KP5 = 93,
	KP6 = 94,
	KP7 = 95,
	KP8 = 96,
	KP9 = 97,
	KP0 = 98,
	KPPeriod = 99,
	NonUsBackslash = 100,
	Application = 101, /**< windows contextual menu, compose */
	Power = 102, /**< The USB document says this is a status flag,
							*   not a physical key - but some Mac keyboards
							*   do have a power key. */
	KPEquals = 103,
	F13 = 104,
	F14 = 105,
	F15 = 106,
	F16 = 107,
	F17 = 108,
	F18 = 109,
	F19 = 110,
	F20 = 111,
	F21 = 112,
	F22 = 113,
	F23 = 114,
	F24 = 115,
	Execute = 116,
	Help = 117,    /**< AL Integrated Help Center */
	Menu = 118,    /**< Menu (show menu) */
	Select = 119,
	Stop = 120,    /**< AC Stop */
	Again = 121,   /**< AC Redo/Repeat */
	Undo = 122,    /**< AC Undo */
	Cut = 123,     /**< AC Cut */
	Copy = 124,    /**< AC Copy */
	Paste = 125,   /**< AC Paste */
	Find = 126,    /**< AC Find */
	Mute = 127,
	VolumeUp = 128,
	VolumeDown = 129,
	KPComma = 133,
	KPEqualsAs400 = 134,

	Alterase = 153,    /**< Erase-Eaze */
	SysReq = 154,
	Cancel = 155,      /**< AC Cancel */
	Clear = 156,
	Prior = 157,
	Return2 = 158,
	Separator = 159,
	Out = 160,
	Oper = 161,
	ClearAgain = 162,
	CrSel = 163,
	ExSel = 164,

	LeftCtrl = 224,
	LeftShift = 225,
	LeftAlt = 226, /**< alt, option */
	LeftSuper = 227, /**< windows, command (apple), meta */
	RightCtrl = 228,
	RightShift = 229,
	RightAlt = 230, /**< alt gr, option */
	RightSuper = 231, /**< windows, command (apple), meta */
	KeyCode_NUM
};

}

} // Kinai
