#include"Game.h"
//#include <iostream>


void Game::initGame() {
    m_window = new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Arkanoid game");
    createIcon();

    map = new Map(WINDOW_WIDTH, WINDOW_HEIGHT);
    paddle = new Paddle(WINDOW_WIDTH, WINDOW_HEIGHT - PADDING_BOTTOM, Parameters::PADDLE_WIDTH, Parameters::PADDLE_HEIGHT);
    ball = new Ball(WINDOW_HEIGHT - PADDING_BOTTOM, WINDOW_WIDTH, Parameters::BALL_WIDTH, Parameters::BALL_HEIGHT);
    bonus = new Bonus(Parameters::BONUS_WIDTH, Parameters::BONUS_HEIGHT);

    loadBackground();
    createIcon();
    createFont();
    createScore();
    createLives();
}

void Game::createScore() {
    score = new Score(*font, Parameters::SCORE_FONT);
    score->setPosition(WINDOW_WIDTH - WINDOW_WIDTH * 0.3, PADDING_TOP / 4);
    score->setPosition(PADDING_LR, PADDING_TOP / 4);
}

void Game::createIcon() {
    sf::Image icon;
    icon.loadFromFile("images/icon1.png");
    m_window->setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
}

void Game::createFont() {
    font = new sf::Font();
    font->loadFromFile("images\\1.otf");
}

void Game::createLives() {
    for (int i = 0;i < LIVES;i++) {
        lives.emplace_back(new Live((WINDOW_WIDTH - PADDING_LR * 3) - (i*LIVES_SIZE + i * Parameters::LIVES_COUNT), PADDING_TOP, LIVES_SIZE, LIVES_SIZE));
    }
}

void Game::loadBackground() {
    texture.loadFromFile("images\\back2.jpg");
    sf::Vector2u size = texture.getSize();
    sprite.setTexture(texture);
    sprite.setScale(Parameters::BACKGROUND_SCALE, Parameters::BACKGROUND_SCALE);
}

void Game::checkWinStatus() {
    if (map->getCurrentBlockCount() == 0) {
        status = WIN;
        win();
    }
}

void Game::runGame() {

    sf::Clock clock;
    m_window->setFramerateLimit(Parameters::FRAMERATE);
    status = START;
    ball->stickPadle(*paddle);
    while (m_window->isOpen()) {

        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time = time / Parameters::FREQUENCY;

        sf::Event event;
        m_window->pollEvent(event);
        if (event.type == sf::Event::Closed)
            m_window->close();

        keyPressProcessing();
        if (status != GAME_OVER && status != WIN) {

            ballProcessing();
            if (status != GAME_OVER)
                drawProcessing(time);
            checkWinStatus();
        }

    }
}

void Game::drawProcessing(float time) {
    m_window->clear();
    m_window->draw(sprite);
    bonusManage(time);
    paddle->update(time, *bonus);
    paddle->drawObject(m_window);
    map->drawingMap(m_window, time);
    ball->drawObject(m_window);
    if (secondBall) secondBall->drawObject(m_window);
    if (additionalLife) bottom->drawObject(m_window);
    for (int i = 0;i < LIVES;i++) {
        lives.at(i)->drawingLive(m_window);
    }
    score->update();
    m_window->draw(*score);
    m_window->display();
}

void Game::ballProcessing() {
    if (status == RUN) {
        ball->setState(true);
        if (secondBall) secondBall->setState(true);
    }
    if (secondBall) { ball->checkAnotherBallCollision(*secondBall); }
    if (!ball->moveBall(*paddle, *map, *bonus, *score, WINDOW_WIDTH, WINDOW_HEIGHT)) {
        if (additionalLife) saveLifeBonus();
        else {
            if (secondBall) {
                ball->copy(*secondBall);
                delete(secondBall);
                secondBall = nullptr;
            }
            else {
                status = FAIL;
                fail();
            }
        }
    }
    if (secondBall) {
        secondBall->checkAnotherBallCollision(*ball);
        if (!secondBall->moveBall(*paddle, *map, *bonus, *score, WINDOW_WIDTH, WINDOW_HEIGHT)) {
            delete(secondBall);
            secondBall = nullptr;

        }
    }
    if (ball->getState() == Ball::STEAK) { status = STEAK; }
}


