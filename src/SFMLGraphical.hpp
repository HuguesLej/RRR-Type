/*
** EPITECH PROJECT, 2025
** RRR-Type [WSL: Ubuntu]
** File description:
** SFMLGraphical
*/

#ifndef SFMLGRAPHICAL_HPP_
    #define SFMLGRAPHICAL_HPP_

    #include <SFML/Graphics.hpp>
    #include "IGraphical.hpp"

class SFMLGraphical : public IGraphical
{
    public:
        SFMLGraphical(std::string windowName = "SFML Window")
        {
            // _window.create(sf::VideoMode::getDesktopMode(), windowName, sf::Style::Fullscreen);
            _window.create(sf::VideoMode(800, 600), windowName, sf::Style::Default);
            _window.setFramerateLimit(60);
        }
        SFMLGraphical(const SFMLGraphical &) = delete;
        SFMLGraphical &operator=(const SFMLGraphical &) = delete;
        ~SFMLGraphical() = default;

        void beginFrame()
        {
            _window.clear(sf::Color::Black);
            updateEvents();
        }

        void endFrame()
        {
            _window.display();
        }

        bool isWindowOpen() override
        {
            return _window.isOpen();
        }

        void closeWindow() override
        {
            if (isWindowOpen()) {
                _window.close();
            }
        }

    protected:
    private:
        sf::RenderWindow _window;

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
