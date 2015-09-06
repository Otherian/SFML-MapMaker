#pragma once
#include "VisibleObject.hpp"

namespace mm
{
	class LevelTextbox : public VisibleObject
	{
	public:
		LevelTextbox();
		~LevelTextbox();

		bool Update(sf::Vector2i mouseXY);
		void Draw(sf::RenderWindow & renderWindow);

		std::string GetContent_String();
		void SetFont(sf::Font &font);
		void SetContent_String(std::string content);
		void SetActivity(bool activity);

	private:
		std::string m_content;
		sf::Text m_text;
	};
}