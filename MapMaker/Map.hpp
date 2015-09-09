#pragma once
#include <SFML/Graphics.hpp>
#include "TileMap.hpp"

namespace mm
{
	class Map
	{
	public:
		Map();
		~Map();

		void Add(TileMap::Depth depth, TileMap* tileMap);
		void Remove(TileMap::Depth depth);
		int GetMapCount() const;
		
		// All Maps :
		void DrawAll(sf::RenderWindow &renderWindow);
		void SaveAll();
		void SetLevel(std::string newLevelName);
		void SetTileSize(sf::Vector2i newTileSize);
		void SetMapSize(sf::Vector2i numberTiles);
		void RefreshVertexArrays();
		
		// Single Map:
		void UpdateTile(Tiles updatedTile, TileMap::Depth currentDepth);
		void SetTexture(std::string newTexture, TileMap::Depth currentDepth);
		void SwapActivity(TileMap::Depth currentDepth);
		TileMap* GetTileMap(TileMap::Depth currentDepth) const;

		// MapGrid & MapBorder
		void Load();
		

	private:
		std::map<TileMap::Depth, TileMap*> TileMapObjects;

		struct TileMapDeallocator
		{
			void operator()(const std::pair<TileMap::Depth, TileMap*>& p_TileMapObject) const
			{
				delete p_TileMapObject.second;
			}
		};
	};
}