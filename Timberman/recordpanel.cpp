#include "recordpanel.h"

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

    // 初始化排行内容
    for (int i = 0; i < 10; ++i) {
        sf::Text text;
        text.setFont(font);
        text.setCharacterSize(40);
        text.setFillColor(sf::Color::White);
        recordTexts.push_back(text);
    }

    setPosition(sf::Vector2f(960, 540));
}

void RecordPanel::updateRecords(Database& db) {// 更新记录面板
    auto records = db.getTopScores(10);

    for (size_t i = 0; i < recordTexts.size(); ++i) {
        if (i < records.size()) {
            recordTexts[i].setString(std::to_string(i + 1) + ". " +
                records[i].second + ": " +
                std::to_string(records[i].first));
        }
        else {
            recordTexts[i].setString(std::to_string(i + 1) + ". ---");
        }
    }

    // Update positions
    setPosition(background.getPosition());
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
    background.setSize(sf::Vector2f(1600, 960));

    // 显示在屏幕中心
    sf::FloatRect bounds = background.getLocalBounds();
    background.setOrigin(bounds.width / 2, bounds.height / 2);

    title.setPosition(position.x, position.y - 250);
    title.setOrigin(title.getLocalBounds().width / 2, title.getLocalBounds().height / 2);

    for (size_t i = 0; i < recordTexts.size(); ++i) {
        recordTexts[i].setPosition(position.x - 200, position.y - 200 + i * 50);
    }
}