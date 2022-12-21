#include "Menu.h"

/* Constructor of the Menu class. */
Menu::Menu()
	:m_helpRequest(false)
{
	/* Loads the textures of the menu. */
	for (int i = 0; i < numofTextures; i++)
	{
		sf::Texture* tempTexture = Textures::instance().getMenuTexture((Menu_t)i);
		sf::Sprite tempSprite = sf::Sprite();
		tempSprite.setTexture(*tempTexture);

		if ((Menu_t)i == newGame || (Menu_t)i == newGameHL)
			tempSprite.setPosition(sf::Vector2f(538, 310));

		if ((Menu_t)i == help || (Menu_t)i == helpHL)
			tempSprite.setPosition(sf::Vector2f(538, 380));

		if ((Menu_t)i == exitGame || (Menu_t)i == exitGameHL)
			tempSprite.setPosition(sf::Vector2f(538, 450));
		
		if ((Menu_t)i == exitHelp || (Menu_t)i == exitHelpHL)
			tempSprite.setPosition(sf::Vector2f(buttonWidth, buttonHeight));

		if ((float)i < (float)numofTextures / 2)
		{
			this->m_reHovered.push_back(false);
			this->m_usedSprites.push_back(tempSprite);
		}

		this->m_menuSprites.push_back(tempSprite);
	}

	this->setTitle(); // Sets the title of the menu.
	this->initMenuWindow(); // Initiates the menu window.
}

/* This function is in charge of running the menu. */
void Menu::runMenu(Sound& sound)
{
	// Menu loop.
	while (this->m_menuWindow->isOpen())
	{
		this->render();
		this->pollEvents(sound);
	}
}

/* This function is in charge of drawing the menu. */
void Menu::drawMenu()
{
	if (!this->m_helpRequest) // If not help mode.
	{
		for (int i = 0; i < m_usedSprites.size() - 1; i++)
			this->m_menuWindow->draw(m_usedSprites[i]);

		this->m_menuWindow->draw(this->m_text);
	}
	else // Help mode.
	{
		this->m_menuWindow->draw(m_menuSprites[helpDisplay]);
		this->m_menuWindow->draw(m_usedSprites[exitHelp]);
	}
}

/* This function is in charge of setting the visuals of the menu title. */
void Menu::setTitle()
{
	this->m_font.loadFromFile("amatic.ttf"); // Font.

	// Visuals of the title text.
	this->m_text.setFont(this->m_font);
	this->m_text.setString(GAME_NAME);
	this->m_text.setCharacterSize(150);
	this->m_text.setPosition(sf::Vector2f(390, 130));
	this->m_text.setStyle(sf::Text::Style::Bold);
	this->m_text.setOutlineColor(sf::Color::Black);
	this->m_text.setOutlineThickness(1);
}

/* This function is in charge of handling the events. */
void Menu::pollEvents(Sound& sound)
{
	/* Events loop. */
	while (this->m_menuWindow->pollEvent(this->m_menuEvent))
	{
		switch (this->m_menuEvent.type)
		{
		case sf::Event::Closed: // Closed game.
			exit(EXIT_SUCCESS);
			break;

		case sf::Event::KeyPressed: // Pressed a key in the keyboard.
			if (this->m_menuEvent.key.code == sf::Keyboard::Escape) // Exit.
				exit(EXIT_SUCCESS);
			if (this->m_menuEvent.key.code == sf::Keyboard::M) // Mute/unmute.
				sound.muteVolume();
			break;

		case sf::Event::MouseButtonReleased: // Clicked on the menu.
			handleClick(m_menuWindow->mapPixelToCoords({ this->m_menuEvent.mouseButton.x, this->m_menuEvent.mouseButton.y }), sound);
			break;

		case sf::Event::MouseMoved: // Moved the mouse on the menu.
		{
			sf::Vector2i mouse_loc = sf::Mouse::getPosition(*this->m_menuWindow); // Current position of the mouse.
			highlight(mouse_loc, sound);
			break;
		}

		default:
			break;
		}
	}
}

/* This function is in charge of displaying the menu. */
void Menu::render()
{
	this->m_menuWindow->clear(sf::Color{ 0x373737FF });

	/* Draw here. */
	this->drawMenu();

	this->m_menuWindow->display();
}

