#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include <vector>

class Branch {
public:
	enum class BranchState {
		RIGHT, LEFT, NONE
	};
private:

	struct BranchData {
		sf::Sprite sprite;
		BranchState state;
		sf::Vector2f targetPosition;
		float moveSpeed;
	};

	std::vector<BranchData> branches;
	sf::Texture branchTexture;
	BranchState playerSide = BranchState::RIGHT;

public:

	Branch() {
		const int NUM_BRANCH = 6;
		branches.resize(NUM_BRANCH);
	}

	void loadTexture(const std::string& texturePath) {
		if (!branchTexture.loadFromFile(texturePath)) {
			throw std::runtime_error("Failed to load branch texture");
		}
	}

	void initialize() {
		for (auto& branch : branches) {
			branch.sprite.setTexture(branchTexture);
			branch.sprite.setPosition(-2000, -2000); // 初始位置在屏幕外
			branch.sprite.setOrigin(220, 20); 
			branch.state = BranchState::NONE;
			branch.moveSpeed = 800.0f;
			branch.targetPosition = getPositionForState(branch.state, &branch - &branches[0]);// 设置目标位置
		}
	}

	void update(float deltaTime) {
		for (auto& branch : branches) {
			sf::Vector2f currentPos = branch.sprite.getPosition();
			sf::Vector2f direction = branch.targetPosition - currentPos;
			float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);

			if (distance > 5.0f) {//如果距离够大则移动
				direction /= distance;
				sf::Vector2f movement = direction * branch.moveSpeed * deltaTime;
				if (std::sqrt(movement.x * movement.x + movement.y * movement.y) > distance) {
					branch.sprite.setPosition(branch.targetPosition);
				}
				else {
					branch.sprite.move(movement);
				}
			}
			else {
				branch.sprite.setPosition(branch.targetPosition);
			}
		}
	}
	void updateBranches(int seed) {
		// 所有树枝状态向下移动一位
		for (int j = branches.size() - 1; j > 0; j--) {
			branches[j].state = branches[j - 1].state;
			branches[j].targetPosition = getPositionForState(branches[j].state, j);
			branches[j].sprite.setPosition(branches[j].targetPosition);

			// 设置翻转
			if (branches[j].state == BranchState::LEFT) {
				branches[j].sprite.setScale(-1.f, 1.f);
			}
			else {
				branches[j].sprite.setScale(1.f, 1.f);
			}
		}

		// 随机生成新树枝状态
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> dist(0, 2);

		int random = dist(gen);

		if (branches[1].state == BranchState::NONE) {
			branches[0].state = static_cast<BranchState>(random);
		}
		else {
			if (branches[1].state == BranchState::RIGHT && static_cast<BranchState>(random) == BranchState::LEFT) {
				branches[0].state = BranchState::NONE;
			}
			else if (branches[1].state == BranchState::LEFT && static_cast<BranchState>(random) == BranchState::RIGHT) {
				branches[0].state = BranchState::NONE;
			}
			else {
				branches[0].state = static_cast<BranchState>(random);
			}
		}

		// 设置新树枝的目标位置并同步
		branches[0].targetPosition = getPositionForState(branches[0].state, 0);
		branches[0].sprite.setPosition(branches[0].targetPosition);

		// 设置翻转
		if (branches[0].state == BranchState::LEFT) {
			branches[0].sprite.setScale(-1.f, 1.f);
		}
		else {
			branches[0].sprite.setScale(1.f, 1.f);
		}
	}


	sf::Vector2f getPositionForState(BranchState state, int index) {
		if (state == BranchState::RIGHT) {
			return sf::Vector2f(1330, index * 150+40);
		}
		else if (state == BranchState::LEFT) {
			return sf::Vector2f(590, index * 150+40);
		}
		else {
			return sf::Vector2f(-2000, -2000); // 隐藏
		}
	}

	void setPlayerSide(BranchState side) {
		playerSide = side;
	}

	BranchState getPlayerSide() const {
		return playerSide;
	}

	bool isGameOver() const {
		return !branches.empty() && branches.back().state == playerSide;
	}

	size_t getNumBranches() const {
		return branches.size();
	}

	void draw(sf::RenderWindow& window) const {
		for (const auto& branch : branches) {	
			window.draw(branch.sprite);
		}
	}
};
