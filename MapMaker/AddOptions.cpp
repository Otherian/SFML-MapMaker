#include "AddOptions.hpp"

namespace mm
{
	AddOptions::AddOptions()
		: m_HitRect_MapGrid(17, 780, 19, 19),
		m_HitRect_InGameVis(17, 806, 19, 19),
		m_HitRect_Transparency(17, 832, 19, 19)

	{
		m_HitRect = sf::IntRect(17, 780, 19, 71);
		
		m_MapGrid.setPosition(17, 780);
		m_InGameVis.setPosition(17, 806);
		m_Transparency.setPosition(17, 832);

		m_MapGrid.setTextureRect(sf::IntRect(1515, 2, 19, 19));
		m_InGameVis.setTextureRect(sf::IntRect(1515, 2, 19, 19));
		m_Transparency.setTextureRect(sf::IntRect(1515, 2, 19, 19));

		m_bMapGrid = true;
		m_bInGameVis = false;
		m_bTransparency = true;

		m_isActive = true;
	}


	AddOptions::~AddOptions()
	{
	}

	bool AddOptions::Update(sf::Vector2i mouseXY)
	{
		if (!m_HitRect.contains(mouseXY))
			return false;

		// which Button?
		if (m_HitRect_MapGrid.contains(mouseXY))
		{
			if (m_bMapGrid)
			{
				m_bMapGrid = false;
				m_content = -1;
			}
			else
			{
				m_bMapGrid = true;
				m_content = 1;
			}
			return true;
		}

		if (m_HitRect_InGameVis.contains(mouseXY))
		{
			if (m_bInGameVis)
			{
				m_bInGameVis = false;
				m_content = -10;
			}
			else
			{
				m_bInGameVis = true;
				m_content = 10;
			}
			return true;
		}

		if (m_HitRect_Transparency.contains(mouseXY))
		{
			if (m_bTransparency)
			{
				m_bTransparency = false;
				m_content = -100;
			}
			else
			{
				m_bTransparency = true;
				m_content = 100;
			}
			return true;
		}
		return false;
	}

	void AddOptions::Draw(sf::RenderWindow &renderWindow)
	{
		if (m_isActive)
		{
			if(m_bMapGrid)
				renderWindow.draw(m_MapGrid);
			if(m_bInGameVis)
				renderWindow.draw(m_InGameVis);
			if(m_bTransparency)
				renderWindow.draw(m_Transparency);
		}
	}


	void AddOptions::SetTexture(sf::Texture &texture)
	{
		m_MapGrid.setTexture(texture);
		m_InGameVis.setTexture(texture);
		m_Transparency.setTexture(texture);
	}

	int AddOptions::GetContent_Int()
	{
		return m_content;
	}
}