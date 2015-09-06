#include "MakerObjectManager.hpp"


namespace mm
{
	MakerObjectManager::MakerObjectManager()
	{
	}

	MakerObjectManager::~MakerObjectManager()
	{
		std::for_each(makerObjects.begin(), makerObjects.end(), ObjectDeallocator());
	}

	void MakerObjectManager::Load(std::string levelname, sf::Vector2i tileSize)
	{
		// Loading TileMaps and Map
		TileMap *B2 = new TileMap(levelname, tileSize, TileMap::Depth::B2, true);
		TileMap *B1 = new TileMap(levelname, tileSize, TileMap::Depth::B1, true);
		TileMap *Zero = new TileMap(levelname, tileSize, TileMap::Depth::Zero, true);
		TileMap *F1 = new TileMap(levelname, tileSize, TileMap::Depth::F1, true);
		TileMap *F2 = new TileMap(levelname, tileSize, TileMap::Depth::F2, true);

		m_Map.Add(B2->GetDepth(), B2);
		m_Map.Add(B1->GetDepth(), B1);
		m_Map.Add(Zero->GetDepth(), Zero);
		m_Map.Add(F1->GetDepth(), F1);
		m_Map.Add(F2->GetDepth(), F2);
		// --------------------------
		m_currentNumberTiles = m_Map.GetTileMap(TileMap::Depth::Zero)->GetNumberTiles();
		m_currentTileSize = tileSize;
		m_currentTileVisible = false;
		m_currentDepth = TileMap::Depth::Zero;
		m_currentTile.SetTexturePos(sf::Vector2i(0, 0));
		m_currentTile.SetTileType(Tiles::TileType::Square);
		m_currentTile.SetSize(tileSize);
		m_currentTile.SetTextureSize(sf::Vector2i(72, 72)); // <<<<<<<<<<<<<<<<
		m_currentTexture = m_Map.GetTileMap(m_currentDepth)->GetTexture();

		// Loading MapBorder & Grid Stuff
		BuildBorderAndGrid();
		m_MapBorder.setFillColor(sf::Color(255, 255, 255, 0));
		m_MapBorder.setOutlineColor(sf::Color(139, 121, 94));
		m_MapBorder.setOutlineThickness(4);
		m_tempBorderRect.setFillColor(sf::Color(77, 77, 77, 140));
		m_tempBorderRect.setOutlineColor(sf::Color(212, 212, 212, 255));
		m_tempBorderRect.setOutlineThickness(2);

		m_MapGrid.setPrimitiveType(sf::PrimitiveType::Lines);
		m_MapGridActive = true;
		// --------------------------
		m_TransparencyActive = true;

		m_MakerTextureSet.loadFromFile("resources/MapMakerTexture.png");
		if (!usedFont.loadFromFile("resources/arialbd.ttf"))
			std::cout << "ERROR: Could not open fond!" << std::endl;

		// Loading Maker-Elements
		Background *BG = new Background();
		BG->SetTexture(m_MakerTextureSet);
		makerObjects["0_BG"] = BG;

		SaveButton *SB = new SaveButton();
		makerObjects["1_SB"] = SB;

		LevelTextbox *LText = new LevelTextbox();
		LText->SetFont(usedFont);
		levelname.erase(0, 10); // remove "resources/"
		LText->SetContent_String(levelname);
		makerObjects["2_LevelText"] = LText;

		TextureTextbox *TexText = new TextureTextbox();
		TexText->SetFont(usedFont);
		std::string texturename = m_Map.GetTileMap(m_currentDepth)->GetTextureName();
		texturename.erase(0, 10); // remove "resources/"
		TexText->SetContent_String(texturename);
		makerObjects["3_TextureText"] = TexText;

		TilesizeTextbox *TileText = new TilesizeTextbox();
		TileText->SetFont(usedFont);
		std::string tilesize = std::to_string(m_currentTileSize.x) + "/" + std::to_string(m_currentTileSize.y);
		TileText->SetContent_String(tilesize);
		makerObjects["4_TilesizeText"] = TileText;

		Shape *Shapes = new Shape();
		Shapes->SetTexture(m_MakerTextureSet);
		makerObjects["5_Shapes"] = Shapes;

		Layer *Layers = new Layer();
		Layers->SetTexture(m_MakerTextureSet);
		makerObjects["6_Layers"] = Layers;

		LayerVisibility *LayerVisibilitys = new LayerVisibility();
		LayerVisibilitys->SetTexture(m_MakerTextureSet);
		makerObjects["7_LayerVisibilitys"] = LayerVisibilitys;

		TextureBox *TexBox = new TextureBox();
		TexBox->SetTexture(m_currentTexture);
		makerObjects["8_TexBox"] = TexBox;

		AddOptions *Options = new AddOptions();
		Options->SetTexture(m_MakerTextureSet);
		makerObjects["9_AddOptions"] = Options;
		// --------------------------
	}


