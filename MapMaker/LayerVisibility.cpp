#include "LayerVisibility.hpp"

namespace mm
{
	LayerVisibility::LayerVisibility()
		: m_HitRect_BG2(133, 607, 45, 74),
		m_HitRect_BG1(186, 607, 45, 74),
		m_HitRect_Zero(239, 607, 45, 74),
		m_HitRect_FG1(292, 607, 45, 74),
		m_HitRect_FG2(345, 607, 45, 74),
		m_SpriteRect_active(1455, 826, 45, 74),
		m_SpriteRect_inactive(1505, 826, 45, 74)

	{
		m_HitRect = sf::IntRect(133, 607, 257, 74);
	
		// Sprite Positions
		m_spriteBG2.setPosition(133, 607);
		m_spriteBG1.setPosition(186, 607);
		m_sprite.setPosition(239, 607);
		m_spriteFG1.setPosition(292, 607);
		m_spriteFG2.setPosition(345, 607);

		// at start all TileMaps are active
		m_spriteBG2.setTextureRect(m_SpriteRect_active);
		m_spriteBG1.setTextureRect(m_SpriteRect_active);
		m_sprite.setTextureRect(m_SpriteRect_active);
		m_spriteFG1.setTextureRect(m_SpriteRect_active);
		m_spriteFG2.setTextureRect(m_SpriteRect_active);

		m_isActive = true;
	}


	LayerVisibility::~LayerVisibility()
	{
	}

	bool LayerVisibility::Update(sf::Vector2i mouseXY)
	{
		if (!m_HitRect.contains(mouseXY))
			return false;

		// m_content = ##
		// first #: Wich Layer > BG2(1) ... FG2(5) 
		// second #: on(1) or off(0)

		// which Button?
		if (m_HitRect_BG2.contains(mouseXY))
		{
			if (m_spriteBG2.getTextureRect().left == 1455) 
			{
				// aktiv > set inaktiv
				m_spriteBG2.setTextureRect(m_SpriteRect_inactive);
				m_content = 10;
			}
			else
			{
				// inaktiv > aktiv
				m_spriteBG2.setTextureRect(m_SpriteRect_active);
				m_content = 11;
			}
			return true;
		}
		if (m_HitRect_BG1.contains(mouseXY))
		{
			if (m_spriteBG1.getTextureRect().left == 1455)
			{
				// aktiv > set inaktiv
				m_spriteBG1.setTextureRect(m_SpriteRect_inactive);
				m_content = 20;
			}
			else
			{
				// inaktiv > aktiv
				m_spriteBG1.setTextureRect(m_SpriteRect_active);
				m_content = 21;
			}
			return true;
		}
		if (m_HitRect_Zero.contains(mouseXY))
		{
			if (m_sprite.getTextureRect().left == 1455)
			{
				// aktiv > set inaktiv
				m_sprite.setTextureRect(m_SpriteRect_inactive);
				m_content = 30;
			}
			else
			{
				// inaktiv > aktiv
				m_sprite.setTextureRect(m_SpriteRect_active);
				m_content = 31;
			}
			return true;
		}
		if (m_HitRect_FG1.contains(mouseXY))
		{
			if (m_spriteFG1.getTextureRect().left == 1455)
			{
				// aktiv > set inaktiv
				m_spriteFG1.setTextureRect(m_SpriteRect_inactive);
				m_content = 40;
			}
			else
			{
				// inaktiv > aktiv
				m_spriteFG1.setTextureRect(m_SpriteRect_active);
				m_content = 41;
			}
			return true;
		}
		if (m_HitRect_FG2.contains(mouseXY))
		{
			if (m_spriteFG2.getTextureRect().left == 1455)
			{
				// aktiv > set inaktiv
				m_spriteFG2.setTextureRect(m_SpriteRect_inactive);
				m_content = 50;
			}
			else
			{
				// inaktiv > aktiv
				m_spriteFG2.setTextureRect(m_SpriteRect_active);
				m_content = 51;
			}
			return true;
		}
		return false;
	}

	void LayerVisibility::Draw(sf::RenderWindow &renderWindow)
	{
		if (m_isActive)
		{
			renderWindow.draw(m_spriteBG2);
			renderWindow.draw(m_spriteBG1);
			renderWindow.draw(m_sprite);
			renderWindow.draw(m_spriteFG1);
			renderWindow.draw(m_spriteFG2);
		}
	}


	void LayerVisibility::SetTexture(sf::Texture &texture)
	{
		m_spriteBG2.setTexture(texture);
		m_spriteBG1.setTexture(texture);
		m_sprite.setTexture(texture);
		m_spriteFG1.setTexture(texture);
		m_spriteFG2.setTexture(texture);
	}

	int LayerVisibility::GetContent_Int()
	{
		// m_content = ##
		// first #: Wich Layer > BG2(1) ... FG2(5) 
		// second #: on(1) or off(0)
		return m_content;
	}
}