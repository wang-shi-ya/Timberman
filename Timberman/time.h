#pragma once
#include <SFML/Graphics.hpp>

class Time {
private:
    sf::RectangleShape timeBar;
    float timeBarStartWidth = 400;
    float timeBarHeight = 80;

    float Begintime = 10.0f; // ��ʼʱ��Ϊ10��
    float addtime = 0.5f;    // ÿ�ε������0.5��
    float timeRemaining = 10.0f;
    float timeBarWidthPerSecond;
    
    // ��������
    float baseSpeed = 1.0f;  // �����ٶ�
    float acceleration = 0.1f; // ���ٶ�
    float currentSpeedMultiplier = 1.0f; // ��ǰ�ٶȱ���
	float maxSpeedMultiplier = 3.0f; // ����ٶȱ���

public:
    sf::Clock clock;
    sf::Time dt = clock.restart();

    Time() {
        reset();  // ���캯���г�ʼ��
    }

    // ��ʼ��ʱ��������ۺͲ���
    void updateTimeBar() {
        timeBar.setSize(sf::Vector2f(timeBarWidthPerSecond * timeRemaining, timeBarHeight));
        timeBar.setFillColor(sf::Color::Red);
        timeBar.setPosition((1920 / 2.f) - timeBarStartWidth / 2.f, 80);
    }

    // ÿ֡����ʱ�������
    void update() {
        if (timeRemaining > 0) {
            // ����ʱ���ƽ����ٶ��𽥼ӿ�
            currentSpeedMultiplier += acceleration * dt.asSeconds();//
            
            // ��������ٶȱ�������ѡ��
            if (currentSpeedMultiplier > maxSpeedMultiplier) {
                currentSpeedMultiplier = maxSpeedMultiplier;
            }
            
            timeRemaining -= dt.asSeconds() * baseSpeed * currentSpeedMultiplier;
            if (timeRemaining < 0) timeRemaining = 0;
        }
        timeBar.setSize(sf::Vector2f(timeBarWidthPerSecond * timeRemaining, timeBarHeight));
    }

    // ÿһ�ε������ʱ��
    void addTime() {
        timeRemaining += addtime;
        if (timeRemaining > Begintime) timeRemaining = Begintime; // �������ʱ��
    }

    // ÿ֡����dt
    void updateDt() {
        dt = clock.restart();
    }

    // ��ȡʣ��ʱ��
    float getTimeRemaining() const {
        return timeRemaining;
    }

    // ����ʱ����
    void showTimeBar(sf::RenderWindow& window) const {
        window.draw(timeBar);
    }

    // ����ʱ��״̬
    void reset() {
        timeRemaining = Begintime;
        timeBarWidthPerSecond = timeBarStartWidth / timeRemaining;
        currentSpeedMultiplier = 1.0f; // �����ٶȱ���
        updateTimeBar();
    }
};