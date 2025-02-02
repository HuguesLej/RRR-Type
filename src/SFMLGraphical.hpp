/*
** EPITECH PROJECT, 2025
** RRR-Type [WSL: Ubuntu]
** File description:
** SFMLGraphical
*/

#ifndef SFMLGRAPHICAL_HPP_
    #define SFMLGRAPHICAL_HPP_

    #include <exception>
    #include <SFML/Graphics.hpp>
    #include "IGraphical.hpp"

class SFMLGraphical : public IGraphical
{
    public:

        class TextureError : public std::exception
        {
            public:
                TextureError(std::string const &path)
                {
                    _message = "Failed to load texture: " + path;
                }
                ~TextureError() noexcept override = default;

                const char *what() const noexcept override
                {
                    return _message.c_str();
                }

            private:
                std::string _message;
        };

        SFMLGraphical() = default;
        SFMLGraphical(const SFMLGraphical &) = delete;
        SFMLGraphical &operator=(const SFMLGraphical &) = delete;
        ~SFMLGraphical() = default;


        void openWindow(std::string const &windowName) override
        {
            // _window.create(sf::VideoMode::getDesktopMode(), windowName, sf::Style::Fullscreen);
            _window.create(sf::VideoMode(800, 600), windowName, sf::Style::Default);
            _window.setFramerateLimit(60);
        }

        void closeWindow() override
        {
            if (isWindowOpen()) {
                _window.close();
            }
        }

        bool isWindowOpen() override
        {
            return _window.isOpen();
        }

        void beginFrame()
        {
            _window.clear(sf::Color::Black);
            updateEvents();
        }

        void endFrame()
        {
            _window.display();
        }


        std::uint32_t addTexture(std::string const &path) override
        {
            sf::Texture texture;

            if (!texture.loadFromFile(path)) {
                throw TextureError(path);
            }
            _textures.push_back(texture);

            return _textures.size() - 1;
        }

        std::vector<std::uint32_t> addTextures(std::vector<std::string> const &paths) override
        {
            std::vector<std::uint32_t> indices;

            for (auto const &path : paths) {
                auto idx = addTexture(path);

                indices.push_back(idx);
            }

            return indices;
        }

        void clearTextures() override
        {
            _textures.clear();
        }


        void drawSprite(comp::Position const &position, comp::Drawable const &drawable, comp::Animable &animable) override
        {
            sf::Sprite sprite;
            sf::Vector2u textureSize = _textures[drawable.textureId].getSize();
            float rectWidth = textureSize.x / animable.framesNumber;
            sf::IntRect rect(rectWidth * animable.currentFrame, 0, rectWidth, textureSize.y);

            animable.currentFrame = (animable.currentFrame + 1) % animable.framesNumber;

            sprite.setTexture(_textures[drawable.textureId]);
            sprite.setTextureRect(rect);
            sprite.setPosition(position.x, position.y);
            sprite.setScale(drawable.scaleX, drawable.scaleY);
            sprite.setRotation(drawable.rotation);

            _window.draw(sprite);
        }

        void drawSprite(comp::Position const &position, comp::Drawable const &drawable) override
        {
            sf::Sprite sprite;

            sprite.setTexture(_textures[drawable.textureId]);
            sprite.setPosition(position.x, position.y);
            sprite.setScale(drawable.scaleX, drawable.scaleY);
            sprite.setRotation(drawable.rotation);

            _window.draw(sprite);
        }


    protected:
    private:
        sf::RenderWindow _window;
        std::vector<sf::Texture> _textures;

        void updateEvents() override
        {
            sf::Event event;

            while (_window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    closeWindow();
            }
        }
};

#endif /* !SFMLGRAPHICAL_HPP_ */
