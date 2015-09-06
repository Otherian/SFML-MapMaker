#include "MapMaker.hpp"

namespace mm
{
	MapMaker::MapMaker()
	{
	}

	MapMaker::~MapMaker()
	{
	}

	void MapMaker::Start()
	{
		if (makerState != Uninitialized)
			return;

		mainWindow.create(sf::VideoMode(1440, 900), "MapMaker", sf::Style::Close);
		mainWindow.setVerticalSyncEnabled(true);
		makerState = Making; 
		makerResult = MakerObjectManager::MakerResult::Continue;

		// Load makerObjectManager
		makerObjectManager.Load("resources/Template.txt", sf::Vector2i(50, 50));
		// -----------------------
		// Set View(port) for Map
		MapView = sf::View(sf::FloatRect(0, 0, 1000, 880));
		MapView.setViewport(sf::FloatRect(427.0f / 1440.0f, 1.0f / 90.0f, 25.0f / 36.0f, 44.0f / 45.0f));
		MapView.move(-4, -4);
		mainWindow.setView(MapView);
		// -----------------------


		while (!IsExiting())
		{
			EventLoop();
		}

		mainWindow.close();
	}

	bool MapMaker::IsExiting()
	{
		if (makerState == Exiting)
			return true;
		else
			return false;
	}

