#include "TextureBox.hpp"

namespace mm
{
	TextureBox::TextureBox()
	{
		m_HitRect = sf::IntRect(19, 160, 380, 380);

		m_selectedTexRect.setPosition(19, 160);
		m_selectedTexRect.setSize(sf::Vector2f(38, 38));
		m_selectedTexRect.setFillColor(sf::Color(255, 255, 255, 0));
		m_selectedTexRect.setOutlineColor(sf::Color(255,255,255,255));
		m_selectedTexRect.setOutlineThickness(-3);

		m_TexBox.setPosition(19, 160);
		m_TexBox.setSize(sf::Vector2f(380, 380));
		m_TexBox.setTextureRect(sf::IntRect(0, 0, 720, 720));

		m_content = 0;
		m_isActive = true;
	}


	TextureBox::~TextureBox()
	{
	}

	void TextureBox::Draw(sf::RenderWindow &renderWindow)
	{
		if (m_isActive)
		{
			renderWindow.draw(m_TexBox);
			renderWindow.draw(m_selectedTexRect);
		}
		
	}

	bool TextureBox::Update(sf::Vector2i mouseXY)
	{
		if (m_HitRect.contains(mouseXY))
		{
			mouseXY.x -= 19;
			mouseXY.y -= 160;

			int x_Position = mouseXY.x / 38;
			int y_Position = mouseXY.y / 38;

			m_selectedTexRect.setPosition(19 + x_Position * 38, 160 + y_Position * 38);
			m_content = x_Position * 10 + y_Position;
			return true;
		}
		return false;
	}

	void TextureBox::SetTexture(sf::Texture &texture)
	{
		m_TexBox.setTexture(&texture);
	}

	int TextureBox::GetContent_Int()
	{
		return m_content;
	}
}