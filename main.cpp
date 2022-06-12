#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<sstream>
#include"figure.hpp"
#include"circle.hpp"
#include"rect.hpp"
#include"line.hpp"


int main()
{
    std::vector<Figure*> figures;
    char operation[10];
    bool onExit{0};
    char fileName[100];
    std::string line;
    bool found = true;
    unsigned posAfterSVG{0};

    while (onExit != true)
    {
    std::cin >> operation;
    if (operation == "exit")
        onExit = true;
    else if (operation == "open")
    {
        std::cin >> fileName;
        std::ifstream file {fileName, std::ios::in};
        file.open(fileName,std::ios::in);
        if (!file.is_open())
        {
            std::cout << "Erorr when opening file!\n";
        }
        while(getline(file,line) || found == true)         //Used stackoverflow for this snippet of code for moving the cursor to where figures in svg file are
        {                                                 //
            if(line.find("<svg>",0) != std::string::npos) //
                found = true;                    
        }                                        
        posAfterSVG = file.tellg() + 1;
        found = false;
        while (getline(file, line) || found == true)
        {
            if(line.find("</svg>",0) != std::string::npos)
                found = true;
            else 
            {
                if(line.find("rect",0))
                {
                    std::string type = "rect";
                    std::stringstream stream(line);
                    
                    stream.seekg(line.find("x=", 0) + 3);
                    float x;
                    stream >> x;
                    
                    stream.seekg(line.find("y=", 0));
                    float y;
                    stream >> y;

                    stream.seekg(line.find("width=", 0));
                    float width;
                    stream >> width;

                    stream.seekg(line.find("heigth=", 0));
                    float heigth;
                    stream >> heigth;

                    stream.seekg(line.find("strokeWidth=", 0));
                    float strokeWidth;
                    stream >> strokeWidth;

                    unsigned FillPos1{line.find("fill=",0) + 6};
                    unsigned FillPos2{line.find('"', FillPos2) - 1};
                    char fill[FillPos2 - FillPos1 + 1];
                    line.copy(fill, FillPos2 - FillPos1, FillPos1);

                    unsigned StrokePos1{line.find("stroke=", 0) + 8};
                    unsigned StrokePos2{line.find('"', StrokePos1) - 1};
                    char stroke[StrokePos2 - StrokePos1 + 1];
                    line.copy(stroke, StrokePos2 - StrokePos1, StrokePos1);

                    Rectangle rect("rectangle", x, y, width, heigth, fill, stroke, strokeWidth);
                    figures.emplace_back(rect);
                }
                if(line.find("circle",0))
                {
                    std::string type = "circle";
                }
            }
        }
        for( auto i : figures )
            std::cout << i << "\n";
    }
    }
}