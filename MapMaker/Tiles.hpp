#pragma once
#include <SFML/Graphics.hpp>

namespace mm
{
	class Tiles
	{
	public:
		enum TileType { Empty, Square, Tri1, Tri2, Tri3, Tri4 };

		Tiles(sf::Vector2i size = sf::Vector2i(0, 0), sf::Vector2i position = sf::Vector2i(0, 0), TileType = Empty);
		virtual ~Tiles();
		
		const sf::Vector2i GetPosition();
		void SetPosition(sf::Vector2i position);
		void SetSize(sf::Vector2i size);
		void SetTexturePos(sf::Vector2i textPos);
		void SetTextureSize(sf::Vector2i textSize);
		void SetTileType(TileType type);

		const sf::Vector2i GetTexturePos();
		const TileType GetType();
		const sf::VertexArray GetVertexArray();		
		void UpdateVertexArray();

		const int GetPosInTileMap();					
		void SetPosInTileMap(int posInTileMapVertex);  
		
	private:
		TileType m_type;

		sf::VertexArray m_VertexArray;
		sf::Vector2i m_position;
		sf::Vector2i m_size;
		sf::Vector2i m_texturePos;
		sf::Vector2i m_textureSize;
		int m_posInTileMapVertex = 0;  
		bool m_VertexArrayUpToDate;
	};
}