	void MapMaker::EventLoop()
	{
		switch(makerState)
		{
		case Making:
			sf::Event currentEvent;
			MouseCoordinates = sf::Vector2i(0, 0);

			while (mainWindow.pollEvent(currentEvent))
			{
				if (currentEvent.type == sf::Event::Closed || (currentEvent.type == sf::Event::KeyPressed && currentEvent.key.code == sf::Keyboard::Escape))
				{
					makerState = Exiting;
					makerResult = MakerObjectManager::MakerResult::Save;
					SaveScreen();
				}
				if (currentEvent.type == sf::Event::KeyPressed && currentEvent.key.code == sf::Keyboard::Left)
				{
					MapView.move(7, 0);
				}
				if (currentEvent.type == sf::Event::KeyPressed && currentEvent.key.code == sf::Keyboard::Right)
				{
					MapView.move(-7, 0);
				}
				if (currentEvent.type == sf::Event::KeyPressed && currentEvent.key.code == sf::Keyboard::Up)
				{
					MapView.move(0, 7);
				}
				if (currentEvent.type == sf::Event::KeyPressed && currentEvent.key.code == sf::Keyboard::Down)
				{
					MapView.move(0, -7);
				}
				if (currentEvent.type == sf::Event::MouseMoved)
				{
					sf::Vector2f distance = sf::Vector2f((oldMouseCoordinates.x - currentEvent.mouseMove.x) * MapView.getSize().x / 1000, (oldMouseCoordinates.y - currentEvent.mouseMove.y) * MapView.getSize().x / 1000);
					// Map-Move
					if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && currentEvent.mouseMove.x > 427 && currentEvent.mouseMove.x  < 1427
																	 && currentEvent.mouseMove.y > 10 && currentEvent.mouseMove.y < 890)
					{
						//float zoomfaktor = MapView.getSize().x / 1000;
						MapView.move(distance);
					}
					// ---------

					// If leavin / joining Map-Area --> Switch state of TilePreview | (ugly but works this way :<)
					if (oldMouseCoordinates.x <= 427 && currentEvent.mouseMove.x > 427)
					{
						mainWindow.setView(MapView);
						makerObjectManager.TilePreview(sf::Vector2i(mainWindow.mapPixelToCoords(sf::Vector2i(static_cast<int>(currentEvent.mouseMove.x), static_cast<int>(currentEvent.mouseMove.y)))));
					}
					if (oldMouseCoordinates.x >= 427 && currentEvent.mouseMove.x < 427)
					{
						makerObjectManager.TilePreview(sf::Vector2i(-10, -10));
					}
					// ---------

					// Drawing with pressed LeftMouseButton || CAREFULL: >>>>>>> OVERWRITES MOUSE- and OLDMOUSECOORDINATE!!!! <<<<<<<
					if (makerResult == MakerObjectManager::MakerResult::Continue
						&& currentEvent.mouseMove.x > 427 && currentEvent.mouseMove.x  <1427
						&& currentEvent.mouseMove.y > 10 && currentEvent.mouseMove.y < 890)
					{
						mainWindow.setView(MapView);
						sf::Vector2i tilesize = makerObjectManager.GetCurrentTileSize();
						MouseCoordinates = sf::Vector2i(mainWindow.mapPixelToCoords(sf::Vector2i(static_cast<int>(currentEvent.mouseMove.x), static_cast<int>(currentEvent.mouseMove.y))));
						oldMouseCoordinates = sf::Vector2i(mainWindow.mapPixelToCoords(sf::Vector2i(static_cast<int>(oldMouseCoordinates.x), static_cast<int>(oldMouseCoordinates.y))));

						// CHeck if transition into another tile:
						if ((MouseCoordinates.x / tilesize.x != oldMouseCoordinates.x / tilesize.x) || (MouseCoordinates.y / tilesize.y != oldMouseCoordinates.y / tilesize.y) || 
							(MouseCoordinates.x < 0 && oldMouseCoordinates.x >= 0) || (MouseCoordinates.y < 0 && oldMouseCoordinates.y >= 0) || 
							(MouseCoordinates.x > 0 && oldMouseCoordinates.x <= 0) || (MouseCoordinates.y > 0 && oldMouseCoordinates.y <= 0))
						{
							if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
								makerResult = makerObjectManager.UpdateAll(MouseCoordinates, true);
							else
								makerObjectManager.TilePreview(MouseCoordinates);
						}
					}
					// ---------

					// Resize Map in x
					if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && makerResult == MakerObjectManager::MakerResult::ResizeMap_x)
					{
						makerObjectManager.Resize(true, 1, distance);
						
					}
					// ---------

					// Resize Map in y
					if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && makerResult == MakerObjectManager::MakerResult::ResizeMap_y)
					{
						makerObjectManager.Resize(true, 2, distance);

					}
					// ---------

					// TODO:
					// DRAG Funktion fuer Tiles
					// neue Bool in makerObjectManager ob DRAG aktiv ist
					// --> wenn ja: hier ne Liste erzeugen aller MausPositionen
					// makerObjectManager.UpdateAll() überladen mit MouseListe und blarb...
					// UNTEN bei aktivierter Drag FUnktion das Update DEAKTIVIEREN!!!!
					// --> Strg+C und Strg+V Modus einbauen bei eingeschaltetem Drag!

					oldMouseCoordinates = sf::Vector2i(currentEvent.mouseMove.x, currentEvent.mouseMove.y);
				}
				if (currentEvent.type == sf::Event::MouseWheelScrolled)
				{
					if(currentEvent.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel && currentEvent.mouseWheelScroll.delta > 0)
						MapView.zoom(0.95f);
					else if(currentEvent.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel && currentEvent.mouseWheelScroll.delta < 0)
						MapView.zoom(1.05f);
				}

