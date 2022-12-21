#include "Buffers.h"

/* Constructor of Buffers class. */
Buffers::Buffers()
{
	// Loads all the sound buffers.
	loadGameBuffer("bumpIntoWall.ogg");
	loadGameBuffer("keyLoot.ogg");
	loadGameBuffer("winLevel.ogg");
	loadGameBuffer("gateOpen.ogg");
	loadGameBuffer("tpSound.ogg");
	loadGameBuffer("fireTouch.ogg");
	loadGameBuffer("killFire.ogg");
	loadGameBuffer("orcDie.ogg");
	loadGameBuffer("keyDrop.ogg");
	loadGameBuffer("hoverSound.ogg");
	loadGameBuffer("gameStart.ogg");
	loadGameBuffer("clickSound.ogg");
	loadGameBuffer("switchPlayerSound.ogg");
	loadGameBuffer("killElvesSound.ogg");
	loadGameBuffer("collectGiftSound.ogg");
	loadGameBuffer("winGameSound.ogg");
}

/* Function to gain access to the buffers. */
sf::SoundBuffer* Buffers::getGameBuffer(Sounds_t bufferEnum)
{
	return &(m_gameBuffers[bufferEnum]);
}

// Makes an instance and is created only once.
Buffers& Buffers::instance()
{
	static Buffers instance;
	return instance;
}

// Function to load a sound buffer.
void Buffers::loadGameBuffer(const std::string fileName)
{
	sf::SoundBuffer temp;
	temp.loadFromFile(fileName);
	m_gameBuffers.push_back(temp);
}
