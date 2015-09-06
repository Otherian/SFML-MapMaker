#pragma once
#include "VisibleObject.hpp"

namespace mm
{
	class Shape : public VisibleObject
	{
	public:
		Shape();
		~Shape();

		bool Update(sf::Vector2i mouseXY);
		
		int GetContent_Int();

	private:
		int m_content;

		sf::IntRect m_HitRect_Empty;
		sf::IntRect m_HitRect_Quad;
		sf::IntRect m_HitRect_Tri1;
		sf::IntRect m_HitRect_Tri2;
		sf::IntRect m_HitRect_Tri3;
		sf::IntRect m_HitRect_Tri4;
	};
}