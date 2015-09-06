#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include "Tiles.hpp"

namespace mm
{
	class TileMap : public sf::Drawable
	{
	public:
		enum Depth {B2, B1, Zero, F1, F2 };
		// z-Information, sorted: B1, B2, Zero, F1, F2

		TileMap(std::string levelname = "", sf::Vector2i tileSize = sf::Vector2i(50, 50), Depth depth = Zero, bool m_isActive = true);
		virtual ~TileMap();

		void Load();
		void draw(sf::RenderTarget& target, sf::RenderStates states) const;
		bool SaveLevel();
		void TileMap::UpdateTile(Tiles updatedTile);

		// <<<<<<<<<<<<<<<<<<< TEXTURE-SIZE HERE >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
		void SetTexture(std::string newTextureName, sf::Vector2i textureSize = sf::Vector2i(72, 72)); 
		const std::string GetTextureName();
		sf::Texture GetTexture();

		void SetLevel(std::string newLevelName);		
		const std::string GetLevelName();		

		void SetNumberTiles(sf::Vector2i numberTiles);
		sf::Vector2i GetNumberTiles();

		void SetTileSize(sf::Vector2i tileSize);
		sf::Vector2i GetTileSize();
		
		void SetActivity(bool active);
		bool GetActivity();

		const Depth GetDepth();
		void CreateVertexArrays();

		void SetTransparency(int transparency);

	private:
		const Depth m_depth;

		std::string m_levelname;
		std::string m_texturename;

		sf::Vector2i m_tileSize;
		int m_transparency = 255;

		// <<<<<<<<<<<<<<<<<<< TEXTURE-SIZE HERE >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
		sf::Vector2i m_textureSize = sf::Vector2i(72, 72);
		sf::Texture m_texture;
		sf::VertexArray m_VertexArray;
		
		sf::Vector2i m_numberTiles; // how many Tiles in x and y
		std::map<std::pair<int,int>, Tiles> m_TileMap;
		bool m_isLoaded;
		bool m_isActive;
	};
}