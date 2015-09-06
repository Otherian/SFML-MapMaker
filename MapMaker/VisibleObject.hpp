#pragma once
#include <string>
#include <SFML/Graphics.hpp>

namespace mm
{
	class VisibleObject
	{
	public:
		VisibleObject();
		virtual ~VisibleObject();

		virtual void Draw(sf::RenderWindow &renderWindow);
		virtual bool Update(sf::Vector2i mouseXY);
		
		virtual void SetActivity(bool activity);

		virtual std::string GetContent_String();
		virtual void SetContent_String(std::string content);
		virtual void SetTexture(sf::Texture &texture);
		virtual int GetContent_Int();

	protected:
		sf::Sprite m_sprite;
		sf::IntRect m_HitRect;
		bool m_isActive;
	};
}