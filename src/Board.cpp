#include "Board.h"

// Constructor of the board.
Board::Board()
    : m_currentLevel(0), m_currentCharacter(0), m_boardSize(0, 0), m_timeLimit(0)
{
    this->m_levelFileNames.push_back("Levels.txt"); // "Levels.txt" needs to contain the names of the levels.
    loadFileNames();
    this->m_playerArrow.setTexture(*Textures::instance().getPlayerArrowTexture());
}

/* This function is in charge of reseting the board data. */
void Board::resetBoard()
{
    // Clears vectors.
    m_characters.clear();
    m_elves.clear();
    m_unmovables.clear();

    m_currentCharacter = 0;
}

/* This function is in charge of loading the names of the files of the levels. */
void Board::loadFileNames()
{
    std::ifstream file;
    this->openFile(file);
    char c;
    string name;

    // Reads from file.
    while (file.get(c))
    {
        name.clear();

        while (c != '\n' && !file.eof())
        {
            name += c;
            file.get(c);
        }

        m_levelFileNames.push_back(name);
    }

    // Closes file in the end.
    file.close();
}

/* This function is in charge of adjusting the objects' locations to the game board area. */
void Board::adjustObjects()
{
    /* fixedPos is the top left corner of the game board. */
    auto fixedPos = sf::Vector2u((gameWidth - (m_boardSize.x * BLOCK_SIZE)) / 2, (gameHeight - (m_boardSize.y * BLOCK_SIZE)) / 2);

    // Positions players.
    for (auto& character : this->m_characters)
    {
        auto charPos = character->getPosition();
        character->setPosition(sf::Vector2f(charPos.x + fixedPos.x, charPos.y + fixedPos.y));
        character->setPrevPosition(sf::Vector2f(charPos.x + fixedPos.x, charPos.y + fixedPos.y));
    }

    // Positions elves.
    for (auto& elf : this->m_elves)
    {
        auto elfPos = elf->getPosition();
        elf->setPosition(sf::Vector2f(elfPos.x + fixedPos.x, elfPos.y + fixedPos.y));
        elf->setPrevPosition(sf::Vector2f(elfPos.x + fixedPos.x, elfPos.y + fixedPos.y));
    }

    // Positions unmovables.
    for (auto& unmovable : this->m_unmovables)
    {
        auto unmovablePos = unmovable->getPosition();
        unmovable->setPosition(sf::Vector2f(unmovablePos.x + fixedPos.x, unmovablePos.y + fixedPos.y));

        // Stores the portals' locations.
        if (typeid(Portal) == typeid(*unmovable))
            m_portalsLocs.push_back(unmovable->getPosition());
    }
}

/* This function is in charge of setting the game board frame. */
void Board::setBoardframe(sf::Vector2f posBgn, sf::Vector2f posEnd)
{
    this->m_boardFrame.setPosition(posBgn);
    this->m_boardFrame.setSize(sf::Vector2f(posEnd.x - posBgn.x, posEnd.y - posBgn.y));
    this->m_boardFrame.setOutlineColor(sf::Color::Black);
    this->m_boardFrame.setOutlineThickness(2);

    // For fun and more visuals.
    if(this->m_currentLevel % 2 == 0)
        this->m_boardFrame.setFillColor(sf::Color(37, 37, 37, 170));
    else
        this->m_boardFrame.setFillColor(sf::Color(150, 150, 150, 170));
}

/* This function is in charge of setting the number of the current level. */
void Board::setCurrLevel(int level)
{
    this->m_currentLevel = level;
}

/* This function is in charge of setting the arrow which is the indicator of the currently played player. */
void Board::setArrow()
{
    sf::Vector2f playerPos = this->m_characters[this->m_currentCharacter]->getPosition();
    sf::Vector2f fixedPos = sf::Vector2f(PLAYER_SIZE / 2, this->m_playerArrow.getGlobalBounds().height + teleportGap);
    this->m_playerArrow.setPosition(sf::Vector2f(playerPos.x + fixedPos.x, playerPos.y - fixedPos.y));
}

/* This function is in charge of "eliminating" the elves (disposes elves). */
void Board::eliminateElves()
{
    for (auto& elf : this->m_elves)
        elf->setDisposal(true);
}

/* This function is in charge of loading a level from a file. */
bool Board::loadLevel()
{
    if (m_levelFileNames.size() - 1 > m_currentLevel)
        m_currentLevel++;
    else return false; // If no more levels.

    resetBoard();

    /* Handle file. */
    std::ifstream file;
    openFile(file); // Knows which level to open by m_currentLevel.

    char c;
    char timeLim[3] = { 0 };
    int counter = 0;

    file.get(c);

    while (isdigit(c)) // Reads for a time limit.
    {
        timeLim[counter] = c; 
        counter++;
        file.get(c);
    }

    this->m_timeLimit = atoi(timeLim);
    if (m_timeLimit > 0) // If there's a time limit.
        m_timeLim = true;
    else // If there's no time limit.
        m_timeLim = false;

    m_boardSize.y = 0;

    /* Rows. */
    while (file.get(c))
    {
        m_boardSize.x = 0;

        /* Cols. */
        while (c != '\n' && !file.eof())
        {
            sf::Vector2f pos = sf::Vector2f(m_boardSize.x * BLOCK_SIZE, m_boardSize.y * BLOCK_SIZE);

            if(!createMovableObject((Objects)c, pos))
                createUnmovableObject((Objects)c, pos);

            /* Updates the width and reads another char. */
            m_boardSize.x++;
            file.get(c);
        }

        /* Updates the height. */
        m_boardSize.y++;
    }

    /* Closes the file - no further use. */
    file.close();
    return true;
}

