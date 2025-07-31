#pragma once
#include<SFML/Audio.hpp>
class audio {
public:
	bool isAudioActive =false;//总声音
	bool isMusicActive = false;//音乐
	bool isTimberAudio = false;//音效

	// 音效对象
	sf::Sound TimberSound, BackgroundSound,DeadOrOutOfTimeSound;
	sf::SoundBuffer timberSoundBuffer,backgroundSoundBuffer,deadtimeSoundBuffer;

	//加载砍树音效
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
		if (!isDead && !isTimeDead) return; // 如果不是死亡状态则不加载
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
	//播放音效
	void playAudio() {
		if (!isAudioActive) return; // 如果音效未激活则不播放
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
