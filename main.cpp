#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include<cstdio>
#include <memory>

#include "figure.hpp"
#include "circle.hpp"
#include "rect.hpp"
#include "line.hpp"

const unsigned MAX_SIZE = 25;

void create(std::vector<Figure*>& figures, bool& changes)
{
    std::cout << "\nFormat for Rectangle: type x y width height fill stroke stroke-width\nFormat for Circle:    type x y r fill stroke stroke-width\nFormat for Line:      type x1 y1 x2 y2 fill stroke stroke-width\n";
    std::string type;
    std::cin >> type;
    if (type == "rectangle")
    {
        float x;
        float y;
        float width;
        float height;
        char fill[MAX_SIZE];
        char stroke[MAX_SIZE];
        float strokeWidth;
        std::cin >> x >> y >> width >> height;
        std::cin.ignore();
        std::cin.getline(fill, MAX_SIZE, ' ');
        std::cin.getline(stroke, MAX_SIZE, ' ');
        std::cin >> strokeWidth;
        figures.push_back(new Rectangle("rectangle", x, y, width, height, fill, stroke, strokeWidth));
        changes = true;
        std::cout << "Successfully created a " << type << " (" << figures.size() << ") !\n";
    }
    else if (type == "circle")
    {
        float x;
        float y;
        float r;
        char fill[MAX_SIZE];
        char stroke[MAX_SIZE];
        float strokeWidth;
        std::cin >> x >> y >> r;
        std::cin.ignore();
        std::cin.getline(fill, MAX_SIZE, ' ');
        std::cin.getline(stroke, MAX_SIZE, ' ');
        std::cin >> strokeWidth;
        figures.push_back(new Circle("circle", x, y, r, fill, stroke, strokeWidth));
        changes = true;
        std::cout << "\nSuccessfully created a " << type << " (" << figures.size() << ") !\n";
    }
    else if (type == "line")
    {
        float x1;
        float y1;
        float x2;
        float y2;
        char fill[MAX_SIZE];
        char stroke[MAX_SIZE];
        float strokeWidth;
        std::cin >> x1 >> y1 >> x2 >> y2;
        std::cin.ignore();
        std::cin.getline(fill, MAX_SIZE, ' ');
        std::cin.getline(stroke, MAX_SIZE, ' ');
        std::cin >> strokeWidth;
        figures.push_back(new Line("line", x1, y1, x2, y2, fill, stroke, strokeWidth));
        changes = true;
        std::cout << "Successfully created a " << type << " (" << figures.size() << ") !\n";
    }
    else
        std::cout << "\nInvalid Figure!";
}

void erase(std::vector<Figure*>& figures, bool& changes, bool openFile)
{
    if(openFile == false)
    {
        std::cout << "No file is open!\n";
        std::cin.ignore();
    }
    else
    {
        int numberToErase{0};
        std::cin >> numberToErase;
        --numberToErase;
        if (numberToErase > figures.size())
        {
            std::cout << "\nThere is no figure " << numberToErase + 1 << "!\n";
        }
        else
        {
            std::cout << "\nErased a " << figures[numberToErase]->getType() << " (" << numberToErase + 1 << ") \n";
            changes = true;
            figures.erase(figures.begin() + numberToErase);
        }
    }
}

const void print(std::vector<Figure*> figures, bool openFile)
{
    if(openFile == false)
        std::cout << "No file is open!\n";
    else
        {
        if (figures.size() != 0)
        {
            for (size_t i = 0; i < figures.size(); i++)
            {
            std::cout << i + 1 << ". ";
            figures[i]->print();
            std::cout << std::endl;
            }
        }
        else
            std::cout << "There are no figures!\n";
    }
}

