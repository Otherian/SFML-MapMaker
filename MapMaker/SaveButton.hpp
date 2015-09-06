#pragma once
#include "VisibleObject.hpp"

namespace mm
{
	class SaveButton : public VisibleObject
	{
	public:
		SaveButton();
		~SaveButton();

		bool Update(sf::Vector2i mouseXY);
	};
}