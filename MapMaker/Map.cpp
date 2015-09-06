#include "Map.hpp"

namespace mm
{
	Map::Map()
	{
		
	}

	Map::~Map()
	{
		std::for_each(TileMapObjects.begin(), TileMapObjects.end(), TileMapDeallocator()); //Functor
	}

	void Map::Load()
	{
	}

	void Map::SwapActivity(TileMap::Depth currentDepth)
	{
		std::map<TileMap::Depth, TileMap*>::const_iterator results = TileMapObjects.find(currentDepth);
		if (results == TileMapObjects.end())
		{
			std::cout << "Map with specified dpeth not found!" << std::endl;
			return;
			// THORW ERROR <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
		}
		results->second->SetActivity(!results->second->GetActivity());
	}

	void Map::SetTexture(std::string newTexture, TileMap::Depth currentDepth)
	{
		std::map<TileMap::Depth, TileMap*>::const_iterator results = TileMapObjects.find(currentDepth);
		if (results == TileMapObjects.end())
		{
			std::cout << "Map with specified dpeth not found!" << std::endl;
			return;
			// THORW ERROR <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
		}
		// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
		// <<<<<<<<<<<<<<<<<<< TEXTURE-SIZE HERE >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
		// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
		results->second->SetTexture(newTexture);
	}

	void Map::SetLevel(std::string newLevelName)
	{
		for (std::map<TileMap::Depth, TileMap*>::const_iterator itr = TileMapObjects.begin(); itr != TileMapObjects.end(); itr++)
		{
			itr->second->SetLevel(newLevelName);
		}
	}

	void Map::SetTileSize(sf::Vector2i newTileSize)
	{
		for (std::map<TileMap::Depth, TileMap*>::const_iterator itr = TileMapObjects.begin(); itr != TileMapObjects.end(); itr++)
		{
			itr->second->SetTileSize(newTileSize);
		}
	}

	void Map::Add(TileMap::Depth depth, TileMap* tileMap)
	{
		TileMapObjects.insert(std::pair<TileMap::Depth, TileMap*>(depth, tileMap));
	}

	void Map::Remove(TileMap::Depth depth)
	{
		std::map<TileMap::Depth, TileMap*>::iterator results = TileMapObjects.find(depth);
		if (results != TileMapObjects.end())
		{
			delete results->second;
			TileMapObjects.erase(results);
		}
	}

	TileMap* Map::GetTileMap(TileMap::Depth currentDepth) const
	{
		std::map<TileMap::Depth, TileMap*>::const_iterator results = TileMapObjects.find(currentDepth);
		if (results == TileMapObjects.end())
			return NULL;
		return results->second;
	}

	int Map::GetMapCount() const
	{
		return TileMapObjects.size();
	}


	void Map::DrawAll(sf::RenderWindow& renderWindow)
	{
		sf::RenderStates states;
		for (std::map<TileMap::Depth, TileMap*>::const_iterator itr = TileMapObjects.begin(); itr != TileMapObjects.end(); itr++)
		{
			itr->second->draw(renderWindow, states);
		}
	}

	void Map::SetMapSize(sf::Vector2i numberTiles)
	{
		for (std::map<TileMap::Depth, TileMap*>::const_iterator itr = TileMapObjects.begin(); itr != TileMapObjects.end(); itr++)
		{
			itr->second->SetNumberTiles(numberTiles);
		}
	}

	void Map::UpdateTile(Tiles updatedTile, TileMap::Depth currentDepth)
	{
		std::map<TileMap::Depth, TileMap*>::const_iterator results = TileMapObjects.find(currentDepth);
		if (results == TileMapObjects.end())
		{
			std::cout << "Map with specified dpeth not found!" << std::endl;
			return;
			// THORW ERROR <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
		}
		results->second->UpdateTile(updatedTile);
	}

	void Map::SaveAll()
	{
		std::string LevelName = TileMapObjects.find(TileMap::Depth::Zero)->second->GetLevelName();
		sf::Vector2i LevelSize = TileMapObjects.find(TileMap::Depth::Zero)->second->GetNumberTiles();

		std::ofstream stream(LevelName, std::ofstream::trunc);
		if (stream.is_open())
		{
			std::cout << "\nWriting to File: " << LevelName << std::endl;
			stream << "LevelSize: " << LevelSize.x << " " << LevelSize.y << "\n" << std::endl;
			stream.close();
			for (std::map<TileMap::Depth, TileMap*>::const_iterator itr = TileMapObjects.begin(); itr != TileMapObjects.end(); itr++)
			{
				if (itr->second->SaveLevel())
				{
					std::cout << "Layer " << itr->first << " saved successfully!" << std::endl;
				}
			}
			std::cout << "All Layers successfully saved into the file: " << LevelName << std::endl;
			return;
		}
		else
		{
			std::cout << "ERROR: Can't open: " << LevelName << std::endl;
			return;
		}
	}

	void Map::RefreshVertexArrays()
	{
		for (std::map<TileMap::Depth, TileMap*>::const_iterator itr = TileMapObjects.begin(); itr != TileMapObjects.end(); itr++)
		{
			itr->second->CreateVertexArrays();
		}
	}
}