void close(std::string& fileName, std::vector<Figure*>& figures, bool& changes, bool& openFile)
{
    if(openFile == false)
        std::cout << "No file is open!\n";
    else
    {
        if (changes == true)
        {
            std::string YesNo;
            std::cout << "You have unsaved changes. Do you want to save them? (yes/no)\n";
            std::cin >> YesNo;
            if(YesNo == "yes")
            {
                std::ifstream file;
                std::string line;
                file.open(fileName, std::ios::in);
                std::ofstream outFile("temp.txt");
                if (!file.is_open())
                {
                    std::cout << "\nError when opening file!\n";
                }
                else
                {
                    bool foundSVG = false;
                    while (getline(file, line) && foundSVG == false)
                    {
                        if(line.find("<svg>",0) != std::string::npos)
                        {
                            outFile << "<svg>\n";
                            for (size_t i = 0; i < figures.size(); i++)
                            {
                                outFile << "<";
                                figures[i]->printForSaving(outFile);
                                outFile << " />\n";
                            }
                            outFile << "</svg>";
                            foundSVG = true;
                        }
                        else
                            outFile << line << std::endl;
                    }
                }
                file.close();
                outFile.close();
                char* fileN = new char[fileName.length() + 1];
                strcpy(fileN, fileName.c_str());
                remove(fileN);
                rename("temp.txt", fileN);
                delete[] fileN;
                openFile = false;
                std::cout << "Changes saved successfully!";
            }
        }
        fileName.clear();
        for(Figure* f : figures)
            delete f;
        figures.clear();
        std::cout<<"\nFile closed successfully!\n";
    }
}

void saveAs(std::string fileName, std::vector<Figure*>& figures)
{
    std::ofstream outFile;
    outFile.open(fileName);
    outFile << "<?xml version=" << '"' << "1.0" << '"' << " standalone=" << '"' << "no" << '"' << "?>\n"
            << "<!DOCTYPE svg PUBLIC " << '"' << "-//W3C//DTD SVG 1.1//EN" << '"' << "\n"
            << '"' << "http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd" << '"'
            << "\n<svg>\n";
    for (size_t i = 0; i < figures.size(); i++)
    {
        outFile << "<";
        figures[i]->printForSaving(outFile);
        outFile << " />\n";
    }
    outFile << "</svg>";
}

void save(std::string fileName, std::vector<Figure*>& figures, bool& changes, bool openFile)
{
    std::ifstream file;
    std::string line;
    file.open(fileName, std::ios::in);
    std::ofstream outFile("temp.txt");
    if(openFile == false)
        std::cout << "No file is open! If you created figures, use the command 'saveas'!\n";
    else
    {
        if (!file.is_open())
        {
            std::cout << "\nError when opening file!\n";
        }
        else
        {
            bool foundSVG = false;
            while (getline(file, line) && foundSVG == false)
            {
                if(line.find("<svg>",0) != std::string::npos)
                {
                    outFile << "<svg>\n";
                    for (size_t i = 0; i < figures.size(); i++)
                    {
                        outFile << "<";
                        figures[i]->printForSaving(outFile);
                        outFile << " />\n";
                    }
                    outFile << "</svg>";
                    foundSVG = true;
                }
                else
                    outFile << line << std::endl;
            }
        }
        file.close();
        outFile.close();
        char* fileN = new char[fileName.length() + 1];
        strcpy(fileN, fileName.c_str());
        remove(fileN);
        rename("temp.txt", fileN);
        delete[] fileN;
        changes = false;
    }
}

