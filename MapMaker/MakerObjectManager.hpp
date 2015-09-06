#pragma once
#include "Map.hpp"
#include "Background.hpp"
#include "SaveButton.hpp"
#include "LevelTextbox.hpp"
#include "TextureTextbox.hpp"
#include "TilesizeTextbox.hpp"
#include "Shape.hpp"
#include "Layer.hpp"
#include "TextureBox.hpp"
#include "LayerVisibility.hpp"
#include "AddOptions.hpp"
#include "SFML\Graphics.hpp"
#include <string>
#include <map>




namespace mm
{
	class MakerObjectManager
	{
	public:
		MakerObjectManager();
		~MakerObjectManager();
		void Load(std::string levelname, sf::Vector2i tileSize = sf::Vector2i(50, 50));

		enum MakerResult { Continue, Save, ResizeMap_x, ResizeMap_y, 
						   TextBox_Level, TextBox_Texture, Textbox_TileSize};  //ToDO: Add Rezise Both

		void Add(std::string name, VisibleObject* makerObject);
		void Remove(std::string name);
		void Resize(bool is_start, int type = 0, sf::Vector2f move = sf::Vector2f(0.f, 0.f));
		int GetObjectCount() const;
		VisibleObject* Get(std::string name) const;
		
		void SaveMap();
		void SetLevel(std::string levelname);
		void SetTexture(std::string texture);
		sf::Vector2i GetCurrentTileSize();
		void TilePreview(sf::Vector2i mouseXY);

		void DrawAll(sf::RenderWindow &renderWindow, sf::View mapView);
		MakerResult UpdateAll(sf::Vector2i mouseXY, bool Map_or_Menu); 

	private:
		std::map<std::string, VisibleObject*> makerObjects;
		sf::Texture m_MakerTextureSet;
		sf::Font usedFont;
		Map m_Map;

		TileMap::Depth m_currentDepth;
		sf::Vector2i m_currentTileSize;
		sf::Vector2i m_currentNumberTiles;
		sf::Texture m_currentTexture;
		Tiles m_currentTile;
		bool m_currentTileVisible;

		void BuildBorderAndGrid();
		sf::VertexArray m_MapGrid;
		bool m_MapGridActive;
		bool m_TransparencyActive;
		void SetTransparency(int transparency);
		sf::RectangleShape m_MapBorder;
		float m_tempBorderMove = 0;
		sf::RectangleShape m_tempBorderRect;		

		// FUNCTOR!!!
		struct ObjectDeallocator
		{
			void operator()(const std::pair<std::string, VisibleObject*> & p_Object) const
			{
				delete p_Object.second;
			}
		};
	};
}


/*

*/