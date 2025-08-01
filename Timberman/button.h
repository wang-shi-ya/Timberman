#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class Button {
private:
    sf::Text text;
    sf::RectangleShape background;

public:
    Button() = default;

    void init(const sf::Font& font, const std::string& label, unsigned int size, sf::Vector2f position) {
        text.setFont(font);
        text.setString(label);
        text.setCharacterSize(size);
        text.setFillColor(sf::Color::White);
        text.setOutlineColor(sf::Color::Black);
        text.setOutlineThickness(3);
        text.setOrigin(text.getLocalBounds().width / 2, text.getLocalBounds().height / 2);
        text.setPosition(position);

        background.setSize(sf::Vector2f(text.getLocalBounds().width + 40, text.getLocalBounds().height + 40));
        background.setOrigin(background.getSize().x / 2, background.getSize().y / 2);
        background.setPosition(position);
        background.setFillColor(sf::Color(50, 50, 50, 200));
    }

    // 添加 setText 方法
    void setText(const std::string& newText) {
        text.setString(newText);
        // 更新文本位置和背景大小
        text.setOrigin(text.getLocalBounds().width / 2, text.getLocalBounds().height / 2);
        background.setSize(sf::Vector2f(text.getLocalBounds().width + 40, text.getLocalBounds().height + 40));
    }

    void draw(sf::RenderWindow& window) {
        window.draw(background);
        window.draw(text);
    }

    bool isClicked(const sf::Vector2f& mousePos) const {
        return background.getGlobalBounds().contains(mousePos);
    }
};