	void MakerObjectManager::DrawAll(sf::RenderWindow& renderWindow, sf::View mapView)
	{
		// Set default View and draw Maker-Elements
		renderWindow.setView(renderWindow.getDefaultView());
		std::map<std::string, VisibleObject*>::const_iterator itr = makerObjects.begin();
		while (itr != makerObjects.end())
		{
			itr->second->Draw(renderWindow);
			itr++;
		}

		// Set Map-View and draw MapStuff
		renderWindow.setView(mapView);
		m_Map.DrawAll(renderWindow);
		if(m_currentTileVisible)
			renderWindow.draw(m_currentTile.GetVertexArray(), &m_currentTexture);
		if (m_MapGridActive)
			renderWindow.draw(m_MapGrid);
		renderWindow.draw(m_MapBorder);
		if (m_tempBorderMove != 0)
			renderWindow.draw(m_tempBorderRect);
	}

	void MakerObjectManager::TilePreview(sf::Vector2i mouseXY)
	{
		if (mouseXY.x > 0 && mouseXY.y > 0
			&& mouseXY.x < m_currentNumberTiles.x * m_currentTileSize.x
			&& mouseXY.y < m_currentNumberTiles.y * m_currentTileSize.y)
		{
			m_currentTileVisible = true;
			m_currentTile.SetPosition(sf::Vector2i((mouseXY.x / m_currentTileSize.x), (mouseXY.y / m_currentTileSize.y)));
			m_currentTile.SetSize(m_currentTileSize);
		}
		else
		{
			m_currentTileVisible = false;
		}
		
	}

