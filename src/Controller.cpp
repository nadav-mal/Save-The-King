#include "Controller.h"

/* Constructor of the controller. */
Controller::Controller()
    : m_win(true), m_pause(false), m_helpMode(false)
{
    this->initVars();
    this->loadLevelsBG(); // Loads the backgrounds for the levels.
    this->loadLevelUpandWinGame(); // Loads the sprites of the level-up and game win.
    this->initButtons(); // Loads the sprites of the buttons.
}

/* Main function of the program. 
 * The function runs the menu (by making it run itself) and the game. */
void Controller::run()
{
    this->loadMenu(); // Loads the menu.
    m_clock.restart(); // Restarts the clock before starting.
    this->getNext(); // First level seperately.
    this->initTimeSet(); // Sets the time display.

    // Repositions the "help mode" display positions.
    this->m_menu.setHelpAndExitPos(sf::Vector2f((gameWidth - menuWidth) / 2, (gameHeight - menuHeight) / 2), 
                                   sf::Vector2f(((gameWidth - menuWidth) / 2) + buttonWidth, ((gameHeight - menuHeight) / 2) + buttonHeight));

    /* Game loop. */
    while (m_window->isOpen())
    {
        /* If won level (perhaps the last level). */
        if (this->m_win)
            this->winLevel();

        /* Updates the state of the game.. */
        update();

        /* Renders. */
        render();

        /* Erases what needs to be removed (elves or unmovables). */
        erase();
    }
}

/* This function is in charge of loading the menu of the game. */
void Controller::loadMenu()
{
    this->m_sound.playMusic("menuMusic.ogg"); // Menu bg music.
    this->m_menu.runMenu(this->m_sound); // Menu loop activation.
    this->m_sound.stopMusic(); // Stops the bg music after the loop.
}

/* This function is in charge of updating the current game state. */
void Controller::update()
{
    this->pollEvents(); // Handles new events.
    const sf::Time deltaTime = m_clock.restart(); // deltaTime saves time passed.

    if (!this->m_pause && !this->m_helpMode) // If we're not in pause or help mode.
    {
        this->updateTime(deltaTime);
        this->moveCurrent(deltaTime); // Moves currently played character.
        std::srand((unsigned)std::time(NULL)); // Polls a set of random numbers.
        this->moveElves(deltaTime); // Moves the elves randomly.
    }
}

/* This function is in charge of handling events. */
void Controller::pollEvents()
{
    /* Events loop. */
    while (this->m_window->pollEvent(this->m_event))
    {
        switch (this->m_event.type)
        {
        /* In case the game was closed. */
        case sf::Event::Closed:
            this->m_window->close();
            break;

        /* In case the user pressed a key. */
        case sf::Event::KeyPressed:
            if (this->m_event.key.code == sf::Keyboard::Escape) // If escape key then close.
                this->m_window->close();

            if (!this->m_pause && !this->m_helpMode) // If we're not in pause or help mode then respond to the keyboard.
                this->handleKeyPressed();
            break;

        /* In case the user clicked on the window. */
        case sf::Event::MouseButtonReleased:
            // Sends the location of the click.
            handleClick(m_window->mapPixelToCoords({ this->m_event.mouseButton.x, this->m_event.mouseButton.y }));
            break;

        /* In case the user moved the mouse. */
        case sf::Event::MouseMoved:
        {
            sf::Vector2i mouse_loc = sf::Mouse::getPosition(*this->m_window); // Stores the current position of the mouse.
            highlightButton(mouse_loc); // Highlights buttons if hovered on with the mouse.
            break;
        }

        default:
            // In any case, we want to set the direction of the currently played character.
            m_board.getCharacters()[m_board.getCurrChar()]->setDirection(sf::Keyboard::Unknown);
            break;
        }
    }
}

