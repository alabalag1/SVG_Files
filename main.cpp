#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<sstream>

#include"figure.hpp"
#include"circle.hpp"
#include"rect.hpp"
#include"line.hpp"

float convertToFloat(std::string str)
{
    std::stringstream stream;
    stream << str;
    float buffer;
    stream >> buffer;
    return buffer;
}

int main()
{
    std::vector<Figure*> figures;
    std::string operation;
    bool onExit{0};
    std::string fileName;
    std::string line;
    bool found = false;

    while (onExit != true)
    {
        std::cout << "Enter operation: ";
        std::cin >> operation;
        if (operation == "exit")
            onExit = true;
        else if (operation == "open")
        {
            std::cin >> fileName;
            std::ifstream file{"figures.svg", std::ios::in};
            if (!file.is_open())
            {
                std::cout << "Erorr when opening file!\n";
            }
            while (getline(file, line) && found == false)       // Used stackoverflow for this snippet of code for moving the cursor to where figures in svg file are
            {                                                   //
                if (line.find("<svg>", 0) != std::string::npos) //
                    found = true;
            }
            found = false;
            while (found == false)
            {
                if (line.find("</svg>", 0) != std::string::npos)
                    found = true;
                else
                {
                    if (line.find("rect", 0) != std::string::npos)
                    {
                        std::string type = "rect";

                        //X
                        size_t xPos1{line.find("x=", 0) + 3};
                        size_t xPos2{line.find('"', xPos1)};
                        size_t xPos{xPos2 - xPos1};
                        char x[xPos + 1];
                        for (size_t i = 0; i < xPos + 1 && (line.find("x",0) != std::string::npos); i++)
                        {
                            x[i] = line[xPos1++];
                        }
                        x[xPos] = '\0';

                        //Y
                        size_t yPos1{line.find("y", 0) + 3};
                        size_t yPos2{line.find('"', yPos1)};
                        size_t yPos{yPos2 - yPos1};
                        char y[yPos + 1];
                        for (size_t i = 0; i < yPos + 1 && (line.find("y",0)!=std::string::npos); i++)
                        {
                            y[i] = line[yPos1++];
                        }
                        y[yPos] = '\0';
                        
                        //Width
                        size_t widthPos1{line.find("width", 0) + 7};
                        size_t widthPos2{line.find('"', widthPos1)};
                        size_t widthPos{widthPos2 - widthPos1};
                        char width[widthPos +1];
                        for (size_t i = 0; i < widthPos + 1 && (line.find("width",0)!=std::string::npos); i++)
                        {
                            width[i] = line[widthPos1++];
                        }
                        width[widthPos] = '\0';

                        //Heigth
                        size_t heigthPos1{line.find("height", 0) + 8};
                        size_t heigthPos2{line.find('"', heigthPos1)};
                        size_t heigthPos{heigthPos2 - heigthPos1};
                        char heigth[heigthPos + 1];
                        for (size_t i = 0; i < heigthPos + 1 && (line.find("height",0)!=std::string::npos); i++)
                        {
                            heigth[i] = line[heigthPos1++];
                        }
                        heigth[heigthPos] = '\0';
 
                        //Fill
                        size_t FillPos1{line.find("fill", 0) + 6};
                        size_t FillPos2{line.find('"', FillPos1)};
                        size_t FillPos{FillPos2 - FillPos1};
                        char fill[FillPos + 1];
                        for (size_t i = 0; i < FillPos + 1 && (line.find("fill",0)!=std::string::npos); i++)
                        {
                            fill[i] = line[FillPos1++];
                        }
                        fill[FillPos] = '\0';
                        //line.copy(fill, FillPos2 - FillPos1, FillPos1);

                        //Stroke
                        size_t StrokePos1{line.find("stroke", 0) + 8};
                        size_t StrokePos2{line.find('"', StrokePos1)};
                        size_t StrokePos{StrokePos2 - StrokePos1};
                        char stroke[StrokePos + 1];
                        for (size_t i = 0; i < StrokePos + 1 && (line.find("stroke",0)!=std::string::npos); i++)
                        {
                            stroke[i] = line[StrokePos1++];
                        }
                        stroke[StrokePos] = '\0';
                        //line.copy(stroke, StrokePos2 - StrokePos1, StrokePos1);

                        //StrokeWidth
                        size_t strokeWidthPos1{line.find("stroke-width", 0) + 14};
                        size_t strokeWidthPos2{line.find('"', strokeWidthPos1) - 1};
                        size_t strokeWidthPos{strokeWidthPos2 - strokeWidthPos1};
                        char strokeWidth[strokeWidthPos + 1];
                        for (size_t i = 0; i < strokeWidthPos + 1 && (line.find("stroke-width",0)!=std::string::npos); i++)
                        {
                            strokeWidth[i] = line[strokeWidthPos1++];
                        }
                        strokeWidth[strokeWidthPos] = '\0';


                        Rectangle *rect = new Rectangle("rectangle", convertToFloat(x), convertToFloat(y), convertToFloat(width), convertToFloat(heigth), fill, stroke, convertToFloat(strokeWidth));
                        figures.push_back(rect);
                    }
                    if (line.find("circle", 0) != std::string::npos)
                    {
                        std::string type = "circle";
                    }
                }
                getline(file, line);
            }
            for (auto i = 0; i < figures.size(); i++)
                std::cout << figures[i].Figure::print() << "\n";
            onExit = true;
        }
    }
}