/* This function is in charge of 'highlighting' buttons which are hovered on. */
void Menu::highlight(sf::Vector2i loc, Sound& sound)
{
	// Loops through the used buttons.
	for (int i = 1; i < this->m_usedSprites.size(); i++)
	{
		// Asks if the 'i' button contains the mouse loc.
		if (this->m_usedSprites[i].getGlobalBounds().contains((sf::Vector2f)loc))
		{
			// Asks if not in help mode.
			if (!this->m_helpRequest)
			{
				if ((Menu_t)i == newGame)
				{
					if (!this->m_reHovered[newGame])
					{
						this->m_reHovered[newGame] = true;
						this->m_usedSprites[i] = this->m_menuSprites[newGameHL];
						sound.playSound(hoverSound);
					}
				}

				if ((Menu_t)i == help)
				{
					if (!this->m_reHovered[help])
					{
						this->m_reHovered[help] = true;
						this->m_usedSprites[i] = this->m_menuSprites[helpHL];
						sound.playSound(hoverSound);
					}
				}

				if ((Menu_t)i == exitGame)
				{
					if (!this->m_reHovered[exitGame])
					{
						this->m_reHovered[exitGame] = true;
						this->m_usedSprites[i] = this->m_menuSprites[exitGameHL];
						sound.playSound(hoverSound);
					}
				}
			}
			// In help mode.
			else
			{
				if ((Menu_t)i == exitHelp)
				{
					if (!this->m_reHovered[exitHelp])
					{
						this->m_reHovered[exitHelp] = true;
						this->m_usedSprites[i] = this->m_menuSprites[exitHelpHL];
						sound.playSound(hoverSound);
					}
				}
			}
		}
		/* Doesn't contain the mouse loc. */
		else
		{
			if ((Menu_t)i == newGame)
			{
				this->m_usedSprites[i] = this->m_menuSprites[newGame];
				this->m_reHovered[newGame] = false;
			}

			if ((Menu_t)i == help)
			{
				this->m_usedSprites[i] = this->m_menuSprites[help];
				this->m_reHovered[help] = false;
			}

			if ((Menu_t)i == exitGame)
			{
				this->m_usedSprites[i] = this->m_menuSprites[exitGame];
				this->m_reHovered[exitGame] = false;
			}

			if ((Menu_t)i == exitHelp)
			{
				this->m_usedSprites[i] = this->m_menuSprites[exitHelp];
				this->m_reHovered[exitHelp] = false;
			}
		}
	}
}

/* Returns a sprite of the menu. */
sf::Sprite Menu::getMenuSprite(int place) const
{
	return this->m_menuSprites[place];
}

/* For the use of the game itself. */
void Menu::setHelpAndExitPos(sf::Vector2f helpPos, sf::Vector2f exitPos)
{
	this->m_menuSprites[helpDisplay].setPosition(helpPos);
	this->m_menuSprites[exitHelp].setPosition(exitPos);
	this->m_menuSprites[exitHelpHL].setPosition(exitPos);
}

/* This function is in charge of handling the users' click on the menu. */
void Menu::handleClick(sf::Vector2f pos, Sound& sound)
{
	// If not in help mode.
	if (!this->m_helpRequest)
	{
		// Loops through used sprites.
		for (int i = 1; i < m_usedSprites.size() - 1; i++)
		{
			// Asks if the 'i' sprite contains the click.
			if (m_menuSprites[i].getGlobalBounds().contains(pos))
			{
				if ((Menu_t)i == newGame)
				{
					sound.playSound(gameStart);
					this->m_menuWindow->close();
				}

				if ((Menu_t)i == help)
				{
					sound.playSound(clickSound);
					this->m_helpRequest = true;
				}

				if ((Menu_t)i == exitGame)
					exit(EXIT_SUCCESS);
			}
		}
	}
	// Help mode.
	else if (m_menuSprites[exitHelp].getGlobalBounds().contains(pos))
	{
		sound.playSound(clickSound);
		this->m_helpRequest = false;
	}
}

/* This function is in charge of initiating the menu's window. */
void Menu::initMenuWindow()
{
	this->m_menuVideo.height = menuHeight;
	this->m_menuVideo.width = menuWidth;
	this->m_menuWindow = new sf::RenderWindow(this->m_menuVideo, GAME_NAME, sf::Style::Close | sf::Style::Titlebar);
}
