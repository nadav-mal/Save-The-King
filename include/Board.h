#pragma once
#include <SFML/Graphics.hpp>
#include <string.h>
#include "GameObject.h"
#include <vector>
#include <fstream>
#include <iostream>
#include <memory>

#include "King.h"
#include "Mage.h"
#include "Thief.h"
#include "Warrior.h"
#include "Elf.h"

using std::string;
using std::vector;
using std::unique_ptr;

/* The Board class is in charge of the game board in which the game occurs. */
class Board
{
public:
	// C-tor.
	Board();

	/* Management. */
	void resetBoard(); // Resets the board's data.
	void loadFileNames(); // Reads the file names of the levels.
	bool loadLevel(); // Loads the current level from a file.
	bool checkCanTeleport(sf::Vector2f& pos); // Used to make sure you can teleport.
	void openFile(std::ifstream &file);
	bool createMovableObject(Objects type, sf::Vector2f pos); // Creates a moveable object.
	void createUnmovableObject(Objects type, sf::Vector2f pos); // Creates an unmovable object.
	void updateCharacter(); // To update currently played character.
	void adjustObjects(); // Used to adjust the object's position on the screen.
	void setBoardframe(sf::Vector2f posBgn, sf::Vector2f posEnd); // Board frame is the area which is played on (displayed with a rectangle shape).
	void setCurrLevel(int level); // For external use.
	void setArrow(); // Sets the arrow which indicates which character is currently played.
	void eliminateElves(); // In case we need to remove the elves from the level.

	/* Getters. */
	vector<unique_ptr<MovableObject>>& getCharacters();  // Access to the vector of the players (characters).
	vector<unique_ptr<Elf>>& getElves();  // Access to the vector of the elves.
	vector<unique_ptr<UnmovableObject>>& getUnmovables();  // Access to the vector of the unmovable objects.
	vector<sf::Vector2f>& getPortalLocations(); // Access to the locations of the portals.
	int getTime() const; // Access to the time limit (or no time limit if the time in the file is 0 or not specified).
	int getCurrChar() const; // Current player which is played.
	int getCurrLevel() const; // Current level number.
	int getNumofLevels() const; // Total number of levels.
	sf::Vector2u getBoardSize() const; // Game board size (area in which the game occurs).
	sf::RectangleShape getBoardFrame() const; // Rectangle of the gameboard.
	bool isTimeLim(); // Returns if a time limit is set or not.

	/* Drawing. */
	void drawCharacters(sf::RenderWindow &window);
	void drawElves(sf::RenderWindow &window);
	void drawUnmovables(sf::RenderWindow &window);
	void drawArrow(sf::RenderWindow& window); // Indicates visually which player (character) is currently played.

private:
	vector<unique_ptr<MovableObject>> m_characters; // Stores players (characters).
	vector<unique_ptr<Elf>> m_elves; // Stores elves.
	vector<unique_ptr<UnmovableObject>> m_unmovables; // Stores unmovable objects.
	vector<sf::Vector2f> m_portalsLocs; // Stores the locations of the portals.
	vector<string> m_levelFileNames; // Stores the names of the files of the levels.
	sf::Sprite m_playerArrow; // Stores the sprite of the currently player character indicator.
	int m_currentCharacter; // Stores the index of the currently played character.
	int m_currentLevel; // Stores the index of the current level.
	int m_timeLimit; // Stores the time limit (if there's one).
	bool m_timeLim; // Stores if there's a time limit or not.
	sf::Vector2u m_boardSize; // Stores the game area size (as read from the files).
	sf::RectangleShape m_boardFrame; // Stores the game area.
};