/* This function is in charge of  */
void Controller::moveElves(const sf::Time deltaTime)
{
    auto size = this->m_board.getBoardSize();
    // fixedPos is the start position (top left corner) of the game board.
    auto fixedPos = sf::Vector2u((gameWidth - (size.x * BLOCK_SIZE)) / 2, (gameHeight - (size.y * BLOCK_SIZE)) / 2);

    // Loops through the vector of the elves and moves them.
    for (auto& elf : m_board.getElves())
    {
        // The elves move themselves.
        elf->move(deltaTime, fixedPos, sf::Vector2u(this->m_video.width, this->m_video.height));

        // Checks the collisions of the elf with the unmovables.
        for (auto& unmovable : m_board.getUnmovables())
            if (elf->collidesWith(*unmovable))
                unmovable->handleCollision(*elf);

        // Checks the collisions of the elf with the players.
        for (auto& player : m_board.getCharacters())
            if (elf->collidesWith(*player))
            {
                player->handleCollision(*elf);
                elf->handleCollision(*player);
            }
    }
}

/* This function is in charge of moving the currently played character. */
void Controller::moveCurrent(const sf::Time deltaTime)
{
    int index = m_board.getCurrChar(); // Takes the index of the curr character.
    auto size = this->m_board.getBoardSize();
    // fixedPos is the start position (top left corner) of the game board.
    auto fixedPos = sf::Vector2u((gameWidth - (size.x * BLOCK_SIZE)) / 2, (gameHeight - (size.y * BLOCK_SIZE)) / 2);
    // The player moves itself.
    m_board.getCharacters()[index]->move(deltaTime, fixedPos, sf::Vector2u(this->m_video.width, this->m_video.height));

    /* Handling collisions */
    playerCollision();
    unmovableCollision();
    elfCollision();

    // Sets the indicator of the currently played character location to the location the character moved to.
    this->m_board.setArrow();
}

/* This function is in charge of handling the user's clicks on the buttons of the game. */
void Controller::handleClick(sf::Vector2f pos)
{
    /* Loops through the buttons. */
    for (int i = 0; i < this->m_usedButtonsSprites.size(); i++)
    {
        // Asks if the click was on the 'i' button.
        if (this->m_usedButtonsSprites[i].getGlobalBounds().contains(pos))
        {
            this->m_sound.playSound(clickSound); // Plays the clicking sound.

            // Asks which button is the 'i' button.
            switch ((GameButtons_t)i)
            {
                case pauseButton:
                    this->m_pause = true;
                break;

                case resumeButton:
                    this->m_pause = false;
                break;

                case restartButton:
                    this->restartLevel();
                break;

                case volUpButton:
                    this->m_sound.incVolume();
                break;

                case volDownButton:
                    this->m_sound.decVolume();
                break;

                case volMuteButton:
                    this->m_sound.muteVolume();
                break;

                case logoutButton:
                    exit(EXIT_SUCCESS);

                case helpInGame:
                    if (!this->m_helpMode)
                        this->m_helpMode = true; // On
                    break;

            default: break;
            }
        }
    }

    /* In case the user exited the help. */
    if (this->m_helpMode && this->m_menu.getMenuSprite(exitHelp).getGlobalBounds().contains(pos))
    {
        this->m_sound.playSound(clickSound);
        this->m_helpMode = false; // Off
    }
}

/* This function is in charge of handling the keyboard key pressed by the user. */
void Controller::handleKeyPressed()
{
    // Sets the direction of the character.
    m_board.getCharacters()[m_board.getCurrChar()]->setDirection(this->m_event.key.code);
 
    // Switch player (character).
    if (this->m_event.key.code == sf::Keyboard::P)
    {
        this->m_sound.playSound(switchPlayerSound);
        m_board.updateCharacter();
    }

    // Mute sounds and music.
    if (this->m_event.key.code == sf::Keyboard::M)
        this->m_sound.muteVolume();
}

/* This function is in charge of handling the teleporting of players. */
bool Controller::handleTeleport(sf::Vector2f pos)
{
    vector<sf::Vector2f> portals = this->m_board.getPortalLocations(); // Receives the portals' locations.
    int index = m_board.getCurrChar(); // Receives the index of the currently played character.
    sf::Vector2f newPos;

    // Loops through the portals.
    for (size_t i = 0; i < portals.size(); i++)
        if (portals[i] == pos) // Finds the right one.
        {
            if (i % 2 == 0)
                newPos = portals[i + 1];
            else
                newPos = portals[i - 1];

            newPos.x += teleportGap; // We don't want to spawn right on top of the other teleport.

            if (this->m_board.checkCanTeleport(newPos)) // Can teleport.
            {
                m_board.getCharacters()[index]->setPosition(newPos);
                m_board.getCharacters()[index]->setPrevPosition(newPos);
            }
            else // Can't teleport (the teleport is blocked).
            {
                m_board.getCharacters()[index]->setPosition(m_board.getCharacters()[index]->getPrevPosition());
                return false;
            }

            break;
        }

    return true; // If we can teleport we reached here.
}

