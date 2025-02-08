/*
** EPITECH PROJECT, 2025
** RRR-Type
** File description:
** Keys
*/

#include "Keys.hpp"

std::ostream &operator<<(std::ostream &os, const Keys &key)
{
    switch (key) {
        case Keys::None: os << "None"; break;
        case Keys::Unknown: os << "Unknown"; break;
        case Keys::A: os << "A"; break;
        case Keys::B: os << "B"; break;
        case Keys::C: os << "C"; break;
        case Keys::D: os << "D"; break;
        case Keys::E: os << "E"; break;
        case Keys::F: os << "F"; break;
        case Keys::G: os << "G"; break;
        case Keys::H: os << "H"; break;
        case Keys::I: os << "I"; break;
        case Keys::J: os << "J"; break;
        case Keys::K: os << "K"; break;
        case Keys::L: os << "L"; break;
        case Keys::M: os << "M"; break;
        case Keys::N: os << "N"; break;
        case Keys::O: os << "O"; break;
        case Keys::P: os << "P"; break;
        case Keys::Q: os << "Q"; break;
        case Keys::R: os << "R"; break;
        case Keys::S: os << "S"; break;
        case Keys::T: os << "T"; break;
        case Keys::U: os << "U"; break;
        case Keys::V: os << "V"; break;
        case Keys::W: os << "W"; break;
        case Keys::X: os << "X"; break;
        case Keys::Y: os << "Y"; break;
        case Keys::Z: os << "Z"; break;
        case Keys::Num0: os << "Num0"; break;
        case Keys::Num1: os << "Num1"; break;
        case Keys::Num2: os << "Num2"; break;
        case Keys::Num3: os << "Num3"; break;
        case Keys::Num4: os << "Num4"; break;
        case Keys::Num5: os << "Num5"; break;
        case Keys::Num6: os << "Num6"; break;
        case Keys::Num7: os << "Num7"; break;
        case Keys::Num8: os << "Num8"; break;
        case Keys::Num9: os << "Num9"; break;
        case Keys::Escape: os << "Escape"; break;
        case Keys::LControl: os << "LControl"; break;
        case Keys::LShift: os << "LShift"; break;
        case Keys::LAlt: os << "LAlt"; break;
        case Keys::LSystem: os << "LSystem"; break;
        case Keys::RControl: os << "RControl"; break;
        case Keys::RShift: os << "RShift"; break;
        case Keys::RAlt: os << "RAlt"; break;
        case Keys::RSystem: os << "RSystem"; break;
        case Keys::Menu: os << "Menu"; break;
        case Keys::LBracket: os << "LBracket"; break;
        case Keys::RBracket: os << "RBracket"; break;
        case Keys::Semicolon: os << "Semicolon"; break;
        case Keys::Comma: os << "Comma"; break;
        case Keys::Period: os << "Period"; break;
        case Keys::Quote: os << "Quote"; break;
        case Keys::Slash: os << "Slash"; break;
        case Keys::Backslash: os << "Backslash"; break;
        case Keys::Tilde: os << "Tilde"; break;
        case Keys::Equal: os << "Equal"; break;
        case Keys::Hyphen: os << "Hyphen"; break;
        case Keys::Space: os << "Space"; break;
        case Keys::Enter: os << "Enter"; break;
        case Keys::Backspace: os << "Backspace"; break;
        case Keys::Tab: os << "Tab"; break;
        case Keys::PageUp: os << "PageUp"; break;
        case Keys::PageDown: os << "PageDown"; break;
        case Keys::End: os << "End"; break;
        case Keys::Home: os << "Home"; break;
        case Keys::Insert: os << "Insert"; break;
        case Keys::Delete: os << "Delete"; break;
        case Keys::Add: os << "Add"; break;
        case Keys::Subtract: os << "Subtract"; break;
        case Keys::Multiply: os << "Multiply"; break;
        case Keys::Divide: os << "Divide"; break;
        case Keys::Left: os << "Left"; break;
        case Keys::Right: os << "Right"; break;
        case Keys::Up: os << "Up"; break;
        case Keys::Down: os << "Down"; break;
        case Keys::Numpad0: os << "Numpad0"; break;
        case Keys::Numpad1: os << "Numpad1"; break;
        case Keys::Numpad2: os << "Numpad2"; break;
        case Keys::Numpad3: os << "Numpad3"; break;
        case Keys::Numpad4: os << "Numpad4"; break;
        case Keys::Numpad5: os << "Numpad5"; break;
        case Keys::Numpad6: os << "Numpad6"; break;
        case Keys::Numpad7: os << "Numpad7"; break;
        case Keys::Numpad8: os << "Numpad8"; break;
        case Keys::Numpad9: os << "Numpad9"; break;
        case Keys::F1: os << "F1"; break;
        case Keys::F2: os << "F2"; break;
        case Keys::F3: os << "F3"; break;
        case Keys::F4: os << "F4"; break;
        case Keys::F5: os << "F5"; break;
        case Keys::F6: os << "F6"; break;
        case Keys::F7: os << "F7"; break;
        case Keys::F8: os << "F8"; break;
        case Keys::F9: os << "F9"; break;
        case Keys::F10: os << "F10"; break;
        case Keys::F11: os << "F11"; break;
        case Keys::F12: os << "F12"; break;
        case Keys::F13: os << "F13"; break;
        case Keys::F14: os << "F14"; break;
        case Keys::F15: os << "F15"; break;
        case Keys::Pause: os << "Pause"; break;
        case Keys::MouseLeft: os << "MouseLeft"; break;
        case Keys::MouseRight: os << "MouseRight"; break;
        case Keys::MouseMiddle: os << "MouseMiddle"; break;
        case Keys::MouseXButton1: os << "MouseXButton1"; break;
        case Keys::MouseXButton2: os << "MouseXButton2"; break;
    }

    return os;
}
