#pragma once
#include "VisibleObject.hpp"

namespace mm
{
	class TextureBox : public VisibleObject
	{
	public:
		TextureBox();
		~TextureBox();

		bool Update(sf::Vector2i mouseXY);
		void SetTexture(sf::Texture &texture);
		void Draw(sf::RenderWindow &renderWindow);

		int GetContent_Int();

	private:
		int m_content;
		sf::RectangleShape m_selectedTexRect;
		sf::RectangleShape m_TexBox;
	};
}