/*
** EPITECH PROJECT, 2025
** RRR-Type [WSL: Ubuntu]
** File description:
** IGraphical
*/

#ifndef IGRAPHICAL_HPP_
    #define IGRAPHICAL_HPP_

    #include <cstdint>
    #include <vector>
    #include "Components/Components.hpp"

class IGraphical
{
    public:
        virtual ~IGraphical() = default;

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

    private:
        virtual void updateEvents() = 0;
};

#endif /* !IGRAPHICAL_HPP_ */