/* This function is in charge of managing the win of a level. */
void Controller::winLevel()
{
    sf::Time timer = cooldown; // Sets a timer to display the banner (win level or win game).
    this->m_clock.restart();

    if (this->m_board.getCurrLevel() < this->m_board.getNumofLevels() - 1)  // Minus the last level.
    {
        this->m_sound.playSound(winLevelSound);
        this->m_window->draw(this->m_levelUpBanner);
    }
    else // Won game.
    {
        this->m_sound.playSound(winGameSound);
        this->m_window->draw(this->m_winGameBanner);
    }

    // Displays the window with the banner.
    this->m_window->display();

    // Timer loop.
    while (timer.asSeconds() > endTime)
        timer -= m_clock.restart();

    this->getNext(); // Loads next level.
}

/* This function is in charge of updating the time. */
void Controller::updateTime(const sf::Time deltaTime)
{
    char timeInChars[50] = { 0 }; // Buffer.

    if (this->m_board.isTimeLim()) // If there's a time limit.
        this->m_time -= deltaTime;
    else
        this->m_time += deltaTime;

    // If the time's not up.
    if (this->m_time.asSeconds() > endTime)
    {
        if (this->m_time.asSeconds() <= 10 && this->m_board.isTimeLim()) // Last 10 seconds warning.
        {
            this->m_timeText.setFillColor(sf::Color::Red);
            this->m_timeText.setOutlineColor(sf::Color::White);
            this->m_timeText.setOutlineThickness(2);
            this->m_timeBG.setOutlineColor(sf::Color::Red);
        }

        _itoa((int)this->m_time.asSeconds(), timeInChars, 10);
        this->m_timeText.setString(timeInChars);
    }
    else
        this->restartLevel(); // Restarts the level if time's up.
}

/* This function is in charge of handling the area which the game is played on. */
void Controller::handleGameBoard()
{
    auto size = this->m_board.getBoardSize();

    auto fixedPos = sf::Vector2f((gameWidth - (size.x * BLOCK_SIZE)) / 2, (gameHeight - (size.y * BLOCK_SIZE)) / 2);
    this->m_board.setBoardframe(sf::Vector2f(this->m_video.width, this->m_video.height), fixedPos);
}

/* This function decreases the current level number because getNext() increases it. */
void Controller::restartLevel()
{
    this->m_board.setCurrLevel(this->m_board.getCurrLevel() - 1);
    this->getNext();
}

/* This function is in charge of updating the bottom right corner of the game board. */
void Controller::updateVideo()
{
    auto size = this->m_board.getBoardSize();
    // fixedPos is the start position (top left corner) of the game board.
    auto fixedPos = sf::Vector2f((gameWidth - (size.x * BLOCK_SIZE)) / 2, (gameHeight - (size.y * BLOCK_SIZE)) / 2);

    // Updates the bottom right corner.
    this->m_video.height = gameHeight - fixedPos.y;
    this->m_video.width = gameWidth - fixedPos.x;
}

/* This function is in charge of displaying the game. */
void Controller::render()
{
    this->m_window->clear(sf::Color{ 0x373737FF });

    /* Background of the level and background of the game board. */
    unsigned int currBG = (this->m_board.getCurrLevel() - 1) % numofLevelsBG;
    this->m_window->draw(this->m_levelsBGSprites[currBG]);
    this->m_window->draw(this->m_board.getBoardFrame());

    /* Objects. */
    m_board.drawElves(*this->m_window);
    m_board.drawUnmovables(*this->m_window);
    m_board.drawCharacters(*this->m_window);

    /* Buttons. */
    this->m_window->draw(this->m_buttonBar);
    this->drawButtons();

    /* Timer. */
    this->m_window->draw(this->m_timeBG);
    this->m_window->draw(this->m_timeText);

    this->m_board.drawArrow(*this->m_window); // Currently played character indicator.

    /* Help mode drawings. */
    if (this->m_helpMode)
    {
        this->m_window->draw(this->m_menu.getMenuSprite(helpDisplay));

        if(this->m_helpExitHover)
            this->m_window->draw(this->m_menu.getMenuSprite(exitHelpHL));
        else
            this->m_window->draw(this->m_menu.getMenuSprite(exitHelp));
    }

    this->m_window->display();
}

