#pragma once
#include <SFML/Graphics.hpp>

class Time {
private:
    sf::RectangleShape timeBar;
    float timeBarStartWidth = 400;
    float timeBarHeight = 80;

    float Begintime = 10.0f; // 初始时间为10秒
    float addtime = 0.5f;    // 每次点击增加0.5秒
    float timeRemaining = 10.0f;
    float timeBarWidthPerSecond;
    
    // 新增变量
    float baseSpeed = 1.0f;  // 基础速度
    float acceleration = 0.1f; // 加速度
    float currentSpeedMultiplier = 1.0f; // 当前速度倍数
	float maxSpeedMultiplier = 3.0f; // 最大速度倍数

public:
    sf::Clock clock;
    sf::Time dt = clock.restart();

    Time() {
        reset();  // 构造函数中初始化
    }

    // 初始化时间条的外观和参数
    void updateTimeBar() {
        timeBar.setSize(sf::Vector2f(timeBarWidthPerSecond * timeRemaining, timeBarHeight));
        timeBar.setFillColor(sf::Color::Red);
        timeBar.setPosition((1920 / 2.f) - timeBarStartWidth / 2.f, 80);
    }

    // 每帧更新时间条宽度
    void update() {
        if (timeRemaining > 0) {
            // 随着时间推进，速度逐渐加快
            currentSpeedMultiplier += acceleration * dt.asSeconds();//
            
            // 限制最大速度倍数（可选）
            if (currentSpeedMultiplier > maxSpeedMultiplier) {
                currentSpeedMultiplier = maxSpeedMultiplier;
            }
            
            timeRemaining -= dt.asSeconds() * baseSpeed * currentSpeedMultiplier;
            if (timeRemaining < 0) timeRemaining = 0;
        }
        timeBar.setSize(sf::Vector2f(timeBarWidthPerSecond * timeRemaining, timeBarHeight));
    }

    // 每一次点击增加时间
    void addTime() {
        timeRemaining += addtime;
        if (timeRemaining > Begintime) timeRemaining = Begintime; // 限制最大时间
    }

    // 每帧更新dt
    void updateDt() {
        dt = clock.restart();
    }

    // 获取剩余时间
    float getTimeRemaining() const {
        return timeRemaining;
    }

    // 绘制时间条
    void showTimeBar(sf::RenderWindow& window) const {
        window.draw(timeBar);
    }

    // 重置时间状态
    void reset() {
        timeRemaining = Begintime;
        timeBarWidthPerSecond = timeBarStartWidth / timeRemaining;
        currentSpeedMultiplier = 1.0f; // 重置速度倍数
        updateTimeBar();
    }
};