#pragma once
#include "VisibleObject.hpp"

namespace mm
{
	class Layer : public VisibleObject
	{
	public:
		Layer();
		~Layer();

		bool Update(sf::Vector2i mouseXY);

		int GetContent_Int();

	private:
		int m_content;

		sf::IntRect m_HitRect_BG2;
		sf::IntRect m_HitRect_BG1;
		sf::IntRect m_HitRect_Zero;
		sf::IntRect m_HitRect_FG1;
		sf::IntRect m_HitRect_FG2;
	};
}