/* This function is in charge of checking if the player can teleport to the sent position (pos). */
bool Board::checkCanTeleport(sf::Vector2f& pos)
{    
    sf::Vector2f newPos = sf::Vector2f(pos.x + BLOCK_SIZE, pos.y); // Right of the portal.

    for (auto& unmovable : m_unmovables)
        if (unmovable->getGlobalBounds().contains(newPos))
            return false;

    for (auto& elf : m_elves)
        if (elf->getGlobalBounds().contains(newPos))
            return false;
    
    for (auto& character : m_characters)
        if (character->getGlobalBounds().contains(newPos))
            return false;

    pos = newPos;
    return true; // Can portal there.
}

/* This function is in charge of opening a file stream. */
void Board::openFile(std::ifstream& file)
{
    /* Open file. */
    string nameofFile = this->m_levelFileNames[m_currentLevel];
    file.open(nameofFile);

    if (file.fail())
    {
        std::cout << "Can't open file.\n";
        exit(EXIT_FAILURE);
    }
}

/* This function is in charge of creating a movable object with the make_unique method, 
 * and then inserting it to the right vector using a unique_ptr. */
bool Board::createMovableObject(Objects type, sf::Vector2f pos)
{
    switch (type)
    {
    case kingC:
    {
        m_currentCharacter = (int)m_characters.size();
        m_characters.push_back(std::make_unique<King>(pos, king));
        this->setArrow();
        return true;
    }
    case thiefC:
        m_characters.push_back(std::make_unique<Thief>(pos, thief));
        return true;

    case mageC:
        m_characters.push_back(std::make_unique<Mage>(pos, mage));
        return true;

    case warriorC:
        m_characters.push_back(std::make_unique<Warrior>(pos, warrior));
        return true;

    case elfC:
        m_elves.push_back(std::make_unique<Elf>(pos, elf));
        return true;

    default: return false;
    }
}

/* This function is in charge of creating an unmovable object with the make_unique method,
 * and then inserting it to the right vector using a unique_ptr. */
void Board::createUnmovableObject(Objects type, sf::Vector2f pos)
{
    switch (type)
    {
    case wallC:
        m_unmovables.push_back(std::make_unique<Wall>(pos, wall));
        break;

    case fireC:
        m_unmovables.push_back(std::make_unique<Fire>(pos, fire));
        break;

    case keyC:
        m_unmovables.push_back(std::make_unique<Key>(pos, key));
        break;

    case orcC:
        m_unmovables.push_back(std::make_unique<Orc>(pos, orc));
        break;

    case gateC:
        m_unmovables.push_back(std::make_unique<Gate>(pos, gate));
        break;

    case throneC:
        m_unmovables.push_back(std::make_unique<Throne>(pos, throne));
        break;

    case portalC:
        m_unmovables.push_back(std::make_unique<Portal>(pos, portal));
        break;

    case timeGiftC:
        m_unmovables.push_back(std::make_unique<TimeGift>(pos, timeGift));
        break;

    case elfGiftC:
        m_unmovables.push_back(std::make_unique<ElfGift>(pos, elfGift));
        break;

    default: break;
    }
}

/* Returns the vector of the players. */
vector<unique_ptr<MovableObject>>& Board::getCharacters()
{
    return m_characters;
}

/* Returns the vector of the elves. */
vector<unique_ptr<Elf>>& Board::getElves()
{
    return m_elves;
}

/* Returns the vector of the unmovables. */
vector<unique_ptr<UnmovableObject>>& Board::getUnmovables()
{
    return m_unmovables;
}

/* Returns the vector of the portals' locations. */
vector<sf::Vector2f>& Board::getPortalLocations()
{
    return m_portalsLocs;
}

/* Returns the time limit. */
int Board::getTime() const
{
    return m_timeLimit;
}

/* Returns the index of the current player played. */
int Board::getCurrChar() const
{
    return m_currentCharacter;
}

/* Returns the index of the current level. */
int Board::getCurrLevel() const
{
    return this->m_currentLevel;
}

/* Returns the total number of levels. */
int Board::getNumofLevels() const
{
    return this->m_levelFileNames.size();
}

/* Returns the game board size. */
sf::Vector2u Board::getBoardSize() const
{
    return m_boardSize;
}

/* Returns the game board's rectangle. */
sf::RectangleShape Board::getBoardFrame() const
{
    return this->m_boardFrame;
}

/* Returns if there's a time limit. */
bool Board::isTimeLim()
{
    return m_timeLim;
}

/* This function is in charge of drawing the characters. */
void Board::drawCharacters(sf::RenderWindow &window)
{
    for (int i = 0; i < m_characters.size(); i++)
        this->m_characters.at(i).get()->drawObject(window);
}

/* This function is in charge of drawing the elves. */
void Board::drawElves(sf::RenderWindow &window)
{
    for (int i = 0; i < m_elves.size(); i++)
        this->m_elves.at(i).get()->drawObject(window);
}

/* This function is in charge of drawing the unmovables. */
void Board::drawUnmovables(sf::RenderWindow &window)
{
    for (int i = 0; i < m_unmovables.size(); i++)
        this->m_unmovables.at(i).get()->drawObject(window);
}

/* This function is in charge of drawing the current player played indicator. */
void Board::drawArrow(sf::RenderWindow& window)
{
    window.draw(this->m_playerArrow);
}

/* Updates the current character played index and sets the arrow to it. */
void Board::updateCharacter()
{
    ++m_currentCharacter %= 4;
    this->setArrow();
}
