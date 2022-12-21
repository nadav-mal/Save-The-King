#include "Sound.h"

Sound::Sound()
{
	/* List of sounds. */
	setSound("bumpIntoWall.ogg", bumpIntoWall);
	setSound("keyLoot.ogg", keyLoot);
	setSound("winLevel.ogg", winLevelSound);
	setSound("gateOpen.ogg", gateOpen);
	setSound("tpSound.ogg", tpSound);
	setSound("fireTouch.ogg", fireTouch);
	setSound("killFire.ogg", killFire);
	setSound("orcDie.ogg", orcDie);
	setSound("keyDrop.ogg", keyDrop);
	setSound("hoverSound.ogg", hoverSound);
	setSound("gameStart.ogg", gameStart);
	setSound("clickSound.ogg", clickSound);
	setSound("switchPlayerSound.ogg", switchPlayerSound);
	setSound("killElvesSound.ogg", killElvesSound);
	setSound("collectGiftSound.ogg", collectGiftSound);
	setSound("winGameSound.ogg", winGameSound);

	/* Volume initiation. */
	this->m_volume = defaultVol;
	this->setVolume();
}

/* Plays the sound once. */
void Sound::playSound(int place)
{
	this->m_sounds[place].play();
}

/* Plays the music in a loop. */
void Sound::playMusic(const std::string fileName)
{
	this->m_music.openFromFile(fileName);
	this->m_music.setLoop(true);
	this->m_music.play();
}

/* Stops the music. */
void Sound::stopMusic()
{
	this->m_music.stop();
}

/* Sets a new sound. Must have buffer. */
void Sound::setSound(const std::string fileName, Sounds_t soundEnum)
{
	sf::Sound tempSound;
	sf::SoundBuffer* tempBuffer = Buffers::instance().getGameBuffer(soundEnum);
	tempSound.setBuffer(*tempBuffer);
	this->m_sounds.push_back(tempSound);
}

/* This function is used to set the volume of the sounds and current music. */
void Sound::setVolume()
{
	for(int i = 0; i < this->m_sounds.size(); i++)
		this->m_sounds[i].setVolume(this->m_volume);

	this->m_music.setVolume(this->m_volume);
}

/* Function to increase volume. */
void Sound::incVolume()
{
	if (this->m_volume == 100) return;

	this->m_volume += 10;
	this->setVolume();
}

/* Function to decrease volume. */
void Sound::decVolume()
{
	if (this->m_volume == 0) return;

	this->m_volume -= 10;
	this->setVolume();
}

/* Function to mute and unmute volume. */
void Sound::muteVolume()
{
	/* Already muted. */
	if (this->m_volume == 0)
	{
		this->m_volume = m_prevVolume;
	}
	/* If already muted, unmute. */
	else
	{
		this->m_prevVolume = this->m_volume;
		this->m_volume = 0;
	}

	this->setVolume();
}