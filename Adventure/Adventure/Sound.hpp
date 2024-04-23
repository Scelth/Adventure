#pragma once
#include <SFML/Audio.hpp>

struct Sound
{
	sf::SoundBuffer playGameSoundBuffer;
	sf::Sound playGameSound;

	sf::Music ambient;
	sf::Music ambientMusic;

	sf::SoundBuffer playerAttackSoundBuffer;
	sf::Sound playerAttackSound;

	sf::SoundBuffer playerCritAttackSoundBuffer;
	sf::Sound playerCritAttackSound;

	sf::SoundBuffer playerDeadSoundBuffer;
	sf::Sound playerDeadSound;

	sf::SoundBuffer walkSoundBuffer;
	sf::Sound walkSound;

	sf::SoundBuffer enemyAttackSoundBuffer;
	sf::Sound enemyAttackSound;
};

void InitSound(Sound& sound);

void TurnOnAmbient(Sound& sound);

void TurnOffAmbient(Sound& sound);

void PauseAmbient(Sound& sound);