/* This function is in charge of drawing the game buttons. */
void Controller::drawButtons()
{
    for (auto& button : this->m_usedButtonsSprites)
        this->m_window->draw(button);
}

/* This function is in charge of handling collisions of currently played player with other players. */
void Controller::playerCollision()
{
    int index = m_board.getCurrChar();

    // Loops through the players.
    for (auto& player : m_board.getCharacters())
        if (m_board.getCharacters()[index]->collidesWith(*player))
        {
            m_board.getCharacters()[index]->handleCollision(*player);
            player->handleCollision(*m_board.getCharacters()[index]);
        }
}

/* This function is in charge of handling collisions of currently played player with elve. */
void Controller::elfCollision()
{
    int index = m_board.getCurrChar();

    // Loops through the elves.
    for (auto& elf : m_board.getElves())
        if (m_board.getCharacters()[index]->collidesWith(*elf))
            m_board.getCharacters()[index]->handleCollision(*elf);
}

/* This function is in charge of hadling collisions of currently played player with unmovables. */
void Controller::unmovableCollision()
{
    auto index = m_board.getCurrChar();

    // Loops through the unmovables.
    for (auto& unmovable : m_board.getUnmovables())
        if (m_board.getCharacters()[index]->collidesWith(*unmovable))
        {
            m_board.getCharacters()[index]->handleCollision(*unmovable);

            // For dynamic casting.
            this->handleSounds(unmovable.get());
        }
}

/* This function is in charge of loading the backgrounds of the levels. */
void Controller::loadLevelsBG()
{
    for (int i = 0; i < numofLevelsBG; i++)
    {
        sf::Sprite tempSprite;
        tempSprite.setTexture(*Textures::instance().getLevelBGTexture((LevelsBG_t)i));
        this->m_levelsBGSprites.push_back(tempSprite);
    }
}

/* This function is in charge of positioning the buttons on the window. */
void Controller::loadButtons()
{
    auto size = this->m_board.getBoardSize();

    for (int i = 0; i < numofButtons ; i++)
    {
        // The currently used sprites.
        if ((float)i < (float)numofButtons / 2)
        {
            /* Calculations to position in the right place, one after another with a small gap. */
            this->m_buttonsSprites[i].setPosition(sf::Vector2f((gameWidth - (BLOCK_SIZE + GAP) * numofUsedButtons) / 2 + (i * (BLOCK_SIZE + GAP)), this->m_video.height + heightGap));
            this->m_usedButtonsSprites[i].setPosition(sf::Vector2f((gameWidth - (BLOCK_SIZE + GAP) * numofUsedButtons) / 2 + (i * (BLOCK_SIZE + GAP)), this->m_video.height + heightGap));
        }
        // The highlights.
        else
            this->m_buttonsSprites[i].setPosition(sf::Vector2f((gameWidth - (BLOCK_SIZE + GAP) * numofUsedButtons) / 2 + ((i - numofUsedButtons) * (BLOCK_SIZE + GAP)), this->m_video.height + heightGap));
    }
    
    // The buttons background bar.
    m_buttonBar.setPosition(sf::Vector2f(m_usedButtonsSprites[0].getPosition().x - ((buttonBarWidth - (BLOCK_SIZE + GAP) * numofUsedButtons) / 2), m_usedButtonsSprites[0].getPosition().y - ((buttonBarHeight - BLOCK_SIZE) / 2) + (heightGap / 3)));
}

/* This function is in charge of getting the next level. */
void Controller::getNext()
{
    // If you can't get another level you've probably won.
    if (!this->m_board.loadLevel())
    {
        std::cout << "You win!\n";
        this->m_sound.stopMusic();
        exit(EXIT_SUCCESS);
    }
    
    this->updateVideo(); // Updates the bottom right corner of the game board.
    this->m_board.adjustObjects(); // Adjusts the objects' locations.

    if(!this->m_window) // Initiates the window if needed.
        this->initWindow();

    // Updates between levels.
    this->updateThemeMusic();
    this->loadButtons();
    this->initTimeSet();
    this->handleGameBoard();
    this->resetWinCon();
}

