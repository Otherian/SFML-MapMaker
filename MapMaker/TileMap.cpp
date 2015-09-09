#include "TileMap.hpp"

namespace mm
{
	TileMap::TileMap(std::string levelname, sf::Vector2i tileSize, Depth depth, bool active)
		: m_levelname(levelname), m_tileSize(tileSize), m_depth(depth), m_isActive(active), m_isLoaded(false)
	{
		Load();
	}

	TileMap::~TileMap()
	{
	}

	bool TileMap::SaveLevel()
	{
		std::ofstream stream(m_levelname, std::ios::app);
		if (stream.is_open())
		{
			std::vector<int> LevelMatrix(m_numberTiles.x * m_numberTiles.y);
			
			// Fill Vector:
			for (std::map<std::pair<int, int>, Tiles>::iterator itr = m_TileMap.begin(); itr != m_TileMap.end(); itr++)
			{
				int Zahl = itr->second.GetType() * 100;
				// TEXTURKRAMS <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
				Zahl += (itr->second.GetTexturePos().x) * 10;
				Zahl += (itr->second.GetTexturePos().y);
				// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
				LevelMatrix[itr->first.first + itr->first.second * m_numberTiles.x] = Zahl;
			}

			// Fill File:		
			switch (m_depth)
			{
			case Zero:
				stream << "Texture-Level-Zero: " << m_texturename << std::endl; // <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
				stream << "Level-Zero:";
				break;
			case B1:
				stream << "Texture-Level-B1: " << m_texturename << std::endl; // <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
				stream << "Level-B1:";
				break;
			case B2:
				stream << "Texture-Level-B2: " << m_texturename << std::endl; // <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
				stream << "Level-B2:";
				break;
			case F1:
				stream << "Texture-Level-F1: " << m_texturename << std::endl; // <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
				stream << "Level-F1:";
				break;
			case F2:
				stream << "Texture-Level-F2: " << m_texturename << std::endl; // <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
				stream << "Level-F2:";
				break;
			}

			for (std::vector<int>::size_type i = 0; i != LevelMatrix.size(); i++) 
			{
				if (!(i % m_numberTiles.x)) // Linebreak
					stream << std::endl;
				if (!LevelMatrix[i]) // 0 --> 000
					stream << "00";
				stream << LevelMatrix[i] << " ";
			}
			stream << "\n" << std::endl;
			stream.close();
			return true;
		}
		return false;
	}

