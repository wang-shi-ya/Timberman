#pragma once
#include<SFML/Audio.hpp>
class Audio {
public:
	bool isAudioActive = true;    // 总声音开关
	bool isMusicActive = true;    // 背景音乐开关
	bool isTimberAudio = true;    // 砍树音效开关

	// 音效对象
	sf::Sound timberSound;
	sf::Sound backgroundSound;
	sf::Sound deadOrOutOfTimeSound;

	// 音效缓冲区
	sf::SoundBuffer timberSoundBuffer;
	sf::SoundBuffer backgroundSoundBuffer;
	sf::SoundBuffer deadtimeSoundBuffer;

	Audio() {
		// 在构造函数中加载所有音效
		loadTimberAudio();
		loadBackgroundAudio();
	}

	// 加载砍树音效
	void loadTimberAudio() {
		if (!timberSoundBuffer.loadFromFile("resource/sound/chop.wav")) {
			throw std::runtime_error("Failed to load timber sound");
		}
		timberSound.setBuffer(timberSoundBuffer);
	}

	// 加载背景音乐
	void loadBackgroundAudio() {
		if (!backgroundSoundBuffer.loadFromFile("resource/sound/backgroundmusic.wav")) {
			throw std::runtime_error("Failed to load background sound");
		}
		backgroundSound.setBuffer(backgroundSoundBuffer);
		backgroundSound.setLoop(true); // 设置循环播放
	}

	// 加载死亡/超时音效
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

	// 播放背景音乐
	void playBackgroundMusic() {
		if (isAudioActive && isMusicActive) {
			if (backgroundSound.getStatus() != sf::Sound::Playing) {
				backgroundSound.play();
			}
		}
	}

	// 播放砍树音效
	void playTimberAudio() {
		if (isAudioActive && isTimberAudio) {
			timberSound.play();
		}
	}

	// 播放死亡/超时音效
	void playDeadAudio() {
		if (isAudioActive) {
			deadOrOutOfTimeSound.play();
		}
	}

};