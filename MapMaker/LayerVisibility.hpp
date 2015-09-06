#pragma once
#include "VisibleObject.hpp"

namespace mm
{
	class LayerVisibility : public VisibleObject
	{
	public:
		LayerVisibility();
		~LayerVisibility();

		bool Update(sf::Vector2i mouseXY);
		void Draw(sf::RenderWindow &renderWindow);
		void SetTexture(sf::Texture &texture);

		int GetContent_Int();

	private:
		int m_content;

		// m_sprite from VisibleObject = spriteZero;
		sf::Sprite m_spriteBG2;
		sf::Sprite m_spriteBG1;
		sf::Sprite m_spriteFG1;
		sf::Sprite m_spriteFG2;

		sf::IntRect m_HitRect_BG2;
		sf::IntRect m_HitRect_BG1;
		sf::IntRect m_HitRect_Zero;
		sf::IntRect m_HitRect_FG1;
		sf::IntRect m_HitRect_FG2;

		sf::IntRect m_SpriteRect_active;
		sf::IntRect m_SpriteRect_inactive;
	};
}