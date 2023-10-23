#pragma once
#include "constants.hpp"

namespace shape
{
	template <typename number = int>
	class Dot
	{
		public:
			number x = 0;
			number y = 0;
			Dot() = default;
			Dot(number x, number y)
			{
				this->x = x;
				this->y = y;
			};
	};

	template <typename number = int>
	class Rect
	{
		public:
			Dot<number> position;
			number width = 0;
			number height = 0;
			Rect() = default;
			Rect(const number width, const number height, const Dot<number> position = {})
			{
				this->width = width;
				this->height = height;
				this->position = position;
				this->no_negative_size();
			};
			Rect(const Dot<number> from, const Dot<number> to = from)
			{
				this->position = from;
				this->width = to.x - from.x;
				this->height = to.y - from.y;
				this->no_negative_size();
			};
			inline Dot<number> get_absolute(const Dot<number> relative)
			{
				return {relative.x + this->position.x, relative.y + this->position.y};
			};
			Dot<number> get_absolute(const choice::relative_pos relative) const
			{
				if (!((relative & choice::relative_pos::Center) && (relative & choice::relative_pos::Middle)))
				{
					throw error::ChoiceError();
				};
				Dot<number> result;
				if (relative & choice::relative_pos::Left)
				{
					result.x += this->position.x;
				};
				if (relative & choice::relative_pos::Right)
				{
					result.x += this->position.x + this->width;
				};
				if (relative & choice::relative_pos::Top)
				{
					result.y += this->position.y;
				};
				if (relative & choice::relative_pos::Bottom)
				{
					result.y += this->position.y + this->height;
				};
				if (relative & choice::relative_pos::Center) // Includes Left & Right
				{
					result.x /= 2;
				};
				if (relative & choice::relative_pos::Middle) // Includes Top & Bottom
				{
					result.y /= 2;
				};
				return result;
			};
			inline void set_absolute(const Dot<number> relative, const Dot<number> absolute)
			{
				this->position.x = absolute.x - relative.x;
				this->position.y = absolute.y - relative.y;
			};
			inline void set_absolute(const choice::relative_pos relative, const Dot<number> absolute)
			{
				this->set_absolute(this->get_absolute(relative), absolute);
			};
			void stretch(const choice::relative_pos relative, const Dot<number> absolute)
			{
				Dot<number> original_absolute = this->get_absolute(relative);
				this->width = absolute.x - original_absolute.x;
				this->height = absolute.y - original_absolute.y;
				this->no_negative_size();
			};
		protected:
			inline void no_negative_size()
			{
				if (this->width < 0)
				{
					this->width = 0;
				};
				if (this->height < 0)
				{
					this->height = 0;
				};
			};
	};
};