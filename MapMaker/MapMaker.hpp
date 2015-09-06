#pragma once
#include "SFML/Graphics.hpp"
#include "MakerObjectManager.hpp"

namespace mm
{
	class MapMaker
	{
	public:
		MapMaker();
		~MapMaker();
		void Start();

	private:
		bool IsExiting();
		void EventLoop();
		void SaveScreen();
		void Textbox();

		enum MakerState { Uninitialized, Exiting, Making};

		MakerState makerState = Uninitialized;
		sf::RenderWindow mainWindow;
		sf::View MapView;
		//sf::Clock frameClock;
		MakerObjectManager makerObjectManager;
		sf::Vector2i oldMouseCoordinates;
		sf::Vector2i MouseCoordinates;
		MakerObjectManager::MakerResult makerResult;
	};

}