#include "VisibleObject.hpp"

namespace mm
{
	VisibleObject::VisibleObject()
		: m_isActive(false)
	{
	}

	VisibleObject::~VisibleObject()
	{
	}

	void VisibleObject::SetActivity(bool activity)
	{
		m_isActive = activity;
	}

	void VisibleObject::Draw(sf::RenderWindow & renderWindow)
	{
		if(m_isActive)
			renderWindow.draw(m_sprite);
	}

	bool VisibleObject::Update(sf::Vector2i mouseXY)
	{
		return false; 
	}

	std::string VisibleObject::GetContent_String()
	{
		return "";
	}

	void VisibleObject::SetContent_String(std::string content)
	{
	}

	void VisibleObject::SetTexture(sf::Texture &texture)
	{
		m_sprite.setTexture(texture);
	}

	int VisibleObject::GetContent_Int()
	{
		return 0;
	}
}
