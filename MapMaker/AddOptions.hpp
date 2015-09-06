#pragma once
#include "VisibleObject.hpp"

namespace mm
{
	class AddOptions : public VisibleObject
	{
	public:
		AddOptions();
		~AddOptions();

		bool Update(sf::Vector2i mouseXY);
		void Draw(sf::RenderWindow &renderWindow);
		void SetTexture(sf::Texture &texture);

		int GetContent_Int();

	private:
		int m_content;

		sf::IntRect m_HitRect_MapGrid;
		sf::IntRect m_HitRect_InGameVis;
		sf::IntRect m_HitRect_Transparency;
		
		sf::Sprite m_MapGrid;
		sf::Sprite m_InGameVis;
		sf::Sprite m_Transparency;

		bool m_bMapGrid;
		bool m_bInGameVis;
		bool m_bTransparency;
	};
}