	void TileMap::Load()
	{
		
		// ----------------
		// Load Texture
		// ----------------
		// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
		

		// TexturKrams <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<


		// -------------------------------
		// Load TileMap
		// -------------------------------
		std::pair<int, int> currentPos(-1,0);
		Tiles Tile(m_tileSize);
		m_TileMap.clear();

		std::ifstream stream(m_levelname);
		std::string string;
		std::string s_compare_depth;
		bool LevelDepthLoaded = false;

		switch (m_depth)
		{
		case Zero:
			s_compare_depth = "Level-Zero:";
			break;
		case B1:
			s_compare_depth = "Level-B1:";
			break;
		case B2:
			s_compare_depth = "Level-B2:";
			break;
		case F1:
			s_compare_depth = "Level-F1:";
			break;
		case F2:
			s_compare_depth = "Level-F2:";
			break;
		}

		if (stream.is_open())
		{
			std::cout << "Load Map " << s_compare_depth << "\n > Levelname:   " << m_levelname << std::endl;
			while (stream >> string)
			{
				if (string.compare("LevelSize:") == 0)
				{
					stream >> string;
					m_numberTiles.x = std::stoi(string, nullptr);
					stream >> string;
					m_numberTiles.y = std::stoi(string, nullptr);
					continue;
				}

				if (string.compare("Texture-"+s_compare_depth) == 0)
				{
					stream >> m_texturename;
					if (!m_texture.loadFromFile(m_texturename))
					{
						std::cout << " > ERROR: Could not load specified textur: " << m_texturename << std::endl;
						std::cout << " >> Set Template Texture!" << std::endl;
						m_texture.loadFromFile("resources/Template.png");
						m_texturename = "resources/Template.png";
					}
						
					else
						std::cout << " > TextureName: " << m_texturename << std::endl;
					continue;
				}

				if (string.compare(s_compare_depth) == 0)
				{
					for (int i = 0; i < (m_numberTiles.x * m_numberTiles.y); i++)
					{
						// Get next entry:
						stream >> string;

						currentPos.first++;
						// Move to next Position (Start has to be (-1,0) !!!!
						if (currentPos.first == m_numberTiles.x) // next row
						{
							currentPos.first = 0;
							currentPos.second += 1;
						}

						// first number: 0 = empty, 1 = Square, 2-5 Triangles
						// second number: Texture # 
						// example: 105 --> TileType = Square; Textur-Nr. 5
						int Number = std::stoi(string, nullptr);
						int TileTypeNumber = Number / 100;
						int texNumber = Number % 100;

						switch (TileTypeNumber)
						{
						case 0:
							Tile.SetTileType(Tiles::TileType::Empty);
							continue;
							break;

						case 1:
							Tile.SetTileType(Tiles::TileType::Square);
							break;

						case 2:
							Tile.SetTileType(Tiles::TileType::Tri1);
							break;

						case 3:
							Tile.SetTileType(Tiles::TileType::Tri2);
							break;

						case 4:
							Tile.SetTileType(Tiles::TileType::Tri3);
							break;

						case 5:
							Tile.SetTileType(Tiles::TileType::Tri4);
							break;
						}

						Tile.SetPosition(sf::Vector2i(currentPos.first, currentPos.second));
						// <<<<<<<<<<<<<<<<<<<<<<<<<<<<< INSERT TEXTURE-CLASS HERE <<<<<<<<<<<<<<<<<<<<<<<<<<< 
						// Until than: Texture is 10x10 Tiles Picture; 72pix Size each Tile
						Tile.SetTextureSize(m_textureSize);
						Tile.SetTexturePos(sf::Vector2i((texNumber / 10), (texNumber % 10)));
						// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

						// Insert in TileMap 
						m_TileMap.insert(std::make_pair(currentPos, Tile));
					}
					LevelDepthLoaded = true;
					stream.close();
					break;
				}				
			}
			stream.close();

			if (!LevelDepthLoaded)
			{
				m_VertexArray.resize(0);
				return;
			}
				
		}
		else 
		{
			std::cout << "ERROR: Level-File could not be opened." << std::endl;
			return;
			// THORW ERROR <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
		}

		// -----------------
		// Create VertexArrays 
		// -----------------
		CreateVertexArrays();
		m_isLoaded = true;
	}

	void TileMap::CreateVertexArrays()
	{
		if (!m_isActive)
			return;

		// Clear old Array
		m_VertexArray.resize(0);
		m_VertexArray.setPrimitiveType(sf::Triangles);
		sf::Vertex vertex;

		for (std::map<std::pair<int, int>, Tiles>::iterator itr = m_TileMap.begin(); itr != m_TileMap.end(); itr++)
		{
			itr->second.SetPosInTileMap(m_VertexArray.getVertexCount());
			for (unsigned int i = 0; i < 6; i++)
			{
				vertex = itr->second.GetVertexArray()[i];
				vertex.color = sf::Color(255, 255, 255, m_transparency);
				m_VertexArray.append(vertex);
			}
		}
	}