				// Update Elements after Mouseclick
				if(currentEvent.type == sf::Event::MouseButtonPressed && currentEvent.mouseButton.button == sf::Mouse::Left)
				{
					MouseCoordinates = sf::Vector2i(currentEvent.mouseButton.x, currentEvent.mouseButton.y);
					if (MouseCoordinates.x < 427) // Click not in Map-Region
					{
						makerResult = makerObjectManager.UpdateAll(MouseCoordinates, false);
					}
					else // Click in Map-Region --> Transform MouseCoords...
					{
						mainWindow.setView(MapView);
						MouseCoordinates = sf::Vector2i(mainWindow.mapPixelToCoords(sf::Vector2i(static_cast<int>(MouseCoordinates.x), static_cast<int>(MouseCoordinates.y))));
						makerResult = makerObjectManager.UpdateAll(MouseCoordinates, true);
					}
				}
				if (currentEvent.type == sf::Event::MouseButtonReleased && currentEvent.mouseButton.button == sf::Mouse::Left)
				{
					if (makerResult == MakerObjectManager::MakerResult::ResizeMap_x)	
					{
						makerObjectManager.Resize(false, 1);
						makerResult = MakerObjectManager::MakerResult::Continue;
					}
					if (makerResult == MakerObjectManager::MakerResult::ResizeMap_y)
					{
						makerObjectManager.Resize(false, 2);
						makerResult = MakerObjectManager::MakerResult::Continue;
					}
						
				}

			}

			if (makerResult == MakerObjectManager::MakerResult::Save)
				SaveScreen();				

			if (makerResult == MakerObjectManager::MakerResult::TextBox_Level ||
				makerResult == MakerObjectManager::MakerResult::TextBox_Texture ||
				makerResult == MakerObjectManager::MakerResult::Textbox_TileSize)
				Textbox();

			mainWindow.clear(sf::Color::Black);
			makerObjectManager.DrawAll(mainWindow, MapView);
			mainWindow.display();
			break;
		}
	}

	void MapMaker::Textbox()
	{
		VisibleObject* Textbox;

		if(makerResult == MakerObjectManager::MakerResult::TextBox_Level)
			Textbox = makerObjectManager.Get("2_LevelText");
		if(makerResult == MakerObjectManager::MakerResult::TextBox_Texture)
			Textbox = makerObjectManager.Get("3_TextureText");
		if (makerResult == MakerObjectManager::MakerResult::Textbox_TileSize)
			Textbox = makerObjectManager.Get("4_TilesizeText");
		
		std::string old_content = Textbox->GetContent_String();
		std::string new_content;
		Textbox->SetContent_String("");
		Textbox->SetActivity(true);

		while (makerResult == MakerObjectManager::MakerResult::TextBox_Level ||
			   makerResult == MakerObjectManager::MakerResult::TextBox_Texture ||
			   makerResult == MakerObjectManager::MakerResult::Textbox_TileSize)
		{
			sf::Event currentEvent;
			while (mainWindow.pollEvent(currentEvent))
			{
				new_content = Textbox->GetContent_String();
				if (currentEvent.type == sf::Event::KeyPressed && currentEvent.key.code == sf::Keyboard::Escape)
				{
					Textbox->SetContent_String(old_content);
					Textbox->SetActivity(false);
					makerResult = MakerObjectManager::MakerResult::Continue;
				}

				if (currentEvent.type == sf::Event::MouseButtonPressed && currentEvent.mouseButton.button == sf::Mouse::Left)
				{
					if (!Textbox->Update(sf::Vector2i(currentEvent.mouseButton.x, currentEvent.mouseButton.y)))
					{
						Textbox->SetContent_String(old_content);
						Textbox->SetActivity(false);
						makerResult = MakerObjectManager::MakerResult::Continue;
					}
				}

				if (currentEvent.type == sf::Event::KeyPressed && currentEvent.key.code == sf::Keyboard::BackSpace)
				{
					if(new_content != "")
						new_content.erase(new_content.end() - 1);
					Textbox->SetContent_String(new_content);
				}

				if (currentEvent.type == sf::Event::TextEntered)
				{
					// Zahlen: 48 - 57
					if ((currentEvent.text.unicode <= 57 && currentEvent.text.unicode >= 44) ||
						(currentEvent.text.unicode <= 90 && currentEvent.text.unicode >= 65) ||
						(currentEvent.text.unicode <= 122 && currentEvent.text.unicode >= 97) ||
						currentEvent.text.unicode == 95 || currentEvent.text.unicode == 32)
					{
						new_content += static_cast<char>(currentEvent.text.unicode);
						Textbox->SetContent_String(new_content);
					}
				}

				// RETURN for Level-Textbox
				if ((currentEvent.type == sf::Event::KeyPressed && currentEvent.key.code == sf::Keyboard::Return)
					&& makerResult == MakerObjectManager::MakerResult::TextBox_Level)
				{
					std::string levelname = "resources/" + new_content;
					std::fstream file(levelname);
					if (file.good())
					{
						file.close();
						makerObjectManager.SetLevel(levelname);
					}
					else
					{
						file.close();
						levelname = "resources/" + new_content + ".txt";
						std::fstream file(levelname);
						if (file.good())
						{
							file.close();
							makerObjectManager.SetLevel(levelname);
							Textbox->SetContent_String(new_content+ ".txt");
						}
						else
						{
							std::cout << "ERROR: Could not find " << new_content << "!" << std::endl;
							Textbox->SetContent_String(old_content);
							file.close();
						}
					}
					makerResult = MakerObjectManager::MakerResult::Continue;
				}

				// RETURN for Texture-Textbox
				if ((currentEvent.type == sf::Event::KeyPressed && currentEvent.key.code == sf::Keyboard::Return)
					&& makerResult == MakerObjectManager::MakerResult::TextBox_Texture)
				{
					std::string texturename = "resources/" + new_content;
					std::fstream file(texturename);
					if (file.good())
					{
						file.close();
						makerObjectManager.SetTexture(texturename);
					}
					else
					{
						file.close();
						texturename = "resources/" + new_content + ".png";
						std::fstream file(texturename);
						if (file.good())
						{
							file.close();
							makerObjectManager.SetTexture(texturename);
							Textbox->SetContent_String(new_content + ".png");
						}
						else
						{
							std::cout << "ERROR: Could not find " << new_content << "!" << std::endl;
							Textbox->SetContent_String(old_content);
							file.close();
						}
					}
					makerResult = MakerObjectManager::MakerResult::Continue;
				}

				// RETURN for TileSize-Textbox
				if ((currentEvent.type == sf::Event::KeyPressed && currentEvent.key.code == sf::Keyboard::Return)
					&& makerResult == MakerObjectManager::MakerResult::Textbox_TileSize)
				{
					// ---------------------------------------------
							// ????????????????????????????????????????????
					// ---------------------------------------------
					Textbox->SetContent_String(old_content);
					makerResult = MakerObjectManager::MakerResult::Continue;
				}
			}

			mainWindow.clear(sf::Color::Black);
			makerObjectManager.DrawAll(mainWindow, MapView);
			mainWindow.display();
		}
		Textbox->SetActivity(false);
	}

	void MapMaker::SaveScreen()
	{
		
		sf::Font font;
		if (!font.loadFromFile("resources/arialbd.ttf"))
			std::cout << "ERROR: Could not open fond!" << std::endl;

		sf::Text text;
		text.setFont(font);
		text.setString(makerObjectManager.Get("2_LevelText")->GetContent_String());
		text.setCharacterSize(30);
		text.setColor(sf::Color::Red);
		text.setPosition(520 + (400.0f - text.getGlobalBounds().width)/2, 360);

		sf::Sprite sprite;
		sf::Texture texture;
		if(!texture.loadFromFile("resources/SaveText.png"))
			std::cout << "ERROR: Could not open SaveWindow!" << std::endl;
		sprite.setTexture(texture);
		sprite.setPosition(sf::Vector2f(520.f, 280.0f));

		sf::IntRect HitRect_Save = sf::IntRect(557, 424, 158, 49);
		sf::IntRect HitRect_Cancel = sf::IntRect(726, 424, 158, 49);

		while (makerResult == MakerObjectManager::MakerResult::Save)
		{
			sf::Event currentEvent;
			while (mainWindow.pollEvent(currentEvent))
			{
				if (currentEvent.type == sf::Event::KeyPressed && currentEvent.key.code == sf::Keyboard::Escape)
				{
					makerResult = MakerObjectManager::MakerResult::Continue;
				}

				if (currentEvent.type == sf::Event::MouseButtonPressed && currentEvent.mouseButton.button == sf::Mouse::Left)
				{
					if (HitRect_Cancel.contains(currentEvent.mouseButton.x, currentEvent.mouseButton.y))
					{
						makerResult = MakerObjectManager::MakerResult::Continue;
						break;
					}
					if (HitRect_Save.contains(currentEvent.mouseButton.x, currentEvent.mouseButton.y))
					{
						makerObjectManager.SaveMap();
						makerResult = MakerObjectManager::MakerResult::Continue;
						break;
					}
				}
			}

			mainWindow.clear(sf::Color::Black);
			makerObjectManager.DrawAll(mainWindow, MapView);
			mainWindow.setView(mainWindow.getDefaultView());
			mainWindow.draw(sprite);
			mainWindow.draw(text);
			mainWindow.display();
		}

	}
}