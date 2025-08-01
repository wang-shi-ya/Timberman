class Axe {
public:
    sf::Sprite sprite;
    sf::Texture texture;
    bool isAxeActive = false;
    bool isVisible = false; // 新增：控制斧头是否可见

    float axeVisibleTime = 0.0f;
    const float AXE_VISIBLE_DURATION = 0.1f; // 斧头显示时间（秒）

    void loadTexture(const std::string& filename) {
        if (!texture.loadFromFile(filename)) {
            throw std::runtime_error("Failed to load axe texture");
        }
        sprite.setTexture(texture);
        sprite.setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);
    }

    void setPosition(float x, float y) {
        sprite.setPosition(x, y);
    }

    void setScale(float x, float y) {
        sprite.setScale(x, y);
    }

    void showAxe(sf::RenderWindow& window) {
        if (isVisible) { // 只有可见时才渲染
            window.draw(sprite);
        }
    }
};