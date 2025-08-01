#ifndef RECORDPANEL_H
#define RECORDPANEL_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <tuple> 
#include "database.h"

class RecordPanel {
public:
    RecordPanel();
    void init(sf::Font& font);
    void updateRecords(Database& db);
    void draw(sf::RenderWindow& window);
    void setPosition(const sf::Vector2f& position);

private:
    sf::Text title;
    std::vector<sf::Text> recordTexts;
    sf::RectangleShape background;
    sf::Font* font;
};

#endif // RECORDPANEL_H