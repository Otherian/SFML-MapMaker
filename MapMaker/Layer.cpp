#include "Layer.hpp"

namespace mm
{
	Layer::Layer()
		: m_HitRect_BG2(133, 579, 45, 28),
		m_HitRect_BG1(186, 579, 45, 28),
		m_HitRect_Zero(239, 579, 45, 28),
		m_HitRect_FG1(292, 579, 45, 28),
		m_HitRect_FG2(345, 579, 45, 28)

	{
		m_HitRect = sf::IntRect(131, 579, 261, 28);
		m_sprite.setPosition(237, 579);
		m_sprite.setTextureRect(sf::IntRect(1453, 506, 49, 104));
		m_content = 2;
		m_isActive = true;
	}


	Layer::~Layer()
	{
	}

	bool Layer::Update(sf::Vector2i mouseXY)
	{
		if (!m_HitRect.contains(mouseXY))
			return false;

		// which Button?
		if (m_HitRect_BG2.contains(mouseXY))
		{
			m_sprite.setPosition(131, 579);
			m_sprite.setTextureRect(sf::IntRect(1453, 290, 49, 104));
			m_content = 0;
			return true;
		}
		if (m_HitRect_BG1.contains(mouseXY))
		{
			m_sprite.setPosition(184, 579);
			m_sprite.setTextureRect(sf::IntRect(1453, 398, 49, 104));
			m_content = 1;
			return true;
		}
		if (m_HitRect_Zero.contains(mouseXY))
		{
			m_sprite.setPosition(237, 579);
			m_sprite.setTextureRect(sf::IntRect(1453, 506, 49, 104));
			m_content = 2;
			return true;
		}
		if (m_HitRect_FG1.contains(mouseXY))
		{
			m_sprite.setPosition(290, 579);
			m_sprite.setTextureRect(sf::IntRect(1453, 614, 49, 104));
			m_content = 3;
			return true;
		}
		if (m_HitRect_FG2.contains(mouseXY))
		{
			m_sprite.setPosition(343, 579);
			m_sprite.setTextureRect(sf::IntRect(1453, 722, 49, 104));
			m_content = 4;
			return true;
		}
		return false;
	}

	int Layer::GetContent_Int()
	{
		return m_content;
	}
}