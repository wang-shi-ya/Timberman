#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <fstream>
#include <sstream>
#include "audio.h"
#include "button.h"
#include "font.h"

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

    // �ı�
    sf::Text musicVolText;
    sf::Text soundVolText;

    // ��ǰ����ֵ
    int musicVolume;
    int soundVolume;
    std::vector<std::string> language = { "simpleChinese","English" };

    // ��Ƶ״̬
    bool musicEnabled;
    bool soundEnabled;

    // �����ļ���
    const std::string SETTINGS_FILE = "settings.cfg";

public:
    SettingPanel() : musicVolume(50), soundVolume(50), musicEnabled(true), soundEnabled(true) {
        loadSettings(); // ���캯���м�������
    }

    ~SettingPanel() {
        saveSettings(); // ���������б�������
    }

    void init(const sf::Font& font) {
        // �������
        panel.setSize(sf::Vector2f(1920, 1080));
        panel.setFillColor(sf::Color(112, 76, 5, 255));
        panel.setOrigin(panel.getSize().x / 2, panel.getSize().y / 2);
        panel.setPosition(960, 540);

        // ����
        title.setFont(font);
        title.setString("Settings");
        title.setCharacterSize(80);
        title.setFillColor(sf::Color::White);
        title.setPosition(960 - title.getGlobalBounds().width / 2, 0);

        // ������ʾ
        backHint.setFont(font);
        backHint.setString("Click ESC to return");
        backHint.setCharacterSize(40);
        backHint.setFillColor(sf::Color::White);
        backHint.setPosition(960 - backHint.getGlobalBounds().width / 2, 800);

        /***********������������***************/

        // ��ʼ����ť
        musicToggleButton.init(font, "Music: " + std::string(musicEnabled ? "ON" : "OFF"), 50, sf::Vector2f(200, 150));
        soundToggleButton.init(font, "Sound: " + std::string(soundEnabled ? "ON" : "OFF"), 50, sf::Vector2f(1160, 150));

        musicVolUpButton.init(font, "+", 40, sf::Vector2f(620, 150));
        musicVolDownButton.init(font, "-", 40, sf::Vector2f(400, 150));

        soundVolUpButton.init(font, "+", 40, sf::Vector2f(1580, 150));
        soundVolDownButton.init(font, "-", 40, sf::Vector2f(1360, 150));

        // ������ʾ�ı�
        musicVolText.setFont(font);
        musicVolText.setString("Vol: " + std::to_string(musicVolume));
        musicVolText.setCharacterSize(40);
        musicVolText.setFillColor(sf::Color::White);
        musicVolText.setPosition(430, 140);

        soundVolText.setFont(font);
        soundVolText.setString("Vol: " + std::to_string(soundVolume));
        soundVolText.setCharacterSize(40);
        soundVolText.setFillColor(sf::Color::White);
        soundVolText.setPosition(1390, 140);
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
        bool settingChanged = false;

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
            settingChanged = true;
        }

        if (soundToggleButton.isClicked(mousePos)) {
            soundEnabled = !soundEnabled;
            soundToggleButton.setText("Sound: " + std::string(soundEnabled ? "ON" : "OFF"));
            audio.isAudioActive = soundEnabled;
            settingChanged = true;
        }

        if (musicVolUpButton.isClicked(mousePos) && musicVolume < 100) {
            musicVolume += 10;
            musicVolText.setString("Vol: " + std::to_string(musicVolume));
            audio.backgroundSound.setVolume(musicVolume);
            settingChanged = true;
        }

        if (musicVolDownButton.isClicked(mousePos) && musicVolume > 0) {
            musicVolume -= 10;
            musicVolText.setString("Vol: " + std::to_string(musicVolume));
            audio.backgroundSound.setVolume(musicVolume);
            settingChanged = true;
        }

        if (soundVolUpButton.isClicked(mousePos) && soundVolume < 100) {
            soundVolume += 10;
            soundVolText.setString("Vol: " + std::to_string(soundVolume));
            audio.timberSound.setVolume(soundVolume);
            audio.deadOrOutOfTimeSound.setVolume(soundVolume);
            settingChanged = true;
        }

        if (soundVolDownButton.isClicked(mousePos) && soundVolume > 0) {
            soundVolume -= 10;
            soundVolText.setString("Vol: " + std::to_string(soundVolume));
            audio.timberSound.setVolume(soundVolume);
            audio.deadOrOutOfTimeSound.setVolume(soundVolume);
            settingChanged = true;
        }

        if (settingChanged) {
            saveSettings(); // ���øı�ʱ��������
        }

        return settingChanged;
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

private:
    // �������õ��ļ�
    void saveSettings() {
        std::ofstream file(SETTINGS_FILE);
        if (file.is_open()) {
            file << "musicEnabled=" << (musicEnabled ? "1" : "0") << "\n";
            file << "soundEnabled=" << (soundEnabled ? "1" : "0") << "\n";
            file << "musicVolume=" << musicVolume << "\n";
            file << "soundVolume=" << soundVolume << "\n";
            file.close();
        }
    }

    // ���ļ���������
    void loadSettings() {
        std::ifstream file(SETTINGS_FILE);
        if (file.is_open()) {
            std::string line;
            while (std::getline(file, line)) {
                std::istringstream is_line(line);
                std::string key;
                if (std::getline(is_line, key, '=')) {
                    std::string value;
                    if (std::getline(is_line, value)) {
                        if (key == "musicEnabled") {
                            musicEnabled = (value == "1");
                        }
                        else if (key == "soundEnabled") {
                            soundEnabled = (value == "1");
                        }
                        else if (key == "musicVolume") {
                            musicVolume = std::stoi(value);
                        }
                        else if (key == "soundVolume") {
                            soundVolume = std::stoi(value);
                        }
                    }
                }
            }
            file.close();
        }
    }
};