float convertToFloat(char* str)
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
    std::fstream file;
    bool changes{0};
    bool openFile{0};
    while (onExit != true)
    {
        std::cout << "\nEnter operation: ";
        std::cin >> operation;
        if (operation == "exit")
        {
            if(openFile == true)
            {
                std::string YesNo;
                std::cout << "There is an open file! You need to close it before you exit! Do you want to close it? (yes/no)\n";
                std::cin >> YesNo;
                if(YesNo == "yes")
                {
                    close(fileName, figures, changes,openFile);
                    openFile = false;
                }
            }
            for(auto f : figures)
                delete f;
            figures.clear();
            std::cout << "Goodbye! :)\n\n";
            onExit = true;
        }
        else if (operation == "open")
        {
            if(openFile == true)
            {
                std::string YesNo;
                std::cout << "There is another open file! You need to close it before you open another one! Do you want to close it? (yes/no)\n";
                std::cin >> YesNo;
                if(YesNo == "yes")
                {
                    close(fileName,figures,changes,openFile);
                    openFile = false;
                }
            }
            else
            {
                openFile = true;
                std::cin >> fileName;
                file.open(fileName, std::ios::in);
                if (!file.is_open())
                    std::cout << "Erorr when opening file!\n";
                else
                {
                    std::cout << "Successfully opened " << fileName << "!\n";
                    /* while (getline(file, line) && foundSVG == false)    // Used stackoverflow for this snippet of code for moving the cursor to where figures in svg file are
                    {                                                   //
                        if (line.find("<svg>", 0) != std::string::npos) //
                            foundSVG = true;
                    } */
                    bool foundSVG = false;
                    while (foundSVG == false)
                    {
                        //!!! line in line.find and getline(file,line) is different from the object 'line' !!!
                        if (line.find("</svg>", 0) != std::string::npos)
                            foundSVG = true;
                        else
                        {
                            if (line.find("rect", 0) != std::string::npos) // rectangle
                            {
                                std::string type = "rect";
    
                                char x[MAX_SIZE];
                                char y[MAX_SIZE];
                                char width[MAX_SIZE];
                                char heigth[MAX_SIZE];
                                char fill[MAX_SIZE];
                                char stroke[MAX_SIZE];
                                char strokeWidth[MAX_SIZE];
    
                                // X
                                size_t xPos1{line.find("x=", 0) + 3};
                                size_t xPos2{line.find('"', xPos1)};
                                size_t xPos{xPos2 - xPos1};
                                // char x[xPos + 1];
                                for (size_t i = 0; i < xPos + 1 && (line.find("x", 0) != std::string::npos); i++)
                                {
                                    x[i] = line[xPos1++];
                                }
                                x[xPos] = '\0';
    
                                // Y
                                size_t yPos1{line.find("y=", 0) + 3};
                                size_t yPos2{line.find('"', yPos1)};
                                size_t yPos{yPos2 - yPos1};
                                // char y[yPos + 1];
                                for (size_t i = 0; i < yPos + 1 && (line.find("y=", 0) != std::string::npos); i++)
                                {
                                    y[i] = line[yPos1++];
                                }
                                y[yPos] = '\0';
    
                                // Width
                                size_t widthPos1{line.find("width=", 0) + 7};
                                size_t widthPos2{line.find('"', widthPos1)};
                                size_t widthPos{widthPos2 - widthPos1};
                                // char width[widthPos +1];
                                for (size_t i = 0; i < widthPos + 1 && (line.find("width=", 0) != std::string::npos); i++)
                                {
                                    width[i] = line[widthPos1++];
                                }
                                width[widthPos] = '\0';
    
                                // Heigth
                                size_t heigthPos1{line.find("height=", 0) + 8};
                                size_t heigthPos2{line.find('"', heigthPos1)};
                                size_t heigthPos{heigthPos2 - heigthPos1};
                                // char heigth[heigthPos + 1];
                                for (size_t i = 0; i < heigthPos + 1 && (line.find("height=", 0) != std::string::npos); i++)
                                {
                                    heigth[i] = line[heigthPos1++];
                                }
                                heigth[heigthPos] = '\0';
    
                                if (line.find("fill", 0) != std::string::npos)
                                {
                                    // Fill
                                    size_t FillPos1{line.find("fill=", 0) + 6};
                                    size_t FillPos2{line.find('"', FillPos1)};
                                    size_t FillPos{FillPos2 - FillPos1};
                                    // char fill[FillPos + 1];
                                    for (size_t i = 0; i < FillPos + 1 && (line.find("fill=", 0) != std::string::npos); i++)
                                    {
                                        fill[i] = line[FillPos1++];
                                    }
                                    fill[FillPos] = '\0';
                                    // line.copy(fill, FillPos2 - FillPos1, FillPos1);
                                }
                                else
                                    strcpy(fill, "none");
    
                                if (line.find("stroke=", 0) != std::string::npos)
                                {
                                    // Stroke
                                    size_t StrokePos1{line.find("stroke=", 0) + 8};
                                    size_t StrokePos2{line.find('"', StrokePos1)};
                                    size_t StrokePos{StrokePos2 - StrokePos1};
                                    // char stroke[StrokePos + 1];
                                    for (size_t i = 0; i < StrokePos + 1 && (line.find("stroke=", 0) != std::string::npos); i++)
                                    {
                                        stroke[i] = line[StrokePos1++];
                                    }
                                    stroke[StrokePos] = '\0';
                                    // line.copy(stroke, StrokePos2 - StrokePos1, StrokePos1);
                                }
                                else
                                    strcpy(stroke, "none");
    
                                if (line.find("stroke-width=", 0) != std::string::npos)
                                {
                                    // StrokeWidth
                                    size_t strokeWidthPos1{line.find("stroke-width=", 0) + 14};
                                    size_t strokeWidthPos2{line.find('"', strokeWidthPos1)};
                                    size_t strokeWidthPos{strokeWidthPos2 - strokeWidthPos1};
                                    // char strokeWidth[strokeWidthPos + 1];
                                    for (size_t i = 0; i < strokeWidthPos + 1 && (line.find("stroke-width", 0) != std::string::npos); i++)
                                    {
                                        strokeWidth[i] = line[strokeWidthPos1++];
                                    }
                                    strokeWidth[strokeWidthPos] = '\0';
                                }
                                else
                                    strcpy(strokeWidth, "0");
    
                                // Rectangle rect("rectangle", convertToFloat(x), convertToFloat(y), convertToFloat(width), convertToFloat(heigth), fill, stroke, convertToFloat(strokeWidth));
                                figures.push_back(new Rectangle("rectangle", convertToFloat(x), convertToFloat(y), convertToFloat(width), convertToFloat(heigth), fill, stroke, convertToFloat(strokeWidth)));
                            }
    
                            else if (line.find("circle", 0) != std::string::npos) // circle
                            {
                                char x[MAX_SIZE];
                                char y[MAX_SIZE];
                                char r[MAX_SIZE];
                                char fill[MAX_SIZE];
                                char stroke[MAX_SIZE];
                                char strokeWidth[MAX_SIZE];
                                std::string type = "circle";
    
                                // X
                                size_t xPos1{line.find("x=", 0) + 3};
                                size_t xPos2{line.find('"', xPos1)};
                                size_t xPos{xPos2 - xPos1};
                                // char x[xPos + 1];
                                for (size_t i = 0; i < xPos + 1 && (line.find("x=", 0) != std::string::npos); i++)
                                {
                                    x[i] = line[xPos1++];
                                }
                                x[xPos] = '\0';
    
                                // Y
                                size_t yPos1{line.find("y=", 0) + 3};
                                size_t yPos2{line.find('"', yPos1)};
                                size_t yPos{yPos2 - yPos1};
                                // char y[yPos + 1];
                                for (size_t i = 0; i < yPos + 1 && (line.find("y=", 0) != std::string::npos); i++)
                                {
                                    y[i] = line[yPos1++];
                                }
                                y[yPos] = '\0';
    
                                // R
                                size_t rPos1{line.find("r=", 0) + 3};
                                size_t rPos2{line.find('"', rPos1)};
                                size_t rPos{rPos2 - rPos1};
                                // char r[rPos + 1];
                                for (size_t i = 0; i < rPos + 1 && (line.find("r=", 0) != std::string::npos); i++)
                                {
                                    r[i] = line[rPos1++];
                                }
                                r[rPos] = '\0';
    
                                if (line.find("fill", 0) != std::string::npos)
                                {
                                    // Fill
                                    size_t FillPos1{line.find("fill=", 0) + 6};
                                    size_t FillPos2{line.find('"', FillPos1)};
                                    size_t FillPos{FillPos2 - FillPos1};
                                    // char fill[FillPos + 1];
                                    for (size_t i = 0; i < FillPos + 1 && (line.find("fill=", 0) != std::string::npos); i++)
                                    {
                                        fill[i] = line[FillPos1++];
                                    }
                                    fill[FillPos] = '\0';
                                }
                                else
                                    strcpy(fill, "none");
    
                                if (line.find("stroke", 0) != std::string::npos)
                                {
                                    // Stroke
                                    size_t StrokePos1{line.find("stroke=", 0) + 8};
                                    size_t StrokePos2{line.find('"', StrokePos1)};
                                    size_t StrokePos{StrokePos2 - StrokePos1};
                                    // char stroke[StrokePos + 1];
                                    for (size_t i = 0; i < StrokePos + 1 && (line.find("stroke=", 0) != std::string::npos); i++)
                                    {
                                        stroke[i] = line[StrokePos1++];
                                    }
                                    stroke[StrokePos] = '\0';
                                }
                                else
                                    strcpy(stroke, "none");
    
                                if (line.find("stroke-width=", 0) != std::string::npos)
                                {
                                    // StrokeWidth
                                    size_t strokeWidthPos1{line.find("stroke-width=", 0) + 14};
                                    size_t strokeWidthPos2{line.find('"', strokeWidthPos1)};
                                    size_t strokeWidthPos{strokeWidthPos2 - strokeWidthPos1};
                                    // char strokeWidth[strokeWidthPos + 1];
                                    for (size_t i = 0; i < strokeWidthPos + 1 && (line.find("stroke-width=", 0) != std::string::npos); i++)
                                    {
                                        strokeWidth[i] = line[strokeWidthPos1++];
                                    }
                                    strokeWidth[strokeWidthPos] = '\0';
                                }
                                else
                                    strcpy(strokeWidth, "0");
    
                                // Circle circ("circle", convertToFloat(x), convertToFloat(y), convertToFloat(r), fill, stroke, convertToFloat(strokeWidth));
                                figures.push_back(new Circle("circle", convertToFloat(x), convertToFloat(y), convertToFloat(r), fill, stroke, convertToFloat(strokeWidth)));
                            }
                            else if (line.find("line", 0) != std::string::npos) // line
                            {
                                std::string type = "line";
    
                                char x1[MAX_SIZE];
                                char y1[MAX_SIZE];
                                char x2[MAX_SIZE];
                                char y2[MAX_SIZE];
                                char fill[MAX_SIZE];
                                char stroke[MAX_SIZE];
                                char strokeWidth[MAX_SIZE];
    
                                // X1
                                size_t x1Pos1{line.find("x1=", 0) + 4};
                                size_t x1Pos2{line.find('"', x1Pos1)};
                                size_t x1Pos{x1Pos2 - x1Pos1};
                                // char x1[x1Pos + 1];
                                for (size_t i = 0; i < x1Pos + 1 && (line.find("x1=", 0) != std::string::npos); i++)
                                {
                                    x1[i] = line[x1Pos1++];
                                }
                                x1[x1Pos] = '\0';
    
                                // Y1
                                size_t y1Pos1{line.find("y1=", 0) + 4};
                                size_t y1Pos2{line.find('"', y1Pos1)};
                                size_t y1Pos{y1Pos2 - y1Pos1};
                                // char y1[y1Pos + 1];
                                for (size_t i = 0; i < y1Pos + 1 && (line.find("y1=", 0) != std::string::npos); i++)
                                {
                                    y1[i] = line[y1Pos1++];
                                }
                                y1[y1Pos] = '\0';
    
                                // X2
                                size_t x2Pos1{line.find("x2=", 0) + 4};
                                size_t x2Pos2{line.find('"', x2Pos1)};
                                size_t x2Pos{x2Pos2 - x2Pos1};
                                // char x2[x2Pos + 1];
                                for (size_t i = 0; i < x2Pos + 1 && (line.find("x2=", 0) != std::string::npos); i++)
                                {
                                    x2[i] = line[x2Pos1++];
                                }
                                x2[x2Pos] = '\0';
    
                                // Y2
                                size_t y2Pos1{line.find("y2=", 0) + 4};
                                size_t y2Pos2{line.find('"', y2Pos1)};
                                size_t y2Pos{y2Pos2 - y2Pos1};
                                // char y2[y2Pos + 1];
                                for (size_t i = 0; i < y2Pos + 1 && (line.find("y2=", 0) != std::string::npos); i++)
                                {
                                    y2[i] = line[y2Pos1++];
                                }
                                y2[y2Pos] = '\0';
    
                                if (line.find("fill", 0) != std::string::npos)
                                {
                                    // Fill
                                    size_t FillPos1{line.find("fill=", 0) + 6};
                                    size_t FillPos2{line.find('"', FillPos1)};
                                    size_t FillPos{FillPos2 - FillPos1};
                                    // char fill[FillPos + 1];
                                    for (size_t i = 0; i < FillPos + 1 && (line.find("fill=", 0) != std::string::npos); i++)
                                    {
                                        fill[i] = line[FillPos1++];
                                    }
                                    fill[FillPos] = '\0';
                                }
                                else
                                    strcpy(fill, "none");
    
                                if (line.find("stroke", 0) != std::string::npos)
                                {
                                    // Stroke
                                    size_t StrokePos1{line.find("stroke=", 0) + 8};
                                    size_t StrokePos2{line.find('"', StrokePos1)};
                                    size_t StrokePos{StrokePos2 - StrokePos1};
                                    // char stroke[StrokePos + 1];
                                    for (size_t i = 0; i < StrokePos + 1 && (line.find("stroke=", 0) != std::string::npos); i++)
                                    {
                                        stroke[i] = line[StrokePos1++];
                                    }
                                    stroke[StrokePos] = '\0';
                                }
                                else
                                    strcpy(stroke, "none");
    
                                if (line.find("stroke-width=", 0) != std::string::npos)
                                {
                                    // StrokeWidth
                                    size_t strokeWidthPos1{line.find("stroke-width=", 0) + 14};
                                    size_t strokeWidthPos2{line.find('"', strokeWidthPos1)};
                                    size_t strokeWidthPos{strokeWidthPos2 - strokeWidthPos1};
                                    // char strokeWidth[strokeWidthPos + 1];
                                    for (size_t i = 0; i < strokeWidthPos + 1 && (line.find("stroke-width=", 0) != std::string::npos); i++)
                                    {
                                        strokeWidth[i] = line[strokeWidthPos1++];
                                    }
                                    strokeWidth[strokeWidthPos] = '\0';
                                }
                                else
                                    strcpy(strokeWidth, "0");
    
                                // Line lin("line", convertToFloat(x1), convertToFloat(y1), convertToFloat(x2), convertToFloat(y2), fill, stroke, convertToFloat(strokeWidth));
                                figures.push_back(new Line("line", convertToFloat(x1), convertToFloat(y1), convertToFloat(x2), convertToFloat(y2), fill, stroke, convertToFloat(strokeWidth)));
                            }
                        }
                        getline(file, line);
                    }
                    file.close();
                }
            }
        }
        else if (operation == "print")
        {
            print(figures, openFile);
        }
        else if (operation == "erase")
        {
            erase(figures,changes, openFile);
        }
        else if (operation == "create")
        {
            create(figures, changes);
        }
        else if (operation == "save")
        {
            save(fileName, figures, changes, openFile);
        }
        else if (operation == "close")
        {
            close(fileName, figures, changes, openFile);
        }
        else if (operation == "help")
        {
            std::cout << "\nopen <file>      opens <file>\n"
                      << "\nclose            closes currently opened file\n"
                      << "\nsave             saves the currently open file\n"
                      << "\nsaveas <file>    saves the currently open file in <file>\n"
                      << "\nprint            prints information about all figures\n"
                      << "\ncreate           creates a new figure\n"
                      << "\nerase <n>        erases figure with number <n>\n"
                      << "\ntranslate [<n>]  translates figure with number <n> or all figures if <n> is not declared\n"
                      << "\nhelp             prints this information\n"
                      << "\nabout            prints information about creator\n"
                      << "\nexit             exits this program\n\n";
        }
        
        
        
        
        //TODO: translate operation == stringstream horizontal= vertical=
    }
}