/* Resets win con. */
void Controller::resetWinCon()
{
    this->m_win = false;   
}

/* This function is in charge of erasing the objects which were set to be erased. */
void Controller::erase()
{
    // Unmovables.
    std::erase_if(m_board.getUnmovables(), [](auto& unmovable)
        {
            return unmovable->isDisposed();
        });

    // Elves.
    std::erase_if(m_board.getElves(), [](auto& elf)
        {
            return elf->isDisposed();
        });
}

// Initiates window to nullptr.
void Controller::initVars()
{
    this->m_window = nullptr;
}

/* Initiates the game window. */
void Controller::initWindow()
{
    this->m_video.height = gameHeight;
    this->m_video.width = gameWidth;
    this->m_window = new sf::RenderWindow(this->m_video, GAME_NAME, sf::Style::Fullscreen);
    this->updateVideo();
}

/* This function is in charge of initiating the time display. */
void Controller::initTimeSet()
{
    // Time text visuals.
    this->m_time = sf::seconds(m_board.getTime());
    this->m_timeFont.loadFromFile("digital.ttf");
    this->m_timeText.setFont(this->m_timeFont);
    this->m_timeText.setCharacterSize(50);
    this->m_timeText.setFillColor(sf::Color::White);
    this->m_timeText.setOutlineThickness(0);

    // Time text location.
    auto size = this->m_board.getBoardSize();
    auto pos = sf::Vector2f(this->m_video.width - BLOCK_SIZE, (gameHeight - (size.y * BLOCK_SIZE)) / 2 - BLOCK_SIZE);
    this->setTimeBG(pos);
    pos = sf::Vector2f(this->m_video.width - BLOCK_SIZE, (gameHeight - (size.y * BLOCK_SIZE)) / 2 - BLOCK_SIZE - GAP);
    this->m_timeText.setPosition(pos);
}

/* This function is in charge of initiating the game buttons' textures. */
void Controller::initButtons()
{
    auto size = this->m_board.getBoardSize();

    // Loops through the buttons.
    for (int i = 0; i < numofButtons; i++)
    {
        sf::Sprite tempSprite;
        tempSprite.setTexture(*Textures::instance().getGameButtonTexture((GameButtons_t)i));

        // Currently used.
        if ((float)i < (float)numofButtons / 2)
        {
            this->m_reHoveredButton.push_back(false);
            this->m_usedButtonsSprites.push_back(tempSprite);
        }

        // In general use.
        this->m_buttonsSprites.push_back(tempSprite);
    }

    this->m_buttonBar.setTexture(*Textures::instance().getGameButtonTexture((GameButtons_t)buttonsBar));
}

