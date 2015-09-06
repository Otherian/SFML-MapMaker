#include "TextureTextbox.hpp"
#include <iostream>

namespace mm
{
	TextureTextbox::TextureTextbox()
	{
		m_HitRect = sf::IntRect(19, 120, 237, 30);
		m_text.setPosition(23, 120);
		m_text.setCharacterSize(25);
		m_text.setColor(sf::Color::Black);
		m_isActive = true;
	}


	TextureTextbox::~TextureTextbox()
	{
	}

	bool TextureTextbox::Update(sf::Vector2i mouseXY)
	{
		return m_HitRect.contains(mouseXY);
	}

	void TextureTextbox::Draw(sf::RenderWindow & renderWindow)
	{
		renderWindow.draw(m_text);
	}

	std::string TextureTextbox::GetContent_String()
	{
		return m_content;
	}

	void TextureTextbox::SetContent_String(std::string content)
	{
		m_content = content;
		m_text.setString(content);
		if (m_text.getLocalBounds().width > 225)
		{
			m_content.erase(m_content.end() - 1);
			m_text.setString(m_content);
		}
	}

	void TextureTextbox::SetFont(sf::Font &font)
	{
		m_text.setFont(font);
	}

	void TextureTextbox::SetActivity(bool activity)
	{
		if (activity)
			m_text.setColor(sf::Color::Red);
		else
			m_text.setColor(sf::Color::Black);
		VisibleObject::SetActivity(activity);
	}
}