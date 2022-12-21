#include "Textures.h"

	//king, thief, mage, warrior, elf, orc, throne, portal,
	//Key, wall, fire, gate
Textures::Textures()
{
	/* Menu loading. */
	loadMenuTexture("background.jpg");
	loadMenuTexture("new.png");
	loadMenuTexture("help.png");
	loadMenuTexture("exit.png");
	loadMenuTexture("exitHelp.png");

	loadMenuTexture("newHL.png");
	loadMenuTexture("helpHL.png");
	loadMenuTexture("exitHL.png");
	loadMenuTexture("exitHelpHL.png");
	loadMenuTexture("helpDisplay.jpg");

	/* Game objects loading. */
	loadObjectTexture("king.png");
	loadObjectTexture("thief.png");
	loadObjectTexture("mage.png");
	loadObjectTexture("warrior.png");
	loadObjectTexture("elf.png");
	loadObjectTexture("orc.png");
	loadObjectTexture("throne.png");
	loadObjectTexture("portal.png");
	loadObjectTexture("Key.png");
	loadObjectTexture("wall.png");
	loadObjectTexture("fire.png");
	loadObjectTexture("gate.png");
	loadObjectTexture("thiefWKey.png");
	loadObjectTexture("timeGift.png");
	loadObjectTexture("killElvesGift.png");

	/* Game levels background loading. */
	loadlevelBGTexture("firstBG.jpg");
	loadlevelBGTexture("secondBG.jpg");
	loadlevelBGTexture("thirdBG.jpg");

	/* Game buttons loading. */
	loadGameButtonTexture("resumeButton.png");
	loadGameButtonTexture("pauseButton.png");
	loadGameButtonTexture("restartButton.png");
	loadGameButtonTexture("volUp.png");
	loadGameButtonTexture("voldown.png");
	loadGameButtonTexture("volMute.png");
	loadGameButtonTexture("logoutButton.png");
	loadGameButtonTexture("helpInGame.png");
	/*Game highlighted buttons loading.*/
	loadGameButtonTexture("resumeButtonHL.png");
	loadGameButtonTexture("pauseButtonHL.png");
	loadGameButtonTexture("restartButtonHL.png");
	loadGameButtonTexture("volUpHL.png");
	loadGameButtonTexture("voldownHL.png");
	loadGameButtonTexture("volMuteHL.png");
	loadGameButtonTexture("logoutButtonHL.png");
	loadGameButtonTexture("helpInGameHL.png");
	loadGameButtonTexture("buttonsBar.png");
	/*Display regarded loadings*/
	loadPlayerArrowTexture("playerArrow.png");
	loadLevelUpBannerTexture("levelUpBanner.png");
	loadWinGameBannerTexture("winGameBanner.png");
}

/*This function returns an object's' texture by a given enum*/
sf::Texture* Textures::getObjectTexture(Objects objEnum)
{
	return &(m_objectsTextures[objEnum]);
}
/*This function returns a menu texture by a given menuEnum*/
sf::Texture* Textures::getMenuTexture(Menu_t menuEnum)
{
	return &(m_menuTextures[menuEnum]);
}
/*This function returns a background texture by a given Background Enum*/
sf::Texture* Textures::getLevelBGTexture(LevelsBG_t bgEnum)
{
	return &(m_levelsBGTextures[bgEnum]);
}
/*This function returns a game button texture by a given button Enum*/
sf::Texture* Textures::getGameButtonTexture(GameButtons_t btnEnum)
{
	return &(m_gameButtonsTextures[btnEnum]);
}
/*This function returns the red arrow texture*/
sf::Texture* Textures::getPlayerArrowTexture()
{
	return &(m_playerArrowTexture);
}
/*This function returns a level up banner*/
sf::Texture* Textures::getLevelUpBannerTexture()
{
	return &(m_levelUpBanner);
}
/*This function returns a win game banner*/
sf::Texture* Textures::getWinGameBannerTexture()
{
	return &(m_winGameBanner);
}

//makes an instance and is created only once
Textures& Textures::instance()
{
	static Textures instance;
	return instance;
}
/*This function recieves an object texture by the given filename*/
void Textures::loadObjectTexture(const std::string fileName)
{
	sf::Texture temp;
	temp.loadFromFile(fileName);
	m_objectsTextures.push_back(temp);
}
/*This function loads a menu texture by the given filename*/
void Textures::loadMenuTexture(const std::string fileName)
{
	sf::Texture temp;
	temp.loadFromFile(fileName);
	m_menuTextures.push_back(temp);
}
/*This function loads a background texture by the given filename*/
void Textures::loadlevelBGTexture(const std::string fileName)
{
	sf::Texture temp;
	temp.loadFromFile(fileName);
	m_levelsBGTextures.push_back(temp);
}
/*This function loads a button texture by the given filename*/
void Textures::loadGameButtonTexture(const std::string fileName)
{
	sf::Texture temp;
	temp.loadFromFile(fileName);
	m_gameButtonsTextures.push_back(temp);
}
/*This function loads an arrow texture by the given filename*/
void Textures::loadPlayerArrowTexture(const std::string fileName)
{
	this->m_playerArrowTexture.loadFromFile(fileName);
}
/*This function loads a level up banner by the given filename*/
void Textures::loadLevelUpBannerTexture(const std::string fileName)
{
	this->m_levelUpBanner.loadFromFile(fileName);
}
/*This function loads a win game banner by the given filename*/
void Textures::loadWinGameBannerTexture(const std::string fileName)
{
	this->m_winGameBanner.loadFromFile(fileName);
}
