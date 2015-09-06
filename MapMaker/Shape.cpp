#include "Shape.hpp"

namespace mm
{
	Shape::Shape()
		: m_HitRect_Quad(25, 576, 32, 32),
		m_HitRect_Empty(63, 576, 32, 32),
		m_HitRect_Tri1(25, 652, 32, 32),
		m_HitRect_Tri2(25, 614, 32, 32),
		m_HitRect_Tri3(63, 652, 32, 32),
		m_HitRect_Tri4(63, 614, 32, 32)
		  
	{
		m_HitRect = sf::IntRect(25, 576, 70, 108);
		m_sprite.setPosition(25, 576);
		m_sprite.setTextureRect(sf::IntRect(1453, 65, 32, 32));
		m_content = 0;
		m_isActive = true;
	}


	Shape::~Shape()
	{
	}

	bool Shape::Update(sf::Vector2i mouseXY)
	{
		if (!m_HitRect.contains(mouseXY))
			return false;

		// which Button?
		if (m_HitRect_Empty.contains(mouseXY))
		{
			m_sprite.setPosition(63, 576);
			m_sprite.setTextureRect(sf::IntRect(1491, 65, 32, 32));
			m_content = 0;
			return true;
		}
		if (m_HitRect_Quad.contains(mouseXY))
		{
			m_sprite.setPosition(25, 576);
			m_sprite.setTextureRect(sf::IntRect(1453, 65, 32, 32));
			m_content = 1;
			return true;
		}
		if (m_HitRect_Tri1.contains(mouseXY))
		{
			m_sprite.setPosition(25, 652);
			m_sprite.setTextureRect(sf::IntRect(1453, 141, 32, 32));
			m_content = 2;
			return true;
		}
		if (m_HitRect_Tri2.contains(mouseXY))
		{
			m_sprite.setPosition(25, 614);
			m_sprite.setTextureRect(sf::IntRect(1453, 103, 32, 32));
			m_content = 3;
			return true;
		}
		if (m_HitRect_Tri3.contains(mouseXY))
		{
			m_sprite.setPosition(63, 652);
			m_sprite.setTextureRect(sf::IntRect(1491, 141, 32, 32));
			m_content = 4;
			return true;
		}
		if (m_HitRect_Tri4.contains(mouseXY))
		{
			m_sprite.setPosition(63, 614);
			m_sprite.setTextureRect(sf::IntRect(1491, 103, 32, 32));
			m_content = 5;
			return true;
		}
		return false;
	}

	int Shape::GetContent_Int()
	{
		return m_content;
	}
}