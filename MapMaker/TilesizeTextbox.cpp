#include "TilesizeTextbox.hpp"
#include <iostream>

namespace mm
{
	TilesizeTextbox::TilesizeTextbox()
	{
		m_HitRect = sf::IntRect(286, 120, 112, 30);
		m_text.setPosition(290, 120);
		m_text.setCharacterSize(25);
		m_text.setColor(sf::Color::Black);
		m_isActive = true;
	}


	TilesizeTextbox::~TilesizeTextbox()
	{
	}

	bool TilesizeTextbox::Update(sf::Vector2i mouseXY)
	{
		//return m_HitRect.contains(mouseXY);
		return false;
	}

	void TilesizeTextbox::Draw(sf::RenderWindow & renderWindow)
	{
		renderWindow.draw(m_text);
	}

	std::string TilesizeTextbox::GetContent_String()
	{
		return m_content;
	}

	void TilesizeTextbox::SetContent_String(std::string content)
	{
		m_content = content;
		m_text.setString(content);
		if (m_text.getLocalBounds().width > 100)
		{
			m_content.erase(m_content.end() - 1);
			m_text.setString(m_content);
		}
	}

	void TilesizeTextbox::SetFont(sf::Font &font)
	{
		m_text.setFont(font);
	}

	void TilesizeTextbox::SetActivity(bool activity)
	{
		if (activity)
			m_text.setColor(sf::Color::Red);
		else
			m_text.setColor(sf::Color::Black);
		VisibleObject::SetActivity(activity);
	}
}