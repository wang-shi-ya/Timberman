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

    // 音频控制按钮
    Button musicToggleButton;
    Button soundToggleButton;
    Button musicVolUpButton;
    Button musicVolDownButton;
    Button soundVolUpButton;
    Button soundVolDownButton;

    // 文本
    sf::Text musicVolText;
    sf::Text soundVolText;

    // 当前音量值
    int musicVolume;
    int soundVolume;
    std::vector<std::string> language = { "simpleChinese","English" };

    // 音频状态
    bool musicEnabled;
    bool soundEnabled;

    // 设置文件名
    const std::string SETTINGS_FILE = "settings.cfg";

public:
    SettingPanel() : musicVolume(50), soundVolume(50), musicEnabled(true), soundEnabled(true) {
        loadSettings(); // 构造函数中加载设置
    }

    ~SettingPanel() {
        saveSettings(); // 析构函数中保存设置
    }

    void init(const sf::Font& font) {
        // 背景面板
        panel.setSize(sf::Vector2f(1920, 1080));
        panel.setFillColor(sf::Color(112, 76, 5, 255));
        panel.setOrigin(panel.getSize().x / 2, panel.getSize().y / 2);
        panel.setPosition(960, 540);

        // 标题
        title.setFont(font);
        title.setString("Settings");
        title.setCharacterSize(80);
        title.setFillColor(sf::Color::White);
        title.setPosition(960 - title.getGlobalBounds().width / 2, 0);

        // 返回提示
        backHint.setFont(font);
        backHint.setString("Click ESC to return");
        backHint.setCharacterSize(40);
        backHint.setFillColor(sf::Color::White);
        backHint.setPosition(960 - backHint.getGlobalBounds().width / 2, 800);

        /***********音量音乐设置***************/

        // 初始化按钮
        musicToggleButton.init(font, "Music: " + std::string(musicEnabled ? "ON" : "OFF"), 50, sf::Vector2f(200, 150));
        soundToggleButton.init(font, "Sound: " + std::string(soundEnabled ? "ON" : "OFF"), 50, sf::Vector2f(1160, 150));

        musicVolUpButton.init(font, "+", 40, sf::Vector2f(620, 150));
        musicVolDownButton.init(font, "-", 40, sf::Vector2f(400, 150));

        soundVolUpButton.init(font, "+", 40, sf::Vector2f(1580, 150));
        soundVolDownButton.init(font, "-", 40, sf::Vector2f(1360, 150));

        // 音量显示文本
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

        // 绘制按钮
        musicToggleButton.draw(window);
        soundToggleButton.draw(window);
        musicVolUpButton.draw(window);
        musicVolDownButton.draw(window);
        soundVolUpButton.draw(window);
        soundVolDownButton.draw(window);

        // 绘制音量文本
        window.draw(musicVolText);
        window.draw(soundVolText);
    }

    // 处理点击事件
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
            saveSettings(); // 设置改变时立即保存
        }

        return settingChanged;
    }

    // 检查是否点击了背景区域
    bool isBackgroundClicked(const sf::Vector2f& mousePos) const {
        return panel.getGlobalBounds().contains(mousePos) &&
            !musicToggleButton.isClicked(mousePos) &&
            !soundToggleButton.isClicked(mousePos) &&
            !musicVolUpButton.isClicked(mousePos) &&
            !musicVolDownButton.isClicked(mousePos) &&
            !soundVolUpButton.isClicked(mousePos) &&
            !soundVolDownButton.isClicked(mousePos);
    }

    // 获取当前音量设置
    int getMusicVolume() const { return musicVolume; }
    int getSoundVolume() const { return soundVolume; }
    bool isMusicEnabled() const { return musicEnabled; }
    bool isSoundEnabled() const { return soundEnabled; }

private:
    // 保存设置到文件
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

    // 从文件加载设置
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