	MakerObjectManager::MakerResult MakerObjectManager::UpdateAll(sf::Vector2i mouseXY, bool Map_or_Menu)
	{
		if (Map_or_Menu && mouseXY.x > 0 && mouseXY.y > 0
						&& mouseXY.x < m_currentNumberTiles.x * m_currentTileSize.x
						&& mouseXY.y < m_currentNumberTiles.y * m_currentTileSize.y)
		{
			// Update Map
			m_currentTile.SetPosition(sf::Vector2i((mouseXY.x / m_currentTileSize.x), (mouseXY.y / m_currentTileSize.y)));
			m_Map.UpdateTile(m_currentTile, m_currentDepth);
		}
		else if (Map_or_Menu && (mouseXY.x >= m_currentNumberTiles.x * m_currentTileSize.x && mouseXY.x <= m_currentNumberTiles.x * m_currentTileSize.x + 7))
		{
			return MakerObjectManager::MakerResult::ResizeMap_x;
		}
		else if (Map_or_Menu && (mouseXY.y >= m_currentNumberTiles.y * m_currentTileSize.y && mouseXY.y <= m_currentNumberTiles.y * m_currentTileSize.y + 7))
		{
			return MakerObjectManager::MakerResult::ResizeMap_y;
		}
		else if(!Map_or_Menu)
		{
			// Update Menu-Objecte
			for (std::map<std::string, VisibleObject*>::iterator itr = makerObjects.begin(); itr != makerObjects.end(); itr++)
			{
				if(itr->second->Update(mouseXY))
				{
					// Find the "True"-Map-Element >> corresponding reaction!
					if (itr->first == "1_SB")				
						return MakerObjectManager::MakerResult::Save;

					if (itr->first == "2_LevelText")
						return MakerObjectManager::MakerResult::TextBox_Level;

					if (itr->first == "3_TextureText")
						return MakerObjectManager::MakerResult::TextBox_Texture;

					if (itr->first == "4_TilesizeText")
						return MakerObjectManager::MakerResult::Textbox_TileSize;

					if (itr->first == "5_Shapes")
					{
						switch (itr->second->GetContent_Int())
						{
						case 0:
							m_currentTile.SetTileType(Tiles::TileType::Empty);
							break;
						case 1:
							m_currentTile.SetTileType(Tiles::TileType::Square);
							break;
						case 2:
							m_currentTile.SetTileType(Tiles::TileType::Tri1);
							break;
						case 3:
							m_currentTile.SetTileType(Tiles::TileType::Tri2);
							break;
						case 4:
							m_currentTile.SetTileType(Tiles::TileType::Tri3);
							break;
						case 5:
							m_currentTile.SetTileType(Tiles::TileType::Tri4);
							break;
						}
					}

					if (itr->first == "6_Layers")
					{
						switch (itr->second->GetContent_Int())
						{
						case 0:
							m_currentDepth = TileMap::Depth::B2;
							break;
						case 1:
							m_currentDepth = TileMap::Depth::B1;
							break;
						case 2:
							m_currentDepth = TileMap::Depth::Zero;
							break;
						case 3:
							m_currentDepth = TileMap::Depth::F1;
							break;
						case 4:
							m_currentDepth = TileMap::Depth::F2;
							break;
						}
						
						VisibleObject* TexBox = makerObjects.find("8_TexBox")->second;
						VisibleObject* TextureTextbox = makerObjects.find("3_TextureText")->second;
						TileMap* currentMap = m_Map.GetTileMap(m_currentDepth);
						
						// Update Texture-Box and -Textbox
						m_currentTexture = currentMap->GetTexture();
						std::string currentTextureName;
						currentTextureName = currentMap->GetTextureName();
						currentTextureName.erase(0, 10);
						TextureTextbox->SetContent_String(currentTextureName);

						// Make Maps transparent if activated
						if (m_TransparencyActive)
							SetTransparency(50);
						
						// IF Map inactive -> Set active!
						if (!(currentMap->GetActivity()))
						{ 
							VisibleObject* LayerVis = makerObjects.find("7_LayerVisibilitys")->second;
							LayerVis->Update(sf::Vector2i(mouseXY.x, mouseXY.y + 30));
							currentMap->SetActivity(true);
						}
						
					}

					if (itr->first == "7_LayerVisibilitys")
					{
						bool activity;
						if ((itr->second->GetContent_Int() % 10) != 0)
							activity = true;
						else
							activity = false;

						switch (itr->second->GetContent_Int() / 10)
						{
						case 1:
							m_Map.GetTileMap(TileMap::Depth::B2)->SetActivity(activity);
							break;
						case 2:
							m_Map.GetTileMap(TileMap::Depth::B1)->SetActivity(activity);
							break;
						case 3:
							m_Map.GetTileMap(TileMap::Depth::Zero)->SetActivity(activity);
							break;
						case 4:
							m_Map.GetTileMap(TileMap::Depth::F1)->SetActivity(activity);
							break;
						case 5:
							m_Map.GetTileMap(TileMap::Depth::F2)->SetActivity(activity);
							break;
						}
					}

					if (itr->first == "8_TexBox")
					{
						m_currentTile.SetTexturePos(sf::Vector2i((itr->second->GetContent_Int()) / 10, (itr->second->GetContent_Int()) % 10));
					}

					if (itr->first == "9_AddOptions")
					{
						switch (itr->second->GetContent_Int())
						{
						case 1:
							m_MapGridActive = true;
							break;
						case -1:
							m_MapGridActive = false;
							break;
						case 10:
							std::cout << "In-Game Visibility activated, but function not implemented!" << std::endl;
							break;
						case -10:
							std::cout << "In-Game Visibility de-activated, but function not implemented!" << std::endl;
							break;
						case 100:
							m_TransparencyActive = true;
							SetTransparency(50);
							break;
						case -100:
							m_TransparencyActive = false;
							SetTransparency(255);
							break;
						}							
					}
				}
			}	
		}
		return MakerObjectManager::MakerResult::Continue;
	}

	void MakerObjectManager::SetTransparency(int transparency)
	{
		if (m_currentDepth != TileMap::Depth::B2)
			m_Map.GetTileMap(TileMap::Depth::B2)->SetTransparency(transparency);
		if (m_currentDepth != TileMap::Depth::B1)
			m_Map.GetTileMap(TileMap::Depth::B1)->SetTransparency(transparency);
		if (m_currentDepth != TileMap::Depth::Zero)
			m_Map.GetTileMap(TileMap::Depth::Zero)->SetTransparency(transparency);
		if (m_currentDepth != TileMap::Depth::F1)
			m_Map.GetTileMap(TileMap::Depth::F1)->SetTransparency(transparency);
		if (m_currentDepth != TileMap::Depth::F2)
			m_Map.GetTileMap(TileMap::Depth::F2)->SetTransparency(transparency);

		m_Map.GetTileMap(m_currentDepth)->SetTransparency(255);
	}

	void MakerObjectManager::Add(std::string name, VisibleObject* makerObject)
	{
		makerObjects.insert(std::pair<std::string, VisibleObject*>(name, makerObject));
	}

