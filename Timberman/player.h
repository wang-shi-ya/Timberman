#pragma once
#include <SFML/Graphics.hpp>
#include<iostream>
#include<Windows.h>

class Player
{
private:
	sf::Sprite playerSprite;
	sf::Texture playerTexture;

	int score = 0; // 玩家得分

public:
	bool isPlayerDead = false; // 玩家是否死亡
	bool isPlayerCut = false;
	void loadPlayer(const std::string& texturePath) {// 加载玩家纹理
		if (!playerTexture.loadFromFile(texturePath)) {
			throw std::runtime_error("Failed to load player texture");
		}
		playerSprite.setTexture(playerTexture);
		playerSprite.setPosition(1250, 750); // 设置初始位置	
	}
	void setPosition(float x, float y) { // 设置玩家位置
		playerSprite.setPosition(x, y);
	}
	void setScale(float x, float y) { // 设置玩家缩放
		playerSprite.setScale(x, y);
	}
	void setOrigin(float x, float y) { // 设置玩家原点
		playerSprite.setOrigin(x, y);
	}
	void showplayer(sf::RenderWindow& window) const { // 显示玩家
		window.draw(playerSprite);
	}
	sf::Sprite getSprite() const { // 获取玩家精灵
		return playerSprite;
	}
};