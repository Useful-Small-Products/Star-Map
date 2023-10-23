#pragma once
#include <string>

namespace choice
{
	enum relative_pos
	{
		Left   = 0b0001,
		Right  = 0b0010,
		Top    = 0b0100,
		Bottom = 0b1000,
		Center = Left | Right,
		Middle = Top | Bottom
	};
};

namespace error
{
	class BasicError : public std::exception
	{
		public:
			std::string reason;
			BasicError() = default;
			BasicError(std::string reason)
			{
				this->reason = reason;
			};
	};
	class ChoiceError : public BasicError {};
};