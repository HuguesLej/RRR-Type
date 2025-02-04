/*
** EPITECH PROJECT, 2025
** RRR-Type [WSL: Ubuntu]
** File description:
** Keys
*/

#ifndef KEYS_HPP_
    #define KEYS_HPP_

    #include <iostream>

enum Keys
{
    None,
    Unknown,
    A,
    B,
    C,
    D,
    E,
    F,
    G,
    H,
    I,
    J,
    K,
    L,
    M,
    N,
    O,
    P,
    Q,
    R,
    S,
    T,
    U,
    V,
    W,
    X,
    Y,
    Z,
    Num0,
    Num1,
    Num2,
    Num3,
    Num4,
    Num5,
    Num6,
    Num7,
    Num8,
    Num9,
    Escape,
    LControl,
    LShift,
    LAlt,
    LSystem,
    RControl,
    RShift,
    RAlt,
    RSystem,
    Menu,
    LBracket,
    RBracket,
    Semicolon,
    Comma,
    Period,
    Quote,
    Slash,
    Backslash,
    Tilde,
    Equal,
    Hyphen,
    Space,
    Enter,
    Backspace,
    Tab,
    PageUp,
    PageDown,
    End,
    Home,
    Insert,
    Delete,
    Add,
    Subtract,
    Multiply,
    Divide,
    Left,
    Right,
    Up,
    Down,
    Numpad0,
    Numpad1,
    Numpad2,
    Numpad3,
    Numpad4,
    Numpad5,
    Numpad6,
    Numpad7,
    Numpad8,
    Numpad9,
    F1,
    F2,
    F3,
    F4,
    F5,
    F6,
    F7,
    F8,
    F9,
    F10,
    F11,
    F12,
    F13,
    F14,
    F15,
    Pause,
    MouseLeft,
    MouseRight,
    MouseMiddle,
    MouseXButton1,
    MouseXButton2
};

std::ostream &operator<<(std::ostream &os, const Keys &key)
{
    switch (key) {
        case None: os << "None"; break;
        case Unknown: os << "Unknown"; break;
        case A: os << "A"; break;
        case B: os << "B"; break;
        case C: os << "C"; break;
        case D: os << "D"; break;
        case E: os << "E"; break;
        case F: os << "F"; break;
        case G: os << "G"; break;
        case H: os << "H"; break;
        case I: os << "I"; break;
        case J: os << "J"; break;
        case K: os << "K"; break;
        case L: os << "L"; break;
        case M: os << "M"; break;
        case N: os << "N"; break;
        case O: os << "O"; break;
        case P: os << "P"; break;
        case Q: os << "Q"; break;
        case R: os << "R"; break;
        case S: os << "S"; break;
        case T: os << "T"; break;
        case U: os << "U"; break;
        case V: os << "V"; break;
        case W: os << "W"; break;
        case X: os << "X"; break;
        case Y: os << "Y"; break;
        case Z: os << "Z"; break;
        case Num0: os << "Num0"; break;
        case Num1: os << "Num1"; break;
        case Num2: os << "Num2"; break;
        case Num3: os << "Num3"; break;
        case Num4: os << "Num4"; break;
        case Num5: os << "Num5"; break;
        case Num6: os << "Num6"; break;
        case Num7: os << "Num7"; break;
        case Num8: os << "Num8"; break;
        case Num9: os << "Num9"; break;
        case Escape: os << "Escape"; break;
        case LControl: os << "LControl"; break;
        case LShift: os << "LShift"; break;
        case LAlt: os << "LAlt"; break;
        case LSystem: os << "LSystem"; break;
        case RControl: os << "RControl"; break;
        case RShift: os << "RShift"; break;
        case RAlt: os << "RAlt"; break;
        case RSystem: os << "RSystem"; break;
        case Menu: os << "Menu"; break;
        case LBracket: os << "LBracket"; break;
        case RBracket: os << "RBracket"; break;
        case Semicolon: os << "Semicolon"; break;
        case Comma: os << "Comma"; break;
        case Period: os << "Period"; break;
        case Quote: os << "Quote"; break;
        case Slash: os << "Slash"; break;
        case Backslash: os << "Backslash"; break;
        case Tilde: os << "Tilde"; break;
        case Equal: os << "Equal"; break;
        case Hyphen: os << "Hyphen"; break;
        case Space: os << "Space"; break;
        case Enter: os << "Enter"; break;
        case Backspace: os << "Backspace"; break;
        case Tab: os << "Tab"; break;
        case PageUp: os << "PageUp"; break;
        case PageDown: os << "PageDown"; break;
        case End: os << "End"; break;
        case Home: os << "Home"; break;
        case Insert: os << "Insert"; break;
        case Delete: os << "Delete"; break;
        case Add: os << "Add"; break;
        case Subtract: os << "Subtract"; break;
        case Multiply: os << "Multiply"; break;
        case Divide: os << "Divide"; break;
        case Left: os << "Left"; break;
        case Right: os << "Right"; break;
        case Up: os << "Up"; break;
        case Down: os << "Down"; break;
        case Numpad0: os << "Numpad0"; break;
        case Numpad1: os << "Numpad1"; break;
        case Numpad2: os << "Numpad2"; break;
        case Numpad3: os << "Numpad3"; break;
        case Numpad4: os << "Numpad4"; break;
        case Numpad5: os << "Numpad5"; break;
        case Numpad6: os << "Numpad6"; break;
        case Numpad7: os << "Numpad7"; break;
        case Numpad8: os << "Numpad8"; break;
        case Numpad9: os << "Numpad9"; break;
        case F1: os << "F1"; break;
        case F2: os << "F2"; break;
        case F3: os << "F3"; break;
        case F4: os << "F4"; break;
        case F5: os << "F5"; break;
        case F6: os << "F6"; break;
        case F7: os << "F7"; break;
        case F8: os << "F8"; break;
        case F9: os << "F9"; break;
        case F10: os << "F10"; break;
        case F11: os << "F11"; break;
        case F12: os << "F12"; break;
        case F13: os << "F13"; break;
        case F14: os << "F14"; break;
        case F15: os << "F15"; break;
        case Pause: os << "Pause"; break;
        case MouseLeft: os << "MouseLeft"; break;
        case MouseRight: os << "MouseRight"; break;
        case MouseMiddle: os << "MouseMiddle"; break;
        case MouseXButton1: os << "MouseXButton1"; break;
        case MouseXButton2: os << "MouseXButton2"; break;
    }

    return os;
}

#endif /* !KEYS_HPP_ */
