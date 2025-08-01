#include "recordpanel.h"
#include <tuple> 
#include <sstream>

RecordPanel::RecordPanel() : font(nullptr) {
    background.setFillColor(sf::Color(50, 50, 50, 200));
    background.setOutlineColor(sf::Color::White);
    background.setOutlineThickness(2.f);
}

void RecordPanel::init(sf::Font& font) {
    this->font = &font;

    title.setFont(font);
    title.setString("TOP SCORES");
    title.setCharacterSize(60);
    title.setFillColor(sf::Color::Yellow);

    for (int i = 0; i < 10; ++i) {
        sf::Text text;
        text.setFont(font);
        text.setCharacterSize(40);
        text.setFillColor(sf::Color::White);
        recordTexts.push_back(text);
    }

    setPosition(sf::Vector2f(960, 540));
}

void RecordPanel::updateRecords(Database& db) {
    try {
        auto records = db.getTopScores(10);

        for (size_t i = 0; i < recordTexts.size(); ++i) {
            if (i < records.size()) {
                std::stringstream ss;
                auto& record = records[i];
                ss << (i + 1) << ". " << std::get<1>(record) << ": " << std::get<0>(record)
                    << " (" << std::get<2>(record) << ")";
                recordTexts[i].setString(ss.str());
            }
            else {
                recordTexts[i].setString(std::to_string(i + 1) + ". ---");
            }
            // 重置原点以确保正确对齐
            recordTexts[i].setOrigin(0, 0);
        }
    }
    catch (const std::exception& e) {
        for (auto& text : recordTexts) {
            text.setString("Error loading records");
        }
    }
}

void RecordPanel::draw(sf::RenderWindow& window) {
    window.draw(background);
    window.draw(title);

    for (auto& text : recordTexts) {
        window.draw(text);
    }
}

void RecordPanel::setPosition(const sf::Vector2f& position) {
    background.setPosition(position);
    background.setSize(sf::Vector2f(1000, 700));
    background.setOrigin(background.getSize().x / 2, background.getSize().y / 2);

    title.setPosition(position.x, position.y - 300);
    title.setOrigin(title.getLocalBounds().width / 2, title.getLocalBounds().height / 2);

    for (size_t i = 0; i < recordTexts.size(); ++i) {
        recordTexts[i].setPosition(position.x - 400, position.y - 200 + i * 50);
    }
}