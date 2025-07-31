#pragma once
#include <SFML/Graphics.hpp>
#include<iostream>
#include<Windows.h>

class Player
{
private:
	sf::Sprite playerSprite;
	sf::Texture playerTexture;

	int score = 0; // ��ҵ÷�

public:
	bool isPlayerDead = false; // ����Ƿ�����
	bool isPlayerCut = false;
	void loadPlayer(const std::string& texturePath) {// �����������
		if (!playerTexture.loadFromFile(texturePath)) {
			throw std::runtime_error("Failed to load player texture");
		}
		playerSprite.setTexture(playerTexture);
		playerSprite.setPosition(1250, 750); // ���ó�ʼλ��	
	}
	void setPosition(float x, float y) { // �������λ��
		playerSprite.setPosition(x, y);
	}
	void setScale(float x, float y) { // �����������
		playerSprite.setScale(x, y);
	}
	void setOrigin(float x, float y) { // �������ԭ��
		playerSprite.setOrigin(x, y);
	}
	void showplayer(sf::RenderWindow& window) const { // ��ʾ���
		window.draw(playerSprite);
	}
	sf::Sprite getSprite() const { // ��ȡ��Ҿ���
		return playerSprite;
	}
};