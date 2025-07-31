#pragma once
#include<SFML/Audio.hpp>
class audio {
public:
	bool isAudioActive =false;//������
	bool isMusicActive = false;//����
	bool isTimberAudio = false;//��Ч

	// ��Ч����
	sf::Sound TimberSound, BackgroundSound,DeadOrOutOfTimeSound;
	sf::SoundBuffer timberSoundBuffer,backgroundSoundBuffer,deadtimeSoundBuffer;

	//���ؿ�����Ч
	void loadTimberAudio() {
		if (!timberSoundBuffer.loadFromFile("resource/sound/chop.wav")) {
			throw std::runtime_error("Failed to load timber sound");
		}
		TimberSound.setBuffer(timberSoundBuffer);
	}
	void loadBackgroundAudio() {
		if (!backgroundSoundBuffer.loadFromFile("resource/sound/background.wav")) {
			throw std::runtime_error("Failed to load background sound");
		}
		BackgroundSound.setBuffer(backgroundSoundBuffer);
	}
	void loadDeadAudio(bool isDead ,bool isTimeDead) {
		if (!isDead && !isTimeDead) return; // �����������״̬�򲻼���
		else if (isDead && !isTimeDead) {
			if (!deadtimeSoundBuffer.loadFromFile("resource/sound/death.wav")) {
				throw std::runtime_error("Failed to load dead sound");
			}
			DeadOrOutOfTimeSound.setBuffer(deadtimeSoundBuffer);
		}
		else if (!isDead && !isTimeDead) {
			if (!deadtimeSoundBuffer.loadFromFile("resource/sound/out_of_time.wav")) {
				throw std::runtime_error("Failed to load dead sound");
			}
			DeadOrOutOfTimeSound.setBuffer(deadtimeSoundBuffer);
		}
	}
	//������Ч
	void playAudio() {
		if (!isAudioActive) return; // �����Чδ�����򲻲���
		else if (isAudioActive) {
			if (isTimberAudio) {
				TimberSound.play();
				DeadOrOutOfTimeSound.play();
			}
			if (isMusicActive) {
				BackgroundSound.play();
			}
		}
	}
};
