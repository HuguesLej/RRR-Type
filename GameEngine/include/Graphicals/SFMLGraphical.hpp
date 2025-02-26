/*
** EPITECH PROJECT, 2025
** RRR-Type [WSL: Ubuntu]
** File description:
** SFMLGraphical
*/

#ifndef SFMLGRAPHICAL_HPP_
    #define SFMLGRAPHICAL_HPP_

    #include <exception>
    #include <memory>
    #include <SFML/Graphics.hpp>

    #include "AGraphical.hpp"

class SFMLGraphical : public AGraphical
{
    public:

        class TextureError : public std::exception
        {
            public:
                TextureError(std::string const &path);
                ~TextureError() noexcept override = default;

                const char *what() const noexcept override;

            private:
                std::string _message;
        };


        SFMLGraphical() = default;
        SFMLGraphical(const SFMLGraphical &) = delete;
        SFMLGraphical &operator=(const SFMLGraphical &) = delete;
        ~SFMLGraphical() = default;


        void openWindow(std::string const &windowName) override;
        void closeWindow() override;
        bool isWindowOpen() override;
        void beginFrame() override;
        void endFrame() override;

        uint32_t addTexture(std::string const &path) override;
        std::vector<uint32_t> addTextures(std::vector<std::string> const &paths) override;
        void clearTextures() override;

        void drawSprite(comp::Position const &position, comp::Drawable const &drawable, comp::Animable &animable, uint64_t &elapsedMs) override;
        void drawSprite(comp::Position const &position, comp::Drawable const &drawable) override;

        void drawBackground(comp::Drawable const &drawable) override;

        bool isTextureVisible(std::pair<float, float> const &renderedSize, std::pair<float, float> const &center) override;

        void setViewCenter(comp::Position const &position) override;

    private:
        sf::RenderWindow _window;
        std::vector<std::shared_ptr<sf::Texture>> _textures;

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


        void drawSprite(sf::Sprite &sprite, sf::IntRect &textureRect, comp::Position const &position, comp::Drawable const &drawable);

        void updateEvents() override;
};

#endif /* !SFMLGRAPHICAL_HPP_ */
