#include <iostream>
#include <sstream>
#include <random>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include"audio.h"
#include "branch.h"
#include "player.h"
#include "tree.h"
#include "rip.h"
#include "axe.h"
#include "log.h"
#include "time.h"
#include "button.h"
#include"trunk.h"
#include "settingpanel.h"
#include "database.h"
#include "recordpanel.h"

int main() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, 2);

    //初始化数据库 

    Database db;
    if (!db.connect("localhost", "root", "HBsc75820306@", "timberman")) {
        std::cerr << "Failed to connect to database" << std::endl;
        return -1;
    }

    // 创建表（如果不存在）
    db.execute("CREATE TABLE IF NOT EXISTS scores ("
        "id INT AUTO_INCREMENT PRIMARY KEY, "
        "score INT NOT NULL, "
        "player_name VARCHAR(50) DEFAULT 'Player', "
        "created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP)");


    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Timber!!!", sf::Style::Resize);
    sf::Texture backgroundTexture;
    backgroundTexture.loadFromFile("resource/graphics/background.png");
    sf::Sprite backgroundSprite(backgroundTexture);

    Audio audio;

    Player player;
    player.loadPlayer("resource/graphics/player.png");
    player.setOrigin(player.getSprite().getTexture()->getSize().x / 2, 0);

    Axe axe;
    axe.loadTexture("resource/graphics/Theaxe1.png");

    Rip rip;
    rip.loadTexture("resource/graphics/rip.png");
    rip.setOrigin(rip.getSprite().getTexture()->getSize().x / 2, 0);

    Log::loadSharedTexture("resource/graphics/log.png");
    Log underlog;
    underlog.setPosition(810, 900);

    Tree tree2, tree3;
    tree2.loadTexture("resource/graphics/tree.png"); tree2.setPosition(-100, 0);
    tree3.loadTexture("resource/graphics/tree.png"); tree3.setPosition(1600, 0);
    Trunk trunk;
    for (int i = 0; i < 6; ++i) {
        std::stringstream texturePath;
        texturePath << "resource/graphics/trunk" << (i + 1) << ".png";
        texturePath.str("");
    }

    Branch branch;
    branch.loadTexture("resource/graphics/branch.png");
    branch.initialize();

    sf::Texture beeTexture;
    beeTexture.loadFromFile("resource/graphics/smallbee.png");
    sf::Sprite beeSprite(beeTexture);
    beeSprite.setPosition(100, 800);
    bool beeActive = false;
    float beeSpeed = 0.f;

    sf::Texture cloudTexture;
    cloudTexture.loadFromFile("resource/graphics/cloud.png");
    sf::Sprite cloudSprite(cloudTexture);
    cloudSprite.setPosition(0, 100);
    bool cloudActive = false;
    float cloudSpeed = 0.f;

    Time time;

    bool isPaused = true, isGameOver = false, acceptInput = false, isGameStarted = false;
    bool isInSettings = false, isInRecords = false;

    //****************字体******************//
    sf::Font font;
    if (!font.loadFromFile("resource/fonts/KOMIKAP_.ttf")) {
        std::cerr << "Failed to load font" << std::endl;
        return -1;
    }

    Button startButton, exitButton, settingsButton, recordButton;
    startButton.init(font, "START GAME", 80, sf::Vector2f(960, 350));
    recordButton.init(font, "RECORD", 80, sf::Vector2f(960, 500));
    settingsButton.init(font, "SETTINGS", 80, sf::Vector2f(960, 650));
    exitButton.init(font, "EXIT", 80, sf::Vector2f(960, 800));

    SettingPanel settingPanel;
    settingPanel.init(font);

    RecordPanel recordPanel;
    recordPanel.init(font);

    sf::Text messageText("", font, 75);
    sf::Text scoreText("Score = 0", font, 80);
    messageText.setFillColor(sf::Color::White);
    scoreText.setFillColor(sf::Color::White);
    messageText.setOrigin(messageText.getLocalBounds().width / 2, messageText.getLocalBounds().height / 2);
    messageText.setPosition(960 - messageText.getLocalBounds().width / 2, 540 - messageText.getLocalBounds().height / 2);
    scoreText.setPosition(20, 20);

    int score = 0;
    std::stringstream scoreStream;
    std::vector<Log> flyingLogs;

    int addscoreNum = 0;
    while (window.isOpen()) {
        time.updateDt();
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed ||
                (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape && !isInSettings && !isInRecords)) {
                if (isGameStarted && !isInSettings && !isInRecords) {
                    // 返回主界面
                    isGameStarted = false;
                    isPaused = true;
                    isGameOver = false;
                    messageText.setString("");
                }
                else {
                    window.close();
                }
            }

            // 在主循环的事件处理部分修改设置面板的处理逻辑
            if (isInSettings) {
                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                    isInSettings = false;
                }
                if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2f mousePos(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y));

                    // 先尝试处理按钮点击
                    bool buttonClicked = settingPanel.handleClick(mousePos, audio);

                    // 如果没有点击任何按钮，且点击了背景区域，才返回主菜单
                    if (!buttonClicked && settingPanel.isBackgroundClicked(mousePos)) {
                        isInSettings = false;
                    }
                }
                continue;
            }

            if (isInRecords) {
                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                    isInRecords = false;
                }
                if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2f mousePos(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y));
                    Button backButton;
                    backButton.init(font, "BACK", 50, sf::Vector2f(960, 850));
                    if (backButton.isClicked(mousePos)) {
                        isInRecords = false;
                    }
                }
                continue;
            }

            if (!isGameStarted) {
                if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2f mousePos(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y));
                    if (startButton.isClicked(mousePos)) {
                        isGameStarted = true;
                        isPaused = false;
                        acceptInput = true;
                        branch.initialize();
                        player.isPlayerDead = false;
                        time.reset();
                        score = 0;
                        scoreStream.str(""); scoreStream << "Score = " << score;
                        scoreText.setString(scoreStream.str());
                        messageText.setString("");
                        flyingLogs.clear();
                    }
                    else if (recordButton.isClicked(mousePos)) {
                        recordPanel.updateRecords(db);
                        isInRecords = true;
                    }
                    else if (exitButton.isClicked(mousePos)) {
                        window.close();
                    }
                    else if (settingsButton.isClicked(mousePos)) {
                        isInSettings = true;
                    }
                }
                continue;
            }

            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
                isPaused = !isPaused;
                messageText.setString(isPaused ? "Game is paused!" : "");
                if (!isPaused) {
                    addscoreNum = 0;
                    isGameOver = false;
                    branch.initialize();
                    player.isPlayerDead = false;
                    time.reset();
                    score = 0;
                    scoreStream.str("");
                    scoreStream << "Score = " << score;
                    scoreText.setString(scoreStream.str());
                    acceptInput = true;
                    flyingLogs.clear();
                }
            }
            if (acceptInput && !isPaused) {
                if ((event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Right) ||
                    (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right)) {
                    player.setPosition(1250, 750);
                    player.setScale(1, 1);
                    branch.setPlayerSide(Branch::BranchState::RIGHT);
                    branch.updateBranches(score);
                    axe.setPosition(1020, 830);
                    axe.setScale(1, 1);
                    axe.isAxeActive = true;
                    axe.isVisible = true;
                    //播放砍树音效
                    audio.playTimberAudio();
                    Log newLog;
                    newLog.setPosition(810, 750);
                    newLog.setOrgin(newLog.logSprite.getTexture()->getSize().x / 2, newLog.logSprite.getTexture()->getSize().y / 2);
                    newLog.logActive = true;
                    newLog.logSpeedX = -1000;
                    flyingLogs.push_back(newLog);
                    trunk.updateTrunk(time.dt.asSeconds());
                    time.addTime();
                    score++;
                    scoreStream.str("");
                    scoreStream << "Score = " << score;
                    scoreText.setString(scoreStream.str());
                }

                if ((event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Left) ||
                    (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)) {
                    player.setPosition(690, 750);
                    player.setScale(-1, 1);
                    branch.setPlayerSide(Branch::BranchState::LEFT);
                    branch.updateBranches(score);
                    axe.setPosition(880, 830);
                    axe.setScale(-1, 1);
                    axe.isAxeActive = true;
                    axe.isVisible = true;
                    audio.playTimberAudio();
                    Log newLog;
                    newLog.setPosition(810, 750);
                    newLog.setOrgin(newLog.logSprite.getTexture()->getSize().x / 2, newLog.logSprite.getTexture()->getSize().y / 2);
                    newLog.logActive = true;
                    newLog.logSpeedX = 1000;
                    flyingLogs.push_back(newLog);
                    trunk.updateTrunk(time.dt.asSeconds());
                    time.addTime();
                    score++;
                    scoreStream.str(""); scoreStream << "Score = " << score;
                    scoreText.setString(scoreStream.str());
                }
                
            }
        }

        if (isGameStarted && !isPaused && !isGameOver) {
            time.update();
            branch.update(time.dt.asSeconds());

            // 更新斧头显示时间
            if (axe.isVisible) {
                axe.axeVisibleTime += time.dt.asSeconds();
                if (axe.axeVisibleTime >= axe.AXE_VISIBLE_DURATION) {
                    axe.isVisible = false;
                    axe.axeVisibleTime = 0.0f;
                }
            }
            for (auto it = flyingLogs.begin(); it != flyingLogs.end();) {//存储飞出的树干
                if (it->logActive) {
                    it->logSprite.move(it->logSpeedX * time.dt.asSeconds(), it->logSpeedY * time.dt.asSeconds());
                    auto pos = it->logSprite.getPosition();
                    if (pos.x < -100 || pos.x > 2000 || pos.y < -100 || pos.y > 1200) {
                        it = flyingLogs.erase(it);
                        continue;
                    }
                }
                ++it;
            }

            if (!beeActive) {
                beeSpeed = static_cast<float>(dist(gen) % 100 + 50) / 5000.f;
                beeSprite.setPosition(2000, static_cast<float>(dist(gen) % 800 + 200));
                beeActive = true;
            }
            else {
                beeSprite.move(-beeSpeed, 0);
                if (beeSprite.getPosition().x < -100) beeActive = false;
            }

            if (!cloudActive) {
                cloudSpeed = static_cast<float>(dist(gen) % 10 + 50) / 5000.f;
                cloudSprite.setPosition(2000, static_cast<float>(dist(gen) % 400));
                cloudActive = true;
            }
            else {
                cloudSprite.move(-cloudSpeed, 0);
                if (cloudSprite.getPosition().x < -100) cloudActive = false;
            }
        }
        if (isGameStarted && (time.getTimeRemaining() <= 0 || branch.isGameOver())) {
            isGameOver = true;
            player.isPlayerDead = true;
            messageText.setString("Game Over!");
            isPaused = true;
            acceptInput = false;

            // 保存分数到数据库
            // 确保每次游戏结束都保存分数
            while (addscoreNum < 1) {
                db.addScore(score);
                ++addscoreNum;
            }
            
            recordPanel.updateRecords(db);
        }

        audio.playBackgroundMusic();

        window.clear();
        window.draw(backgroundSprite);
        window.draw(cloudSprite);
        trunk.showTrunk(window);
        tree2.showTree(window); tree3.showTree(window);
        underlog.showLog(window);
        if (!player.isPlayerDead) {
            for (const auto& log : flyingLogs)
                log.showLog(window);
        }

        if (!isGameStarted) {
            if (isInSettings) {
                settingPanel.draw(window);
            }
            else if (isInRecords) {
                recordPanel.draw(window);

                // 添加返回按钮
                Button backButton;
                backButton.init(font, "BACK", 50, sf::Vector2f(960, 850));
                backButton.draw(window);
            }
            else {
                startButton.draw(window);
                recordButton.draw(window);
                settingsButton.draw(window);
                exitButton.draw(window);
            }
        }
        else {
            if (!player.isPlayerDead) {
                player.showplayer(window);
                if (axe.isAxeActive) {
                    if (axe.isVisible) { // 只有当斧头可见时才渲染
                        axe.showAxe(window);
                    }
                }
                time.showTimeBar(window);
            }
            else {
                rip.showRip(window, player);
            }
            branch.draw(window);
            window.draw(beeSprite);
            window.draw(scoreText);
            if (isPaused) window.draw(messageText);
        }
        window.display();
    }
    return 0;
}