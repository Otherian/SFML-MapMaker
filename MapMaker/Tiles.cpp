#include "Tiles.hpp"

namespace mm
{
	Tiles::Tiles(sf::Vector2i size, sf::Vector2i position, TileType type)
		: m_size(size), m_position(position), m_type(type), m_VertexArrayUpToDate(false)
	{
	}

	Tiles::~Tiles()
	{
	}

	const sf::Vector2i Tiles::GetPosition()
	{
		return m_position;
	}

	void Tiles::SetPosition(sf::Vector2i position)
	{
		m_position = position;
		m_VertexArrayUpToDate = false;
	}

	void Tiles::SetSize(sf::Vector2i size)
	{
		m_size = size;
		m_VertexArrayUpToDate = false;
	}

	void Tiles::SetTexturePos(sf::Vector2i textPos)
	{
		m_texturePos = textPos;
		m_VertexArrayUpToDate = false;
	}

	void Tiles::SetTextureSize(sf::Vector2i textSize)
	{
		m_textureSize = textSize;
		m_VertexArrayUpToDate = false;
	}

	void Tiles::SetTileType(TileType type)
	{
		m_type = type;
		m_VertexArrayUpToDate = false;
	}


	const int Tiles::GetPosInTileMap()
	{
		return m_posInTileMapVertex;
	}

	void Tiles::SetPosInTileMap(int posInTileMapVertex)
	{
		m_posInTileMapVertex = posInTileMapVertex;
	}
	

	const sf::Vector2i Tiles::GetTexturePos()
	{
		return m_texturePos;
	}

	const Tiles::TileType Tiles::GetType()
	{
		return m_type;
	}

	const sf::VertexArray Tiles::GetVertexArray()
	{
		if (m_VertexArrayUpToDate)
			return m_VertexArray;
		
		UpdateVertexArray();
		return m_VertexArray;
	}

	void Tiles::UpdateVertexArray()
	{
		m_VertexArray.resize(0);
		m_VertexArray.resize(6);
		m_VertexArray.setPrimitiveType(sf::PrimitiveType::Triangles);

		sf::Vector2f pos0 = sf::Vector2f(static_cast<float>(m_position.x * m_size.x), static_cast<float>(m_position.y * m_size.y));
		sf::Vector2f tex0 = sf::Vector2f(static_cast<float>(m_texturePos.x * m_textureSize.x), static_cast<float>(m_texturePos.y * m_textureSize.y));

		sf::Vector2f pos1 = sf::Vector2f(static_cast<float>(m_position.x * m_size.x), static_cast<float>((m_position.y + 1) * m_size.y));
		sf::Vector2f tex1 = sf::Vector2f(static_cast<float>(m_texturePos.x * m_textureSize.x), static_cast<float>((m_texturePos.y + 1) * m_textureSize.y));

		sf::Vector2f pos2 = sf::Vector2f(static_cast<float>((m_position.x + 1) * m_size.x), static_cast<float>((m_position.y + 1) * m_size.y));
		sf::Vector2f tex2 = sf::Vector2f(static_cast<float>((m_texturePos.x + 1) * m_textureSize.x), static_cast<float>((m_texturePos.y + 1) * m_textureSize.y));

		sf::Vector2f pos3 = sf::Vector2f(static_cast<float>((m_position.x + 1) * m_size.x), static_cast<float>(m_position.y * m_size.y));
		sf::Vector2f tex3 = sf::Vector2f(static_cast<float>((m_texturePos.x + 1) * m_textureSize.x), static_cast<float>(m_texturePos.y * m_textureSize.y));

		switch (m_type) 
		{
		case Empty:
			return;
			break;
		case Square:
			// 0 -- 3
			// |	|
			// 1 -- 2
			
			// positions:
			m_VertexArray[0].position = pos0;
			m_VertexArray[1].position = pos1;
			m_VertexArray[2].position = pos3;

			m_VertexArray[3].position = pos1;
			m_VertexArray[4].position = pos2;
			m_VertexArray[5].position = pos3;

			// texture:
			m_VertexArray[0].texCoords = tex0;					
			m_VertexArray[1].texCoords = tex1;
			m_VertexArray[2].texCoords = tex3;

			m_VertexArray[3].texCoords = tex1;
			m_VertexArray[4].texCoords = tex2;
			m_VertexArray[5].texCoords = tex3;
			break;

		case Tri1:

			// 0
			// | \
			// |  \
			// 1 -- 2

			// positions:
			m_VertexArray[0].position = pos0;
			m_VertexArray[1].position = pos1;
			m_VertexArray[2].position = pos2;

			// texture:
			m_VertexArray[0].texCoords = tex0;
			m_VertexArray[1].texCoords = tex1;
			m_VertexArray[2].texCoords = tex2;

			
			break;

		case Tri2:
			// 0 -- 3
			// |  /
			// | /
			// 1

			// positions:
			m_VertexArray[0].position = pos0;
			m_VertexArray[1].position = pos1;
			m_VertexArray[2].position = pos3;

			// texture:
			m_VertexArray[0].texCoords = tex0;
			m_VertexArray[1].texCoords = tex1;
			m_VertexArray[2].texCoords = tex3;
			break;

		case Tri3:
			//		3
			//    / |
			//	 /  |
			// 1 -- 2

			// positions:
			m_VertexArray[0].position = pos1;
			m_VertexArray[1].position = pos2;
			m_VertexArray[2].position = pos3;

			// texture:
			m_VertexArray[0].texCoords = tex1;
			m_VertexArray[1].texCoords = tex2;
			m_VertexArray[2].texCoords = tex3;
			break;

		case Tri4:
			// 0 -- 3
			//   \  |
			//    \ |
			//      2

			// positions:
			m_VertexArray[0].position = pos0;
			m_VertexArray[1].position = pos2;
			m_VertexArray[2].position = pos3;

			// texture:
			m_VertexArray[0].texCoords = tex0;
			m_VertexArray[1].texCoords = tex2;
			m_VertexArray[2].texCoords = tex3;
			break;
			
		}
	}
}