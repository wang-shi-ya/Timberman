#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "audio.h"
#include "button.h"

class SettingPanel {
private:
    sf::RectangleShape panel;
    sf::Text title;
    sf::Text backHint;

    // ��Ƶ���ư�ť
    Button musicToggleButton;
    Button soundToggleButton;
    Button musicVolUpButton;
    Button musicVolDownButton;
    Button soundVolUpButton;
    Button soundVolDownButton;

    // ������ʾ�ı�
    sf::Text musicVolText;
    sf::Text soundVolText;

    // ��ǰ����ֵ
    int musicVolume;
    int soundVolume;

    // ��Ƶ״̬
    bool musicEnabled;
    bool soundEnabled;

public:
    SettingPanel() : musicVolume(50), soundVolume(50), musicEnabled(true), soundEnabled(true) {}

    void init(const sf::Font& font) {
        // �������
        panel.setSize(sf::Vector2f(1920, 1080));
        panel.setFillColor(sf::Color(0, 0, 0, 180));
        panel.setOrigin(panel.getSize().x / 2, panel.getSize().y / 2);
        panel.setPosition(960, 540);

        // ����
        title.setFont(font);
        title.setString("Settings");
        title.setCharacterSize(80);
        title.setFillColor(sf::Color::White);
        title.setPosition(960 - title.getGlobalBounds().width / 2, 200);

        // ������ʾ
        backHint.setFont(font);
        backHint.setString("Click anywhere or press ESC to return");
        backHint.setCharacterSize(40);
        backHint.setFillColor(sf::Color::White);
        backHint.setPosition(960 - backHint.getGlobalBounds().width / 2, 800);

        // ��ʼ����ť
        musicToggleButton.init(font, "Music: ON", 50, sf::Vector2f(960, 350));
        soundToggleButton.init(font, "Sound: ON", 50, sf::Vector2f(960, 450));

        musicVolUpButton.init(font, "+", 40, sf::Vector2f(1100, 350));
        musicVolDownButton.init(font, "-", 40, sf::Vector2f(800, 350));

        soundVolUpButton.init(font, "+", 40, sf::Vector2f(1100, 450));
        soundVolDownButton.init(font, "-", 40, sf::Vector2f(800, 450));

        // ������ʾ�ı�
        musicVolText.setFont(font);
        musicVolText.setString("Vol: " + std::to_string(musicVolume));
        musicVolText.setCharacterSize(40);
        musicVolText.setFillColor(sf::Color::White);
        musicVolText.setPosition(900, 350);

        soundVolText.setFont(font);
        soundVolText.setString("Vol: " + std::to_string(soundVolume));
        soundVolText.setCharacterSize(40);
        soundVolText.setFillColor(sf::Color::White);
        soundVolText.setPosition(900, 450);
    }

    void draw(sf::RenderWindow& window) {
        window.draw(panel);
        window.draw(title);
        window.draw(backHint);

        // ���ư�ť
        musicToggleButton.draw(window);
        soundToggleButton.draw(window);
        musicVolUpButton.draw(window);
        musicVolDownButton.draw(window);
        soundVolUpButton.draw(window);
        soundVolDownButton.draw(window);

        // ���������ı�
        window.draw(musicVolText);
        window.draw(soundVolText);
    }

    // �������¼�
    bool handleClick(const sf::Vector2f& mousePos, Audio& audio) {
        if (musicToggleButton.isClicked(mousePos)) {
            musicEnabled = !musicEnabled;
            musicToggleButton.setText("Music: " + std::string(musicEnabled ? "ON" : "OFF"));
            audio.isMusicActive = musicEnabled;
            if (musicEnabled) {
                audio.playBackgroundMusic();
            }
            else {
                audio.backgroundSound.stop();
            }
            return true;
        }

        if (soundToggleButton.isClicked(mousePos)) {
            soundEnabled = !soundEnabled;
            soundToggleButton.setText("Sound: " + std::string(soundEnabled ? "ON" : "OFF"));
            audio.isAudioActive = soundEnabled;
            return true;
        }

        if (musicVolUpButton.isClicked(mousePos) && musicVolume < 100) {
            musicVolume += 10;
            musicVolText.setString("Vol: " + std::to_string(musicVolume));
            audio.backgroundSound.setVolume(musicVolume);
            return true;
        }

        if (musicVolDownButton.isClicked(mousePos) && musicVolume > 0) {
            musicVolume -= 10;
            musicVolText.setString("Vol: " + std::to_string(musicVolume));
            audio.backgroundSound.setVolume(musicVolume);
            return true;
        }

        if (soundVolUpButton.isClicked(mousePos) && soundVolume < 100) {
            soundVolume += 10;
            soundVolText.setString("Vol: " + std::to_string(soundVolume));
            audio.timberSound.setVolume(soundVolume);
            audio.deadOrOutOfTimeSound.setVolume(soundVolume);
            return true;
        }

        if (soundVolDownButton.isClicked(mousePos) && soundVolume > 0) {
            soundVolume -= 10;
            soundVolText.setString("Vol: " + std::to_string(soundVolume));
            audio.timberSound.setVolume(soundVolume);
            audio.deadOrOutOfTimeSound.setVolume(soundVolume);
            return true;
        }

        return false;
    }

    // ����Ƿ����˱�������
    bool isBackgroundClicked(const sf::Vector2f& mousePos) const {
        return panel.getGlobalBounds().contains(mousePos) &&
            !musicToggleButton.isClicked(mousePos) &&
            !soundToggleButton.isClicked(mousePos) &&
            !musicVolUpButton.isClicked(mousePos) &&
            !musicVolDownButton.isClicked(mousePos) &&
            !soundVolUpButton.isClicked(mousePos) &&
            !soundVolDownButton.isClicked(mousePos);
    }

    // ��ȡ��ǰ��������
    int getMusicVolume() const { return musicVolume; }
    int getSoundVolume() const { return soundVolume; }
    bool isMusicEnabled() const { return musicEnabled; }
    bool isSoundEnabled() const { return soundEnabled; }
};