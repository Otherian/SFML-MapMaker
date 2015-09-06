#include "LevelTextbox.hpp"
#include <iostream>

namespace mm
{
	LevelTextbox::LevelTextbox()
	{
		m_HitRect = sf::IntRect(84, 46, 305, 30);
		m_text.setPosition(88, 46);
		m_text.setCharacterSize(25);
		m_text.setColor(sf::Color::Black);

		m_isActive = true;
	}


	LevelTextbox::~LevelTextbox()
	{
	}

	bool LevelTextbox::Update(sf::Vector2i mouseXY)
	{
		return m_HitRect.contains(mouseXY);
	}

	void LevelTextbox::Draw(sf::RenderWindow & renderWindow)
	{
		renderWindow.draw(m_text);
	}

	std::string LevelTextbox::GetContent_String()
	{
		return m_content;
	}

	void LevelTextbox::SetContent_String(std::string content)
	{
		m_content = content;
		m_text.setString(content);
		while (m_text.getLocalBounds().width > 293)
		{
			m_content.erase(m_content.end() - 1);
			m_text.setString(m_content);
		}
	}

	void LevelTextbox::SetFont(sf::Font &font)
	{
		m_text.setFont(font);
	}

	void LevelTextbox::SetActivity(bool activity)
	{
		if(activity)
			m_text.setColor(sf::Color::Red);
		else
			m_text.setColor(sf::Color::Black);
		VisibleObject::SetActivity(activity);
	}
}