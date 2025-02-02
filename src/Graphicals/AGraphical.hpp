/*
** EPITECH PROJECT, 2025
** RRR-Type [WSL: Ubuntu]
** File description:
** AGraphical
*/

#ifndef AGRAPHICAL_HPP_
    #define AGRAPHICAL_HPP_

    #include <cstdint>
    #include <unordered_map>
    #include <vector>
    #include "../Components/Components.hpp"
    #include "../Keys.hpp"

class AGraphical
{
    public:
        virtual ~AGraphical() = default;

        virtual void openWindow(std::string const &windowName) = 0;
        virtual void closeWindow() = 0;
        virtual bool isWindowOpen() = 0;
        virtual void beginFrame() = 0;
        virtual void endFrame() = 0;

        virtual std::uint32_t addTexture(std::string const &path) = 0;
        virtual std::vector<std::uint32_t> addTextures(std::vector<std::string> const &paths) = 0;
        virtual void clearTextures() = 0;

        virtual void drawSprite(comp::Position const &position, comp::Drawable const &drawable, comp::Animable &animable) = 0;
        virtual void drawSprite(comp::Position const &position, comp::Drawable const &drawable) = 0;

        bool isKeyPressed(Keys key)
        {
            return _keysState[key];
        }

    protected:
        std::unordered_map<Keys, bool> _keysState = {
            {Unknown, false},
            {A, false},
            {B, false},
            {C, false},
            {D, false},
            {E, false},
            {F, false},
            {G, false},
            {H, false},
            {I, false},
            {J, false},
            {K, false},
            {L, false},
            {M, false},
            {N, false},
            {O, false},
            {P, false},
            {Q, false},
            {R, false},
            {S, false},
            {T, false},
            {U, false},
            {V, false},
            {W, false},
            {X, false},
            {Y, false},
            {Z, false},
            {Num0, false},
            {Num1, false},
            {Num2, false},
            {Num3, false},
            {Num4, false},
            {Num5, false},
            {Num6, false},
            {Num7, false},
            {Num8, false},
            {Num9, false},
            {Escape, false},
            {LControl, false},
            {LShift, false},
            {LAlt, false},
            {LSystem, false},
            {RControl, false},
            {RShift, false},
            {RAlt, false},
            {RSystem, false},
            {Menu, false},
            {LBracket, false},
            {RBracket, false},
            {Semicolon, false},
            {Comma, false},
            {Period, false},
            {Quote, false},
            {Slash, false},
            {Backslash, false},
            {Tilde, false},
            {Equal, false},
            {Hyphen, false},
            {Space, false},
            {Enter, false},
            {Backspace, false},
            {Tab, false},
            {PageUp, false},
            {PageDown, false},
            {End, false},
            {Home, false},
            {Insert, false},
            {Delete, false},
            {Add, false},
            {Subtract, false},
            {Multiply, false},
            {Divide, false},
            {Left, false},
            {Right, false},
            {Up, false},
            {Down, false},
            {Numpad0, false},
            {Numpad1, false},
            {Numpad2, false},
            {Numpad3, false},
            {Numpad4, false},
            {Numpad5, false},
            {Numpad6, false},
            {Numpad7, false},
            {Numpad8, false},
            {Numpad9, false},
            {F1, false},
            {F2, false},
            {F3, false},
            {F4, false},
            {F5, false},
            {F6, false},
            {F7, false},
            {F8, false},
            {F9, false},
            {F10, false},
            {F11, false},
            {F12, false},
            {F13, false},
            {F14, false},
            {F15, false},
            {Pause, false},
            {MouseLeft, false},
            {MouseRight, false},
            {MouseMiddle, false},
            {MouseXButton1, false},
            {MouseXButton2, false}
        };

    private:
        virtual void updateEvents() = 0;
};

#endif /* !AGRAPHICAL_HPP_ */
