#pragma once

#include <string>

class GuiBase{
    public:
        double x,y,width,height;
        bool visible;

        GuiBase();
};

class TextBox : public GuiBase{
    public:
        double fontScale;
        std::string text;

        TextBox(std::string text, double fontScale, double x, double y, double width, double height, bool visible);
};