void Game::keyPressProcessing() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        if ((paddle->getX()) - Parameters::PADDLE_PADDING >= 0) {
            paddle->direction = Parameters::LEFT;
            paddle->setSpeed(Parameters::PADDLE_SPEED);
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        if ((paddle->getX() + paddle->getWidth() + Parameters::PADDLE_PADDING) <= WINDOW_WIDTH) {
            paddle->direction = Parameters::RIGHT;
            paddle->setSpeed(Parameters::PADDLE_SPEED);
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        if (status == FAIL || status == START || status == STEAK) {
            status = RUN;
        }
    }
}


void Game::bonusProcessing() {
    bool runBonus = true;
    if (!bonus->isRun()) {
        bonus->inMove = true;
        switch ((bonus->getBonusType())) {

        case Bonus::CHANGE_PADLE_SIZE:
            paddle->bonusActive();
            switch (getRandomNumber(0, 1)) {
            case 0: paddle->changeSize(1);  break;
            case 1: paddle->changeSize(-1); break;
            default: break;
            }
            break;

        case Bonus::CHANGE_BALL_SPEED:
            ball->bonusActive();
            switch (getRandomNumber(0, 1)) {
            case 0: ball->changeSpeed(1);  break;
            case 1:  ball->changeSpeed(-1); break;
            default: break;
            }
            break;

        case Bonus::STICK_BALL:
            paddle->bonusActive();
            paddle->isSteak = true;
            break;

        case Bonus::CHANCE:
            additionalLife = true;
            bottom = new Bottom(0, (paddle->getY() + paddle->getHeight() + 5), WINDOW_WIDTH, Parameters::BOTTOM_HEIGHT);
            runBonus = false;
            bonus->fail();
            break;

        case Bonus::MOVING_BLOCK:
            if (!map->moveBlock) {
                map->addMoveBlock();
                bonus->fail();
            }
            runBonus = false;
            break;

        case Bonus::SECOND_BALL:
            if (!secondBall) {
                secondBall = new Ball(WINDOW_HEIGHT - PADDING_BOTTOM, WINDOW_WIDTH, Parameters::BALL_WIDTH, Parameters::BALL_HEIGHT);
                bonus->fail();
                secondBall->stickPadle(*paddle);
            }
            runBonus = false;
            break;
        }
    }
    if (runBonus) { bonus->runBonus(); }
}

void Game::gameOver() {
    this->gameOverText = new sf::Text("Game Over", *font, Parameters::GAME_OVER_FONT_SIZE);
    this->gameOverText->setOrigin(sf::Vector2f(this->gameOverText->getGlobalBounds().width / 2, this->gameOverText->getGlobalBounds().height / 2));
    this->gameOverText->setPosition(sf::Vector2f(m_window->getSize().x / 2, m_window->getSize().y / 2));
    drawMessage(gameOverText);
}

void Game::win() {
    this->winText = new sf::Text("You win!", *font, Parameters::WIN_FONT_SIZE);
    this->winText->setOrigin(sf::Vector2f(this->winText->getGlobalBounds().width / 2, this->winText->getGlobalBounds().height / 2));
    this->winText->setPosition(sf::Vector2f(m_window->getSize().x / 2, m_window->getSize().y / 2));
    drawMessage(winText);
}

void Game::bonusManage(float time) {
    if (bonus->isExist()) {
        activateBonus();
        bonus->update(time);
        if (!(bonus->isActiv())) {
            bonus->drawObject(m_window);
        }
        else {
            bonusProcessing();
        }
    }
}

void Game::activateBonus() {
    if (bonus->getRect().intersects(paddle->getRect())) {
        bonus->activate();
        bonus->inMove = false;
    }
    else if (bonus->getY() >= WINDOW_HEIGHT) {
        bonus->fail();
        bonus->deleteBonus();
    }
}

bool Game::saveLifeBonus() {
    if (additionalLife) {
        ball->changeVDirection();
        additionalLife = false;
        bonus->fail();
        return 1;
    }
    else
        return 0;
}

void Game::drawMessage(sf::Text *text) {
    sf::Color color(250, 128, 114);
    text->setPosition(text->getPosition().x, text->getPosition().y);
    text->setFillColor(sf::Color::Black);
    m_window->draw(*text);
    text->setPosition(text->getPosition().x + 5, text->getPosition().y + 5);
    text->setFillColor(color);
    m_window->draw(*text);
    m_window->display();
}

void Game::fail() {
    livesCount--;
    lives.at(LIVES - livesCount - 1)->failLive();
    score->incrementScore(Parameters::FAIL_SCORE);
    if (livesCount == 0) {
        gameOver();
        status = GAME_OVER;
    }
}