	void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		if (m_isLoaded && m_isActive)
		{
			states.texture = &m_texture;
			target.draw(m_VertexArray, states);
		}
	}

	void TileMap::SetTexture(std::string newTextureName, sf::Vector2i textureSize)
	{
		if (m_texturename != newTextureName)
		{
			m_texturename = newTextureName;
			m_texture.loadFromFile(newTextureName);
		}

		if (m_textureSize != textureSize)
		{
			m_textureSize = textureSize;
			for (std::map<std::pair<int, int>, Tiles>::iterator itr = m_TileMap.begin(); itr != m_TileMap.end(); itr++)
			{
				itr->second.SetTextureSize(textureSize);
				CreateVertexArrays();
			}
		}
	}


	void TileMap::SetLevel(std::string newLevelName)
	{
		m_levelname = newLevelName;
		Load();
	}

	void TileMap::SetNumberTiles(sf::Vector2i numberTiles)
	{
		if (numberTiles.x >= m_numberTiles.x && numberTiles.y >= m_numberTiles.y)
		{
			m_numberTiles = numberTiles;
		}
		else
		{
			std::map<std::pair<int, int>, Tiles>::iterator itr = m_TileMap.begin();
			while (itr != m_TileMap.end())
			{
				if ((itr->first.first + 1) > numberTiles.x || (itr->first.second + 1) > numberTiles.y)
				{
					m_TileMap.erase(itr++); // Deletes Element and THAN continues ~
				}
				else
				{
					++itr;
				}
			}
			m_numberTiles = numberTiles;
			// Array has to be created again!
			CreateVertexArrays();
		}
	}

	sf::Vector2i TileMap::GetNumberTiles()
	{
		return m_numberTiles;
	}

	void TileMap::SetTileSize(sf::Vector2i tileSize)
	{
		m_tileSize = tileSize;
		for (std::map<std::pair<int, int>, Tiles>::iterator itr = m_TileMap.begin(); itr != m_TileMap.end(); itr++)
		{
			itr->second.SetSize(tileSize);
		}
		CreateVertexArrays();
	}

	sf::Vector2i TileMap::GetTileSize()
	{
		return m_tileSize;
	}

	void TileMap::SetActivity(bool active)
	{
		m_isActive = active;
		if (active == true)	
			CreateVertexArrays();
	}

	bool TileMap::GetActivity()
	{
		return m_isActive;
	}

	const std::string TileMap::GetLevelName()
	{
		return m_levelname;
	}

	const std::string TileMap::GetTextureName()
	{
		return m_texturename;
	}

	sf::Texture TileMap::GetTexture()
	{
		return m_texture;
	}

	const TileMap::Depth TileMap::GetDepth()
	{
		return m_depth;
	}

	void TileMap::UpdateTile(Tiles updatedTile)
	{
		std::pair<int, int> updatedTilePos = std::make_pair(updatedTile.GetPosition().x, updatedTile.GetPosition().y);
		std::map<std::pair<int, int>, Tiles>::iterator result = m_TileMap.find(updatedTilePos);
		if (result == m_TileMap.end()) // not in Map --> fill in
		{
			updatedTile.SetPosInTileMap(m_VertexArray.getVertexCount());
			for (unsigned int i = 0; i < 6; i++)
				m_VertexArray.append(updatedTile.GetVertexArray()[i]);

			m_TileMap.insert(std::make_pair(updatedTilePos, updatedTile));
		}
		else // Pos already taken; Override!
		{
			int oldVertexPos = result->second.GetPosInTileMap();
			updatedTile.SetPosInTileMap(oldVertexPos);
			for (unsigned int i = 0; i < 6; i++)
				m_VertexArray[i + oldVertexPos] = (updatedTile.GetVertexArray()[i]);
						
			if (updatedTile.GetType() == Tiles::TileType::Empty)
				m_TileMap.erase(result);
			else
				result->second = updatedTile;
		}
	}

	void TileMap::SetTransparency(int transparency)
	{
		if (transparency < 0 || transparency > 255)
		{
			std::cout << "ERROR: Transparency has to be between 0 - 255!!" << std::endl;
			return;
		}
		if (m_transparency != transparency)
		{
			m_transparency = transparency;
			if(m_isActive)
				CreateVertexArrays();
		}
	}
}