/* This function is in charge of highlighting a button which is hovered on. */
void Controller::highlightButton(sf::Vector2i loc)
{
    // Loops through used buttons.
    for (int i = 0; i < this->m_usedButtonsSprites.size(); i++)
    {
        // Asks if one of the used buttons' bounds contains the mouse location.
        if (this->m_usedButtonsSprites[i].getGlobalBounds().contains((sf::Vector2f)loc))
        {
            // Asks if we're not in help mode.
            if (!this->m_helpMode)
            {
                // Finds which button is the right one and turns it's "hovered" boolean to true.
                if ((GameButtons_t)i == resumeButton)
                {
                    if (!this->m_reHoveredButton[resumeButton])
                    {
                        this->m_reHoveredButton[resumeButton] = true;
                        this->m_usedButtonsSprites[i] = this->m_buttonsSprites[resumeButtonHL];
                        this->m_sound.playSound(hoverSound);
                    }
                }

                if ((GameButtons_t)i == pauseButton)
                {
                    if (!this->m_reHoveredButton[pauseButton])
                    {
                        this->m_reHoveredButton[pauseButton] = true;
                        this->m_usedButtonsSprites[i] = this->m_buttonsSprites[pauseButtonHL];
                        this->m_sound.playSound(hoverSound);
                    }
                }

                if ((GameButtons_t)i == restartButton)
                {
                    if (!this->m_reHoveredButton[restartButton])
                    {
                        this->m_reHoveredButton[restartButton] = true;
                        this->m_usedButtonsSprites[i] = this->m_buttonsSprites[restartButtonHL];
                        this->m_sound.playSound(hoverSound);
                    }
                }

                if ((GameButtons_t)i == volUpButton)
                {
                    if (!this->m_reHoveredButton[volUpButton])
                    {
                        this->m_reHoveredButton[volUpButton] = true;
                        this->m_usedButtonsSprites[i] = this->m_buttonsSprites[volUpButtonHL];
                        this->m_sound.playSound(hoverSound);
                    }
                }

                if ((GameButtons_t)i == volDownButton)
                {
                    if (!this->m_reHoveredButton[volDownButton])
                    {
                        this->m_reHoveredButton[volDownButton] = true;
                        this->m_usedButtonsSprites[i] = this->m_buttonsSprites[volDownButtonHL];
                        this->m_sound.playSound(hoverSound);
                    }
                }

                if ((GameButtons_t)i == volMuteButton)
                {
                    if (!this->m_reHoveredButton[volMuteButton])
                    {
                        this->m_reHoveredButton[volMuteButton] = true;
                        this->m_usedButtonsSprites[i] = this->m_buttonsSprites[volMuteButtonHL];
                        this->m_sound.playSound(hoverSound);
                    }
                }

                if ((GameButtons_t)i == logoutButton)
                {
                    if (!this->m_reHoveredButton[logoutButton])
                    {
                        this->m_reHoveredButton[logoutButton] = true;
                        this->m_usedButtonsSprites[i] = this->m_buttonsSprites[logoutButtonHL];
                        this->m_sound.playSound(hoverSound);
                    }
                }

                if ((GameButtons_t)i == helpInGame)
                {
                    if (!this->m_reHoveredButton[helpInGame])
                    {
                        this->m_reHoveredButton[helpInGame] = true;
                        this->m_usedButtonsSprites[i] = this->m_buttonsSprites[helpInGameHL];
                        this->m_sound.playSound(hoverSound);
                    }
                }
            }
        }
        // Sets the rest to false and default sprite.
        else
        {
            if ((GameButtons_t)i == resumeButton)
            {
                this->m_usedButtonsSprites[i] = this->m_buttonsSprites[resumeButton];
                this->m_reHoveredButton[resumeButton] = false;
            }

            if ((GameButtons_t)i == pauseButton)
            {
                this->m_usedButtonsSprites[i] = this->m_buttonsSprites[pauseButton];
                this->m_reHoveredButton[pauseButton] = false;
            }

            if ((GameButtons_t)i == restartButton)
            {
                this->m_usedButtonsSprites[i] = this->m_buttonsSprites[restartButton];
                this->m_reHoveredButton[restartButton] = false;
            }

            if ((GameButtons_t)i == volUpButton)
            {
                this->m_usedButtonsSprites[i] = this->m_buttonsSprites[volUpButton];
                this->m_reHoveredButton[volUpButton] = false;
            }

            if ((GameButtons_t)i == volDownButton)
            {
                this->m_usedButtonsSprites[i] = this->m_buttonsSprites[volDownButton];
                this->m_reHoveredButton[volDownButton] = false;
            }

            if ((GameButtons_t)i == volMuteButton)
            {
                this->m_usedButtonsSprites[i] = this->m_buttonsSprites[volMuteButton];
                this->m_reHoveredButton[volMuteButton] = false;
            }

            if ((GameButtons_t)i == logoutButton)
            {
                this->m_usedButtonsSprites[i] = this->m_buttonsSprites[logoutButton];
                this->m_reHoveredButton[logoutButton] = false;
            }

            if ((GameButtons_t)i == helpInGame && !this->m_helpMode)
            {
                this->m_usedButtonsSprites[i] = this->m_buttonsSprites[helpInGame];
                this->m_reHoveredButton[helpInGame] = false;
            }
        }
    }

    /* Help exit button in game hover. */
    if (this->m_helpMode && this->m_menu.getMenuSprite(exitHelp).getGlobalBounds().contains((sf::Vector2f)loc))
    {
        this->m_helpExitHover = true;
        this->m_sound.playSound(hoverSound);
    }
    else
        this->m_helpExitHover = false;
}

