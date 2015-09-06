#include "Background.hpp"

namespace mm
{
	Background::Background()
	{
		m_sprite.setTextureRect(sf::IntRect(0, 0, 1440, 900));
		m_sprite.setPosition(0, 0);
		m_isActive = true;
	}


	Background::~Background()
	{
	}
}