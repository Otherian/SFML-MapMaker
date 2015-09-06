#include "SaveButton.hpp"
#include <iostream>

namespace mm
{
	SaveButton::SaveButton()
	{
		m_HitRect = sf::IntRect(17, 21, 57, 57);
		m_isActive = false; // nothing to draw here
	}


	SaveButton::~SaveButton()
	{
	}

	bool SaveButton::Update(sf::Vector2i mouseXY)
	{
		return m_HitRect.contains(mouseXY);
	}
}