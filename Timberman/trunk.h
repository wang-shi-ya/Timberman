class Trunk {
private:
    std::vector<sf::Texture> trunkTextures;
    std::vector<sf::Sprite> trunkSprites;
    std::mt19937 gen;

public:
    Trunk() {
        std::random_device rd;
        gen.seed(rd());

        // 预加载所有可能的树干纹理
        for (int i = 0; i < 6; ++i) {
            sf::Texture texture;
            std::string path = "resource/graphics/trunk" + std::to_string(i + 1) + ".png";
            if (!texture.loadFromFile(path)) {
                throw std::runtime_error("Failed to load trunk texture: " + path);
            }
            trunkTextures.push_back(std::move(texture));
        }

        // 初始化树干
        for (int i = 0; i < 6; ++i) {
            addNewTrunkToTop();
        }
    }

    void addNewTrunkToTop() {
        int idx = gen() % 6; // 随机选择纹理
        sf::Sprite sprite;
        sprite.setTexture(trunkTextures[idx]);
        sprite.setPosition(810, 0);
        trunkSprites.insert(trunkSprites.begin(), sprite);
        updatePositions();
    }

	void updatePositions() {
		// 重新设置每一段 trunk 的位置
		for (int i = 0; i < trunkSprites.size(); ++i) {
			trunkSprites[i].setPosition(810, 150 * i);
		}
	}

	void updateTrunk(float dt) {
		// 删除最底部的树干（最后一个）
		if (!trunkSprites.empty()) {
			trunkSprites.pop_back();
		}
		// 在顶部添加一个新 trunk
		addNewTrunkToTop();
	}

	void showTrunk(sf::RenderWindow& window) const {
		for (const auto& sprite : trunkSprites) {
			window.draw(sprite);
		}
	}
};
