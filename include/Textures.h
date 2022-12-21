#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "Macros.h"

/* Textures class is in charge of storing all the textures loaded into the game.
 * The class uses the singleton method in order to avoid loading a certain texture more than once. */
class Textures
{
public:
	/* instance() is used to gain access to the stored textures. */
	static Textures& instance();

	/* Getters of the textures. */
	sf::Texture* getObjectTexture(Objects objEnum); 
	sf::Texture* getMenuTexture(Menu_t menuEnum); 
	sf::Texture* getLevelBGTexture(LevelsBG_t bgEnum); 
	sf::Texture* getGameButtonTexture(GameButtons_t btnEnum);
	sf::Texture* getPlayerArrowTexture(); 
	sf::Texture* getLevelUpBannerTexture();
	sf::Texture* getWinGameBannerTexture();

	/* Loaders of the textures (from a file). */
	void loadObjectTexture(const std::string fileName);
	void loadMenuTexture(const std::string fileName);
	void loadlevelBGTexture(const std::string fileName);
	void loadGameButtonTexture(const std::string fileName);
	void loadPlayerArrowTexture(const std::string fileName);
	void loadLevelUpBannerTexture(const std::string fileName);
	void loadWinGameBannerTexture(const std::string fileName);

private:
	/* Ctor. */
	Textures();

	/* Different vector of textures and sole textures to store all the textures. */
	std::vector<sf::Texture> m_objectsTextures;
	std::vector<sf::Texture> m_menuTextures;
	std::vector<sf::Texture> m_levelsBGTextures;
	std::vector<sf::Texture> m_gameButtonsTextures;
	sf::Texture m_playerArrowTexture;
	sf::Texture m_levelUpBanner;
	sf::Texture m_winGameBanner;
};