#include "Sound.hpp"
#include "Constants.hpp"

void InitSound(Sound& sound)
{
	sound.playGameSoundBuffer.loadFromFile(RESOURCES_PATH + "Audio/PlayGame.wav");
	sound.playGameSound.setBuffer(sound.playGameSoundBuffer);

	sound.ambient.openFromFile(RESOURCES_PATH + "Audio/Ambient.wav");
	sound.ambientMusic.openFromFile(RESOURCES_PATH + "Audio/AmbientMusic.wav");

	sound.walkSoundBuffer.loadFromFile(RESOURCES_PATH + "Audio/Move.wav");
	sound.walkSound.setBuffer(sound.walkSoundBuffer);

	sound.playerAttackSoundBuffer.loadFromFile(RESOURCES_PATH + "Audio/PlayerAttack.wav");
	sound.playerAttackSound.setBuffer(sound.playerAttackSoundBuffer);

	sound.playerDeadSoundBuffer.loadFromFile(RESOURCES_PATH + "Audio/PlayerDead.wav");
	sound.playerDeadSound.setBuffer(sound.playerDeadSoundBuffer);

	sound.playerCritAttackSoundBuffer.loadFromFile(RESOURCES_PATH + "Audio/PlayerCriticalAttack.wav");
	sound.playerCritAttackSound.setBuffer(sound.playerCritAttackSoundBuffer);

	sound.enemyAttackSoundBuffer.loadFromFile(RESOURCES_PATH + "Audio/EnemyAttack.wav");
	sound.enemyAttackSound.setBuffer(sound.enemyAttackSoundBuffer);

	sound.ambient.play();
	sound.ambientMusic.play();
}