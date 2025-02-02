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
    #include "AGraphical.hpp"

class SFMLGraphical : public AGraphical
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
            _textures.shrink_to_fit();
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


    private:
        sf::RenderWindow _window;
        std::vector<sf::Texture> _textures;
        std::unordered_map<sf::Keyboard::Key, Keys> _keysMap = {
            {sf::Keyboard::Unknown, Keys::Unknown},
            {sf::Keyboard::A, Keys::A},
            {sf::Keyboard::B, Keys::B},
            {sf::Keyboard::C, Keys::C},
            {sf::Keyboard::D, Keys::D},
            {sf::Keyboard::E, Keys::E},
            {sf::Keyboard::F, Keys::F},
            {sf::Keyboard::G, Keys::G},
            {sf::Keyboard::H, Keys::H},
            {sf::Keyboard::I, Keys::I},
            {sf::Keyboard::J, Keys::J},
            {sf::Keyboard::K, Keys::K},
            {sf::Keyboard::L, Keys::L},
            {sf::Keyboard::M, Keys::M},
            {sf::Keyboard::N, Keys::N},
            {sf::Keyboard::O, Keys::O},
            {sf::Keyboard::P, Keys::P},
            {sf::Keyboard::Q, Keys::Q},
            {sf::Keyboard::R, Keys::R},
            {sf::Keyboard::S, Keys::S},
            {sf::Keyboard::T, Keys::T},
            {sf::Keyboard::U, Keys::U},
            {sf::Keyboard::V, Keys::V},
            {sf::Keyboard::W, Keys::W},
            {sf::Keyboard::X, Keys::X},
            {sf::Keyboard::Y, Keys::Y},
            {sf::Keyboard::Z, Keys::Z},
            {sf::Keyboard::Num0, Keys::Num0},
            {sf::Keyboard::Num1, Keys::Num1},
            {sf::Keyboard::Num2, Keys::Num2},
            {sf::Keyboard::Num3, Keys::Num3},
            {sf::Keyboard::Num4, Keys::Num4},
            {sf::Keyboard::Num5, Keys::Num5},
            {sf::Keyboard::Num6, Keys::Num6},
            {sf::Keyboard::Num7, Keys::Num7},
            {sf::Keyboard::Num8, Keys::Num8},
            {sf::Keyboard::Num9, Keys::Num9},
            {sf::Keyboard::Escape, Keys::Escape},
            {sf::Keyboard::LControl, Keys::LControl},
            {sf::Keyboard::LShift, Keys::LShift},
            {sf::Keyboard::LAlt, Keys::LAlt},
            {sf::Keyboard::LSystem, Keys::LSystem},
            {sf::Keyboard::RControl, Keys::RControl},
            {sf::Keyboard::RShift, Keys::RShift},
            {sf::Keyboard::RAlt, Keys::RAlt},
            {sf::Keyboard::RSystem, Keys::RSystem},
            {sf::Keyboard::Menu, Keys::Menu},
            {sf::Keyboard::LBracket, Keys::LBracket},
            {sf::Keyboard::RBracket, Keys::RBracket},
            {sf::Keyboard::Semicolon, Keys::Semicolon},
            {sf::Keyboard::Comma, Keys::Comma},
            {sf::Keyboard::Period, Keys::Period},
            {sf::Keyboard::Quote, Keys::Quote},
            {sf::Keyboard::Slash, Keys::Slash},
            {sf::Keyboard::Backslash, Keys::Backslash},
            {sf::Keyboard::Tilde, Keys::Tilde},
            {sf::Keyboard::Equal, Keys::Equal},
            {sf::Keyboard::Hyphen, Keys::Hyphen},
            {sf::Keyboard::Space, Keys::Space},
            {sf::Keyboard::Enter, Keys::Enter},
            {sf::Keyboard::Backspace, Keys::Backspace},
            {sf::Keyboard::Tab, Keys::Tab},
            {sf::Keyboard::PageUp, Keys::PageUp},
            {sf::Keyboard::PageDown, Keys::PageDown},
            {sf::Keyboard::End, Keys::End},
            {sf::Keyboard::Home, Keys::Home},
            {sf::Keyboard::Insert, Keys::Insert},
            {sf::Keyboard::Delete, Keys::Delete},
            {sf::Keyboard::Add, Keys::Add},
            {sf::Keyboard::Subtract, Keys::Subtract},
            {sf::Keyboard::Multiply, Keys::Multiply},
            {sf::Keyboard::Divide, Keys::Divide},
            {sf::Keyboard::Left, Keys::Left},
            {sf::Keyboard::Right, Keys::Right},
            {sf::Keyboard::Up, Keys::Up},
            {sf::Keyboard::Down, Keys::Down},
            {sf::Keyboard::Numpad0, Keys::Numpad0},
            {sf::Keyboard::Numpad1, Keys::Numpad1},
            {sf::Keyboard::Numpad2, Keys::Numpad2},
            {sf::Keyboard::Numpad3, Keys::Numpad3},
            {sf::Keyboard::Numpad4, Keys::Numpad4},
            {sf::Keyboard::Numpad5, Keys::Numpad5},
            {sf::Keyboard::Numpad6, Keys::Numpad6},
            {sf::Keyboard::Numpad7, Keys::Numpad7},
            {sf::Keyboard::Numpad8, Keys::Numpad8},
            {sf::Keyboard::Numpad9, Keys::Numpad9},
            {sf::Keyboard::F1, Keys::F1},
            {sf::Keyboard::F2, Keys::F2},
            {sf::Keyboard::F3, Keys::F3},
            {sf::Keyboard::F4, Keys::F4},
            {sf::Keyboard::F5, Keys::F5},
            {sf::Keyboard::F6, Keys::F6},
            {sf::Keyboard::F7, Keys::F7},
            {sf::Keyboard::F8, Keys::F8},
            {sf::Keyboard::F9, Keys::F9},
            {sf::Keyboard::F10, Keys::F10},
            {sf::Keyboard::F11, Keys::F11},
            {sf::Keyboard::F12, Keys::F12},
            {sf::Keyboard::F13, Keys::F13},
            {sf::Keyboard::F14, Keys::F14},
            {sf::Keyboard::F15, Keys::F15},
            {sf::Keyboard::Pause, Keys::Pause}
        };
        std::unordered_map<sf::Mouse::Button, Keys> _mouseMap = {
            {sf::Mouse::Left, Keys::MouseLeft},
            {sf::Mouse::Right, Keys::MouseRight},
            {sf::Mouse::Middle, Keys::MouseMiddle},
            {sf::Mouse::XButton1, Keys::MouseXButton1},
            {sf::Mouse::XButton2, Keys::MouseXButton2}
        };


        void updateEvents() override
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
                }
            }
        }

};

#endif /* !SFMLGRAPHICAL_HPP_ */
