#pragma once
#include<SFML/Graphics.hpp>
class Axe {
private:
	sf::Texture axeTexture; // 斧头纹理
	sf::Sprite axeSprite; // 斧头精灵
public:
	bool isAxeActive = false; // 斧头是否激活
	void loadTexture(const std::string& texturepath) {
		if (!axeTexture.loadFromFile(texturepath)) {
			throw std::runtime_error("Failed to load branch texture");
		}
		axeSprite.setTexture(axeTexture);
	}
	void setPosition(float x, float y) {
		axeSprite.setPosition(x,y);
	}
	void setScale(float x,float y) {
		axeSprite.setScale(x, y);
	}
	void setOrgin() {
		axeSprite.setOrigin(axeTexture.getSize().x / 2, 0);
	}
	void showAxe(sf::RenderWindow& window)const {
		window.draw(axeSprite);
	}
};
