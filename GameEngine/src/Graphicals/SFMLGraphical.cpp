/*
** EPITECH PROJECT, 2025
** RRR-Type
** File description:
** SFMLGraphical
*/

#include "SFMLGraphical.hpp"


SFMLGraphical::TextureError::TextureError(std::string const &path)
{
    _message = "Failed to load texture: " + path;
}

const char *SFMLGraphical::TextureError::what() const noexcept
{
    return _message.c_str();
}


void SFMLGraphical::openWindow(std::string const &windowName)
{
    // _window.create(sf::VideoMode::getDesktopMode(), windowName, sf::Style::Fullscreen);
    _window.create(sf::VideoMode(800, 600), windowName, sf::Style::Default);
    _window.setFramerateLimit(60);
}

void SFMLGraphical::closeWindow()
{
    if (isWindowOpen()) {
        _window.close();
    }
}

bool SFMLGraphical::isWindowOpen()
{
    return _window.isOpen();
}

void SFMLGraphical::beginFrame()
{
    _window.clear(sf::Color::Black);
    updateEvents();
}

void SFMLGraphical::endFrame()
{
    _window.display();
}


uint32_t SFMLGraphical::addTexture(std::string const &path)
{
    auto texture = std::make_shared<sf::Texture>();

    if (!texture->loadFromFile(path)) {
        throw TextureError(path);
    }
    _textures.push_back(texture);

    return _textures.size() - 1;
}

std::vector<uint32_t> SFMLGraphical::addTextures(std::vector<std::string> const &paths)
{
    std::vector<uint32_t> indices;

    for (auto const &path : paths) {
        auto idx = addTexture(path);

        indices.push_back(idx);
    }

    return indices;
}

void SFMLGraphical::clearTextures()
{
    _textures.clear();
    _textures.shrink_to_fit();
}


void SFMLGraphical::drawSprite(comp::Position const &position, comp::Drawable const &drawable, comp::Animable &animable, uint64_t &elapsedMs)
{
    sf::Sprite sprite;
    sf::Vector2u textureSize = _textures[drawable.textureId]->getSize();
    float rectWidth = textureSize.x / animable.framesNumber;
    sf::IntRect rect(rectWidth * animable.currentFrame, 0, rectWidth, textureSize.y);

    if (animable.elapsedTimeMs >= animable.cooldownMs) {
        animable.currentFrame = (animable.currentFrame + 1) % animable.framesNumber;
        animable.elapsedTimeMs = 0;
    } else {
        animable.elapsedTimeMs += elapsedMs;
    }

    drawSprite(sprite, rect, position, drawable);
}

void SFMLGraphical::drawSprite(comp::Position const &position, comp::Drawable const &drawable)
{
    sf::Sprite sprite;
    sf::IntRect rect(0, 0, _textures[drawable.textureId]->getSize().x, _textures[drawable.textureId]->getSize().y);

    drawSprite(sprite, rect, position, drawable);
}

void SFMLGraphical::drawSprite(sf::Sprite &sprite, sf::IntRect &textureRect, comp::Position const &position, comp::Drawable const &drawable)
{
    if (!isTextureVisible({textureRect.width, textureRect.height}, {position.x, position.y})) {
        return;
    }

    sprite.setTexture(*_textures[drawable.textureId]);
    sprite.setTextureRect(textureRect);
    sprite.setOrigin(textureRect.width / 2, textureRect.height / 2);
    sprite.setPosition(position.x, position.y);
    sprite.setScale(drawable.scaleX, drawable.scaleY);
    sprite.setRotation(drawable.rotation);

    _window.draw(sprite);
}


void SFMLGraphical::drawBackground(comp::Drawable const &drawable)
{
    sf::Sprite sprite;
    sf::Vector2u textureSize = _textures[drawable.textureId]->getSize();
    std::pair<float, float> scale = {_window.getSize().x * 2 / textureSize.x, _window.getSize().y * 2 / textureSize.y};

    sprite.setTexture(*_textures[drawable.textureId]);
    sprite.setOrigin(textureSize.x / 2, textureSize.y / 2);
    sprite.setPosition(_window.getView().getCenter());
    sprite.setScale(scale.first, scale.second);

    _window.draw(sprite);
}


bool SFMLGraphical::isTextureVisible(std::pair<float, float> const &renderedSize, std::pair<float, float> const &center)
{
    sf::Vector2f viewCenter = _window.getView().getCenter();
    sf::Vector2f viewSize = _window.getView().getSize();

    sf::FloatRect textureBounds(center.first - renderedSize.first / 2.0f, center.second - renderedSize.second / 2.0f, renderedSize.first, renderedSize.second);
    sf::FloatRect viewBounds(viewCenter - viewSize / 2.0f, viewSize);

    return viewBounds.intersects(textureBounds);
}


void SFMLGraphical::setViewCenter(comp::Position const &position)
{
    sf::View view = _window.getView();
    view.setCenter(position.x, position.y);
    _window.setView(view);
}


void SFMLGraphical::updateEvents()
{
    sf::Event event;

    while (_window.pollEvent(event)) {
        switch (event.type) {

            case sf::Event::Closed: {
                closeWindow();
                break;
            }

            case sf::Event::Resized: {
                sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
                _window.setView(sf::View(visibleArea));
                break;
            }

            case sf::Event::KeyPressed: {
                auto key = _keysMap.find(event.key.code);
                if (key != _keysMap.end()) {
                    _keysState[key->second] = true;
                }
                break;
            }

            case sf::Event::KeyReleased: {
                auto key = _keysMap.find(event.key.code);
                if (key != _keysMap.end()) {
                    _keysState[key->second] = false;
                }
                break;
            }

            case sf::Event::MouseButtonPressed: {
                auto key = _mouseMap.find(event.mouseButton.button);
                if (key != _mouseMap.end()) {
                    _keysState[key->second] = true;
                }
                break;
            }

            case sf::Event::MouseButtonReleased: {
                auto key = _mouseMap.find(event.mouseButton.button);
                if (key != _mouseMap.end()) {
                    _keysState[key->second] = false;
                }
                break;
            }

            default: {
                break;
            }

        }
    }
}
