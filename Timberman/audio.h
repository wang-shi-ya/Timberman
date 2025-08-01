#pragma once
#include<SFML/Audio.hpp>
class Audio {
public:
	bool isAudioActive = true;    // ����������
	bool isMusicActive = true;    // �������ֿ���
	bool isTimberAudio = true;    // ������Ч����

	// ��Ч����
	sf::Sound timberSound;
	sf::Sound backgroundSound;
	sf::Sound deadOrOutOfTimeSound;

	// ��Ч������
	sf::SoundBuffer timberSoundBuffer;
	sf::SoundBuffer backgroundSoundBuffer;
	sf::SoundBuffer deadtimeSoundBuffer;

	Audio() {
		// �ڹ��캯���м���������Ч
		loadTimberAudio();
		loadBackgroundAudio();
	}

	// ���ؿ�����Ч
	void loadTimberAudio() {
		if (!timberSoundBuffer.loadFromFile("resource/sound/chop.wav")) {
			throw std::runtime_error("Failed to load timber sound");
		}
		timberSound.setBuffer(timberSoundBuffer);
	}

	// ���ر�������
	void loadBackgroundAudio() {
		if (!backgroundSoundBuffer.loadFromFile("resource/sound/backgroundmusic.wav")) {
			throw std::runtime_error("Failed to load background sound");
		}
		backgroundSound.setBuffer(backgroundSoundBuffer);
		backgroundSound.setLoop(true); // ����ѭ������
	}

	// ��������/��ʱ��Ч
	void loadDeadAudio(bool isDead, bool isTimeDead) {
		if (!isDead && !isTimeDead) return;

		std::string soundFile;
		if (isDead) {
			soundFile = "resource/sound/death.wav";
		}
		else {
			soundFile = "resource/sound/out_of_time.wav";
		}

		if (!deadtimeSoundBuffer.loadFromFile(soundFile)) {
			throw std::runtime_error("Failed to load dead sound");
		}
		deadOrOutOfTimeSound.setBuffer(deadtimeSoundBuffer);
	}

	// ���ű�������
	void playBackgroundMusic() {
		if (isAudioActive && isMusicActive) {
			if (backgroundSound.getStatus() != sf::Sound::Playing) {
				backgroundSound.play();
			}
		}
	}

	// ���ſ�����Ч
	void playTimberAudio() {
		if (isAudioActive && isTimberAudio) {
			timberSound.play();
		}
	}

	// ��������/��ʱ��Ч
	void playDeadAudio() {
		if (isAudioActive) {
			deadOrOutOfTimeSound.play();
		}
	}

};