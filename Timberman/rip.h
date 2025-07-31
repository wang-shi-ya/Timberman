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
		//ripSprite.setPosition(600, 860); // ���ó�ʼλ��
	}
	sf::Sprite getSprite() { // ��ȡ����
		return ripSprite;
	}
	void setPosition(float x, float y) { // ����λ��
		ripSprite.setPosition(x, y);
	}
	// ��������
	void setScale(float x, float y) { // ��������
		ripSprite.setScale(x, y);
	}
	// ����ԭ��
	void setOrigin(float x, float y) { // ����ԭ��
		ripSprite.setOrigin(x, y);
	}
	//��ʾĹ��
	void showRip(sf::RenderWindow& window,Player player){ // ��ʾĹ��
		setPosition(player.getSprite().getPosition().x , player.getSprite().getPosition().y+20 ); // ����Ĺ��λ��������·�
		window.draw(ripSprite);
	}
};
