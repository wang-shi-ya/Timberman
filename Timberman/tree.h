#pragma once
#include <iostream>
#include<SFML/Graphics.hpp>
#include <string>
#include<vector>

class Tree {
private:
	sf::Vector2f originalPosition;
	bool isMovingDown = false;
	float moveDistance = 0;
	const float totalMoveDistance = 150;

public:
	sf::Texture treeTexture;
	sf::Sprite treeSprite;
	bool isTreeBack = true;
	float treeSpeedX = 0;
	float treeSpeedY = 800;

	void loadTexture(const std::string& texturePath) {
		if (!treeTexture.loadFromFile(texturePath)) {
			throw std::runtime_error("Failed to load tree texture");
		}
		treeSprite.setTexture(treeTexture);
	}

	void setPosition(float x, float y) {
		treeSprite.setPosition(x, y);
		originalPosition = sf::Vector2f(x, y);
	}

	void showTree(sf::RenderWindow& window) const {
		window.draw(treeSprite);
	}

	void startMovingDown() {
		treeSprite.setPosition(810, -150);
		isMovingDown = true;
		isTreeBack = false;
		moveDistance = 0;
	}
	void update(float dt) {
		if (isMovingDown) {
			float moveAmount = treeSpeedY * dt;
			treeSprite.move(0, moveAmount);
			moveDistance += moveAmount;

			if (moveDistance >= totalMoveDistance) {
				isMovingDown = false;
				treeSprite.setPosition(originalPosition);
				isTreeBack = true;
			}
		}
	}
	

	bool isBack() const {
		return isTreeBack;
	}
};