/*
** EPITECH PROJECT, 2025
** RRR-Type [WSL: Ubuntu]
** File description:
** IGraphical
*/

#ifndef IGRAPHICAL_HPP_
    #define IGRAPHICAL_HPP_

class IGraphical
{
    public:
        virtual ~IGraphical() = default;

        virtual bool isWindowOpen() = 0;
        virtual void beginFrame() = 0;
        virtual void endFrame() = 0;
        virtual void closeWindow() = 0;

    private:
        virtual void updateEvents() = 0;
};

#endif /* !IGRAPHICAL_HPP_ */
