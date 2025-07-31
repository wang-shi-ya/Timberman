#pragma once
#include <SFML/Graphics.hpp>
#include"player.h"

class Rip {
private:
	sf::Texture ripTexture;
	sf::Sprite ripSprite;
public:
	void loadTexture(const std::string& texturePath) {
		if (!ripTexture.loadFromFile(texturePath)) {
			throw std::runtime_error("Failed to load rip texture");
		}
		ripSprite.setTexture(ripTexture);
		//ripSprite.setPosition(600, 860); // 设置初始位置
	}
	sf::Sprite getSprite() { // 获取精灵
		return ripSprite;
	}
	void setPosition(float x, float y) { // 设置位置
		ripSprite.setPosition(x, y);
	}
	// 设置缩放
	void setScale(float x, float y) { // 设置缩放
		ripSprite.setScale(x, y);
	}
	// 设置原点
	void setOrigin(float x, float y) { // 设置原点
		ripSprite.setOrigin(x, y);
	}
	//显示墓碑
	void showRip(sf::RenderWindow& window,Player player){ // 显示墓碑
		setPosition(player.getSprite().getPosition().x , player.getSprite().getPosition().y+20 ); // 设置墓碑位置在玩家下方
		window.draw(ripSprite);
	}
};
