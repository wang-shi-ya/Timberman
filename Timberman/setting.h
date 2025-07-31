// settingpanel.h
#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class SettingPanel {
private:
    sf::RectangleShape panel;
    sf::Text title;
    sf::Text backHint;

public:
    SettingPanel() = default;//

    void init(const sf::Font& font) {
        panel.setSize(sf::Vector2f(1920, 1080));
        panel.setFillColor(sf::Color(0, 0, 0, 180));
        panel.setOrigin(panel.getSize().x / 2, panel.getSize().y / 2);
        panel.setPosition(960, 540);

        title.setFont(font);
        title.setString("Settings");
        title.setCharacterSize(80);
        title.setFillColor(sf::Color::White);
        title.setPosition(960 - title.getGlobalBounds().width / 2, 400);

        backHint.setFont(font);
        backHint.setString("Click anywhere or press ESC to return");
        backHint.setCharacterSize(40);
        backHint.setFillColor(sf::Color::White);
        backHint.setPosition(960 - backHint.getGlobalBounds().width / 2, 600);
    }

    void draw(sf::RenderWindow& window) {
        window.draw(panel);
        window.draw(title);
        window.draw(backHint);
    }
};
