#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Log {
public:
    static sf::Texture logTexture; // ��̬��ͼ
    sf::Sprite logSprite;
    bool logActive = false;
    float logSpeedX = 1000;
    float logSpeedY = -800;

	Log() {// ���캯��
        logSprite.setTexture(logTexture);
    }

    static void loadSharedTexture(const std::string& texturepath) {
        if (!logTexture.loadFromFile(texturepath)) {
            std::cerr << "Failed to load log texture from: " << texturepath << std::endl;
        }
    }

    void setPosition(float x, float y) {
        logSprite.setPosition(x, y);
    }

    void setScale(float x, float y) {
        logSprite.setScale(x, y);
    }

    void setOrgin(float x, float y) {
        logSprite.setOrigin(x, y);
    }

    void showLog(sf::RenderWindow& window) const {
        window.draw(logSprite);
    }
};

// ��̬��������
sf::Texture Log::logTexture;
