/*
** EPITECH PROJECT, 2025
** RRR-Type [WSL: Ubuntu]
** File description:
** AGraphical
*/

#ifndef AGRAPHICAL_HPP_
    #define AGRAPHICAL_HPP_

    #include <unordered_map>
    #include <vector>

    #include "Components.hpp"
    #include "Keys.hpp"

class AGraphical
{
    public:
        virtual ~AGraphical() = default;

        virtual void openWindow(std::string const &windowName) = 0;
        virtual void closeWindow() = 0;
        virtual bool isWindowOpen() = 0;
        virtual void beginFrame() = 0;
        virtual void endFrame() = 0;

        virtual uint32_t addTexture(std::string const &path) = 0;
        virtual std::vector<uint32_t> addTextures(std::vector<std::string> const &paths) = 0;
        virtual void clearTextures() = 0;

        virtual void drawSprite(comp::Position const &position, comp::Drawable const &drawable, comp::Animable &animable, uint64_t &elapsedMs) = 0;
        virtual void drawSprite(comp::Position const &position, comp::Drawable const &drawable) = 0;

        virtual void drawBackground(comp::Drawable const &drawable) = 0;

        virtual bool isTextureVisible(std::pair<float, float> const &renderedSize, std::pair<float, float> const &center) = 0;

        virtual void setViewCenter(comp::Position const &position) = 0;

        bool isKeyPressed(Keys key);

    protected:
        std::unordered_map<Keys, bool> _keysState = {
            {Keys::None, false},
            {Keys::Unknown, false},
            {Keys::A, false},
            {Keys::B, false},
            {Keys::C, false},
            {Keys::D, false},
            {Keys::E, false},
            {Keys::F, false},
            {Keys::G, false},
            {Keys::H, false},
            {Keys::I, false},
            {Keys::J, false},
            {Keys::K, false},
            {Keys::L, false},
            {Keys::M, false},
            {Keys::N, false},
            {Keys::O, false},
            {Keys::P, false},
            {Keys::Q, false},
            {Keys::R, false},
            {Keys::S, false},
            {Keys::T, false},
            {Keys::U, false},
            {Keys::V, false},
            {Keys::W, false},
            {Keys::X, false},
            {Keys::Y, false},
            {Keys::Z, false},
            {Keys::Num0, false},
            {Keys::Num1, false},
            {Keys::Num2, false},
            {Keys::Num3, false},
            {Keys::Num4, false},
            {Keys::Num5, false},
            {Keys::Num6, false},
            {Keys::Num7, false},
            {Keys::Num8, false},
            {Keys::Num9, false},
            {Keys::Escape, false},
            {Keys::LControl, false},
            {Keys::LShift, false},
            {Keys::LAlt, false},
            {Keys::LSystem, false},
            {Keys::RControl, false},
            {Keys::RShift, false},
            {Keys::RAlt, false},
            {Keys::RSystem, false},
            {Keys::Menu, false},
            {Keys::LBracket, false},
            {Keys::RBracket, false},
            {Keys::Semicolon, false},
            {Keys::Comma, false},
            {Keys::Period, false},
            {Keys::Quote, false},
            {Keys::Slash, false},
            {Keys::Backslash, false},
            {Keys::Tilde, false},
            {Keys::Equal, false},
            {Keys::Hyphen, false},
            {Keys::Space, false},
            {Keys::Enter, false},
            {Keys::Backspace, false},
            {Keys::Tab, false},
            {Keys::PageUp, false},
            {Keys::PageDown, false},
            {Keys::End, false},
            {Keys::Home, false},
            {Keys::Insert, false},
            {Keys::Delete, false},
            {Keys::Add, false},
            {Keys::Subtract, false},
            {Keys::Multiply, false},
            {Keys::Divide, false},
            {Keys::Left, false},
            {Keys::Right, false},
            {Keys::Up, false},
            {Keys::Down, false},
            {Keys::Numpad0, false},
            {Keys::Numpad1, false},
            {Keys::Numpad2, false},
            {Keys::Numpad3, false},
            {Keys::Numpad4, false},
            {Keys::Numpad5, false},
            {Keys::Numpad6, false},
            {Keys::Numpad7, false},
            {Keys::Numpad8, false},
            {Keys::Numpad9, false},
            {Keys::F1, false},
            {Keys::F2, false},
            {Keys::F3, false},
            {Keys::F4, false},
            {Keys::F5, false},
            {Keys::F6, false},
            {Keys::F7, false},
            {Keys::F8, false},
            {Keys::F9, false},
            {Keys::F10, false},
            {Keys::F11, false},
            {Keys::F12, false},
            {Keys::F13, false},
            {Keys::F14, false},
            {Keys::F15, false},
            {Keys::Pause, false},
            {Keys::MouseLeft, false},
            {Keys::MouseRight, false},
            {Keys::MouseMiddle, false},
            {Keys::MouseXButton1, false},
            {Keys::MouseXButton2, false}
        };

    private:
        virtual void updateEvents() = 0;
};

#endif /* !AGRAPHICAL_HPP_ */