	void MakerObjectManager::Remove(std::string name)
	{
		std::map<std::string, VisibleObject*>::iterator results = makerObjects.find(name);
		if (results != makerObjects.end())
		{
			delete results->second;
			makerObjects.erase(results);
		}
	}

	VisibleObject* MakerObjectManager::Get(std::string name) const
	{
		std::map<std::string, VisibleObject*>::const_iterator results = makerObjects.find(name);
		if (results == makerObjects.end())
			return NULL;
		return results->second;
	}

	int MakerObjectManager::GetObjectCount() const
	{
		return makerObjects.size();
	}

	void MakerObjectManager::SaveMap()
	{
		m_Map.SaveAll();
	}

	void MakerObjectManager::SetLevel(std::string levelname)
	{
		m_Map.SetLevel(levelname);
	}

	void MakerObjectManager::SetTexture(std::string texture)
	{
		m_Map.SetTexture(texture, m_currentDepth);
		m_currentTexture = m_Map.GetTileMap(m_currentDepth)->GetTexture();
	}


	sf::Vector2i MakerObjectManager::GetCurrentTileSize()
	{
		return m_currentTileSize;
	}

	void MakerObjectManager::BuildBorderAndGrid()
	{
		m_MapBorder.setSize(sf::Vector2f(m_currentNumberTiles.x * m_currentTileSize.x * 1.0f, m_currentNumberTiles.y * m_currentTileSize.y * 1.0f));	
		sf::Vertex vertex;
		sf::Color color;
		m_MapGrid.resize(0);
		for (int i = 1; i < m_currentNumberTiles.x; i++)
		{
			if (i % 5 == 0)
				color = sf::Color(238, 173, 14, 255);
			else
				color = sf::Color(138, 138, 138, 255);
			vertex = sf::Vertex(sf::Vector2f(i*m_currentTileSize.x * 1.0f, 0.f), color);
			m_MapGrid.append(vertex);
			vertex = sf::Vertex(sf::Vector2f(i*m_currentTileSize.x * 1.0f, m_currentTileSize.y * m_currentNumberTiles.y * 1.0f), color);
			m_MapGrid.append(vertex);
		}
		for (int i = 1; i < m_currentNumberTiles.y; i++)
		{
			if (i % 5 == 0)
				color = sf::Color(238, 173, 14, 255);
			else
				color = sf::Color(138, 138, 138, 255);
			vertex = sf::Vertex(sf::Vector2f(0, i*m_currentTileSize.y * 1.0f), color);
			m_MapGrid.append(vertex);
			vertex = sf::Vertex(sf::Vector2f(m_currentTileSize.x * m_currentNumberTiles.x * 1.0f, i*m_currentTileSize.y * 1.0f), color);
			m_MapGrid.append(vertex);
		}
	}

	void MakerObjectManager::Resize(bool is_start, int type, sf::Vector2f move)
	{
		// Abfangen WELCHER Rand geklickt wurde!!!		
		if (is_start)
		{
			if (type == 1)
			{
				m_tempBorderMove -= move.x;
				m_tempBorderRect.setPosition(m_currentNumberTiles.x * m_currentTileSize.x * 1.0f + 2, 0.f);
				m_tempBorderRect.setSize(sf::Vector2f(m_tempBorderMove, m_currentNumberTiles.y * m_currentTileSize.y * 1.0f));
				
			}
			if (type == 2)
			{
				m_tempBorderMove -= move.y;
				m_tempBorderRect.setPosition(0.f, m_currentNumberTiles.y * m_currentTileSize.y * 1.0f + 2);
				m_tempBorderRect.setSize(sf::Vector2f(m_currentNumberTiles.x * m_currentTileSize.x * 1.0f, m_tempBorderMove));
			}
				
		}
		else
		{
			if (type == 1)
			{
				m_currentNumberTiles.x += static_cast<int>(std::round(m_tempBorderMove / (m_currentTileSize.x)));
				if (m_currentNumberTiles.x < 1)
					m_currentNumberTiles.x = 1;
			}
			if (type == 2)
			{
				m_currentNumberTiles.y += static_cast<int>(std::round(m_tempBorderMove / (m_currentTileSize.y)));
				if (m_currentNumberTiles.y < 1)
					m_currentNumberTiles.y = 1;
			}
			m_Map.SetMapSize(m_currentNumberTiles);
			m_tempBorderMove = 0;
			BuildBorderAndGrid();
		}
	}
}