/* This function is in charge of updating the background music of the level. */
void Controller::updateThemeMusic()
{
    switch ((this->m_board.getCurrLevel() % 3) + 1)
    {
    case firstTheme:
        this->m_sound.stopMusic();
        this->m_sound.playMusic("firstLevelMusic.ogg");
        break;

    case secondTheme:
        this->m_sound.stopMusic();
        this->m_sound.playMusic("secondLevelMusic.ogg");
        break;

    case thirdTheme:
        this->m_sound.stopMusic();
        this->m_sound.playMusic("thirdLevelMusic.ogg");
        break;

    default: break;
    }
}

/* This function is in charge of handling the sounds of the game. */
void Controller::handleSounds(GameObject* object)
{
    auto index = m_board.getCurrChar();

    /*---------------------- Dynamic cast -----------------------*/
    /* Player encountered a time gift. */
    if (TimeGift* timegift = dynamic_cast<TimeGift*>(object))
    {
        this->m_sound.playSound(collectGiftSound);
        this->m_time += sf::seconds(timegift->getTime());
    }

    /* Player encountered an elf gift. */
    if (ElfGift* elfgift = dynamic_cast<ElfGift*>(object))
    {
        this->m_sound.playSound(killElvesSound);
        this->m_board.eliminateElves();
    }

    /* Thief encountered a key. */
    if (Key* key = dynamic_cast<Key*>(object))
    {
        if (key->isDisposed())
            this->m_sound.playSound(keyLoot);
    }

    /* Thief encountered a gate. */
    if (Gate* gate = dynamic_cast<Gate*>(object))
    {
        if (gate->isDisposed())
            this->m_sound.playSound(gateOpen);
        else
            this->m_sound.playSound(bumpIntoWall);
    }
    /*-----------------------------------------------------------*/

    /*---------------------- RTTI -----------------------*/
    if (typeid(Orc) == typeid(*object))
    {
        /* Warrior encountered an orc. */
        if (typeid(Warrior) == typeid(*m_board.getCharacters()[index]))
        {
            m_board.createUnmovableObject(keyC, object->getPosition());

            this->m_sound.playSound(orcDie);
            this->m_sound.playSound(keyDrop);
        }
        else
            this->m_sound.playSound(bumpIntoWall);
    }

    if (typeid(Portal) == typeid(*object))
    {
        /* Anyone encountered a portal except a mage. */
        if (typeid(Mage) != typeid(m_board.getCharacters()[index]))
        {
            sf::Vector2f pos = object->getPosition();

            if (this->handleTeleport(pos))
                this->m_sound.playSound(tpSound);
            else
                this->m_sound.playSound(bumpIntoWall);
        }
    }

    if (typeid(Throne) == typeid(*object))
    {
        /* King encountered the throne - Won level. */
        if (typeid(King) == typeid(*m_board.getCharacters()[index]))
            this->m_win = true;
        else
            this->m_sound.playSound(bumpIntoWall);
    }

    /* Player encountered a wall. */
    if (typeid(Wall) == typeid(*object))
        this->m_sound.playSound(bumpIntoWall);

    if (typeid(Fire) == typeid(*object))
    {
        /* Mage encountered fire. */
        if (typeid(Mage) == typeid(*m_board.getCharacters()[index]))
            this->m_sound.playSound(killFire);
        else
            this->m_sound.playSound(fireTouch);
    }
    /*---------------------------------------------------*/
}

/* This function is in charge of setting the time text background visuals and position. */
void Controller::setTimeBG(sf::Vector2f pos)
{
    this->m_timeBG.setFillColor(sf::Color::Black);
    this->m_timeBG.setOutlineColor(sf::Color::White);
    this->m_timeBG.setOutlineThickness(2);
    this->m_timeBG.setSize(sf::Vector2f(80, 70));
    this->m_timeBG.setPosition(sf::Vector2f(pos.x - 27, pos.y - 12));
}

/* This function is in charge of loading the textures and setting the positions of the win level/game banners. */
void Controller::loadLevelUpandWinGame()
{
    this->m_levelUpBanner.setTexture(*Textures::instance().getLevelUpBannerTexture());
    this->m_levelUpBanner.setPosition(sf::Vector2f((gameWidth - lvUpWidth) / 2, (gameHeight - lvUpHeight) / 2));

    this->m_winGameBanner.setTexture(*Textures::instance().getWinGameBannerTexture());
    this->m_winGameBanner.setPosition(sf::Vector2f((gameWidth - winGameBannerWidth) / 2, (gameHeight - winGameBannerHeight) / 2));
}
