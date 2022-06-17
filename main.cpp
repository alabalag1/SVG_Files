///SVG_Files Georgi Krastev 2022
///https://github.com/alabalag1/SVG_Files


#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <cstdio>
#include <memory>

#include "figure.hpp"
#include "circle.hpp"
#include "rect.hpp"
#include "line.hpp"

const unsigned MAX_SIZE = 25;

void find(std::string search, char *destination, std::string source) ///Searchs for a Figure keyword and saves its value in a local variable
{
    size_t Pos1{source.find(search, 0) + search.length() + 1}; 
    size_t Pos2{source.find('"', Pos1)};
    size_t Pos{Pos2 - Pos1};
    for (size_t i = 0; i < Pos + 1 && source.find(search, 0) != std::string::npos; i++)
    {
        destination[i] = source[Pos1++];
    }
    destination[Pos] = '\0';
}

void create(std::vector<Figure *> &figures, bool &changes) ///Creates a Figure by user input
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
    {
        std::cout << "\nInvalid Figure!";
        std::cin.ignore(1024, '\n');
    }
}

void erase(std::vector<Figure *> &figures, bool &changes, bool openFile) ///Erases a figure by a consecutive number, entered by the user
{
    if (openFile == false)
    {
        std::cout << "No file is open!\n";
        std::cin.ignore(1024,'\n');
    }
    else
    {
        unsigned numberToErase{0};
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

void print(std::vector<Figure *> figures) ///Prints all figures, which are opened from file or created by the user
{
    if (figures.empty() == false)
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

void close(std::string &fileName, std::vector<Figure *> &figures, bool &changes, bool &openFile) ///Closes opened file
{
    if (openFile == false)
        std::cout << "No file is open!\n";
    else if (changes == true)
    {
        std::string YesNo;
        std::cout << "You have unsaved changes. Do you want to save them? (yes/no): ";
        std::cin >> YesNo;
        if (YesNo == "yes")
        {
            std::ifstream file;
            std::string line;
            file.open(fileName, std::ios::in);
            std::ofstream outFile("temp.txt");
            bool foundSVG = false;
            while (getline(file, line) && foundSVG == false)
            {
                if (line.find("<svg>", 0) != std::string::npos)
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
            file.close();
            outFile.close();
            char *fileN = new char[fileName.length() + 1];
            strcpy(fileN, fileName.c_str());
            remove(fileN);
            rename("temp.txt", fileN);
            delete[] fileN;
            std::cout << "Changes saved successfully!";
            std::cout << "\nFile " << '"' << fileName << '"' <<" closed successfully!\n";
        }
    }
    for (size_t i = 0; i < figures.size(); i++)
        delete figures[i];
    figures.clear();
    openFile = false;
    std::cout << "\nFile " << '"' << fileName << '"' <<" closed successfully!\n";
    fileName.erase(fileName.begin(),fileName.end());
}

void saveAs(std::string fileName, std::vector<Figure *> figures, bool &openFile, bool &changes) ///Saves all figures in a file, which name is by user input
{
    std::ofstream outFile;
    outFile.open(fileName, std::ios::out);
    outFile << "<?xml version=" << '"' << "1.0" << '"' << " standalone=" << '"' << "no" << '"' << "?>\n"
            << "<!DOCTYPE svg PUBLIC " << '"' << "-//W3C//DTD SVG 1.1//EN" << '"' << "\n"
            << '"' << "http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd" << '"'
            << ">\n<svg>\n";
    for (size_t i = 0; i < figures.size(); i++)
    {
        outFile << "<";
        figures[i]->printForSaving(outFile);
        outFile << " />\n";
    }
    outFile << "</svg>";
    outFile.close();
    openFile = true;
    changes = false;
    std::cout << "File " << '"' << fileName << '"' << " saved successfully!";
}

void save(std::string fileName, std::vector<Figure *> figures, bool &changes, bool openFile) ///Saves all figures in the currently opened file
{
    std::ifstream file;
    std::string line;
    file.open(fileName, std::ios::in);
    std::ofstream outFile("temp.txt");
    if (openFile == false)
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
                if (line.find("<svg>", 0) != std::string::npos)
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
        char *fileN = new char[fileName.length() + 1];
        strcpy(fileN, fileName.c_str());
        remove(fileN);
        rename("temp.txt", fileN);
        delete[] fileN;
        changes = false;
        std::cout << "File " << '"' << fileName << '"' << " saved successfully!";
    }
}

float convertToFloat(char *str) ///Converts string to float
{
    std::stringstream stream;
    stream << str;
    float buffer;
    stream >> buffer;
    return buffer;
}

int main()
{
    ///A vector of pointers to Figure objects was used to store all the figures that are created or read and later saved in a file.
    ///If a normal Figure object was used instead of a pointer to Figure object for the vector, there would be object slicing.
    std::vector<Figure *> figures;
    std::string operation;
    bool onExit{0};
    std::string fileName;
    std::string line;
    std::fstream file;
    bool changes{0};
    bool openFile{0};
    while (std::cin && onExit != true)
    {
        std::cout << "\nEnter operation: ";
        std::cin >> operation;
        if (operation == "exit")
        {
            if (openFile == true)
            {
                std::string YesNo;
                std::cout << "\nThere is an open file! You need to close it before you exit! Do you want to close it? (yes/no): ";
                std::cin >> YesNo;
                if (YesNo == "yes")
                {
                    close(fileName, figures, changes, openFile);
                    openFile = false;
                    for (auto f : figures)
                        delete f;
                    figures.clear();
                    std::cout << "Goodbye! :)\n\n";
                    onExit = true;
                }
            }
            else
            {
                for (auto f : figures)
                    delete f;
                figures.clear();
                std::cout << "\nGoodbye! :)\n\n";
                onExit = true;
            }
        }
        else if (operation == "open") //Open isn't in its own void function because other functions couldn't be used
        {
            if (openFile == true)
            {
                std::cin.ignore(1024, '\n');
                std::string YesNo;
                std::cout << "There is another open file! You need to close it before you open another one! Do you want to close it? (yes/no): ";
                std::cin >> YesNo;
                if (YesNo == "yes")
                {
                    close(fileName, figures, changes, openFile);
                    openFile = false;
                }
            }
            else
            {
                std::cin >> fileName;
                file.open(fileName, std::ios::in);
                if (!file.is_open())
                {
                    std::cout << "Erorr when opening file!\n";
                    openFile = false;
                }
                else
                {
                    std::cout << "Successfully opened " << '"' << fileName << '"' << "!\n";
                    openFile = true;
                    bool foundSVG = false;
                    line.clear();
                    while (foundSVG == false) ///Line by line searching
                    {
                        //!!! line in line.find and getline(file,line) is different from the object 'Line' !!!
                        if (line.find("</svg>", 0) != std::string::npos) ///Used stackoverflow for this snippet of code for finding where figures' code starts
                            foundSVG = true;
                        else
                        {
                            if (line.find("rect", 0) != std::string::npos) ///Searching for rectangles in the file
                            {
                                char x[MAX_SIZE];
                                char y[MAX_SIZE];
                                char width[MAX_SIZE];
                                char heigth[MAX_SIZE];
                                char fill[MAX_SIZE];
                                char stroke[MAX_SIZE];
                                char strokeWidth[MAX_SIZE];

                                //X
                                find("x=", x, line);

                                //Y
                                find("y=", y, line);

                                //Width
                                find("width=", width, line);

                                //Height
                                find("height=", heigth, line);

                                //Fill
                                if (line.find("fill=", 0) != std::string::npos)
                                    find("fill=", fill, line);
                                else
                                    strcpy(fill, "none");

                                //Stroke
                                if (line.find("stroke=", 0) != std::string::npos)
                                    find("stroke=", stroke, line);
                                else
                                    strcpy(stroke, "none");

                                //Stroke-Width
                                if (line.find("stroke-width=", 0) != std::string::npos)
                                    find("stroke-width=", strokeWidth, line);
                                else
                                    strcpy(strokeWidth, "0");

                                figures.push_back(new Rectangle("rectangle", convertToFloat(x), convertToFloat(y), convertToFloat(width), convertToFloat(heigth), fill, stroke, convertToFloat(strokeWidth)));
                            }

                            else if (line.find("circle", 0) != std::string::npos) ///Searching for circles in the file
                            {
                                char x[MAX_SIZE];
                                char y[MAX_SIZE];
                                char r[MAX_SIZE];
                                char fill[MAX_SIZE];
                                char stroke[MAX_SIZE];
                                char strokeWidth[MAX_SIZE];

                                //X
                                find("x=", x, line);
                                
                                //Y
                                find("y=", y, line);

                                //R
                                find("r=", r, line);

                                //Fill
                                if (line.find("fill", 0) != std::string::npos)
                                    find("fill=", fill, line);
                                else
                                    strcpy(fill, "none");

                                //Stroke
                                if (line.find("stroke", 0) != std::string::npos)
                                    find("stroke=", stroke, line);
                                else
                                    strcpy(stroke, "none");

                                //Stroke-Width
                                if (line.find("stroke-width=", 0) != std::string::npos)
                                    find("stroke-width=", strokeWidth, line);
                                else
                                    strcpy(strokeWidth, "0");

                                figures.push_back(new Circle("circle", convertToFloat(x), convertToFloat(y), convertToFloat(r), fill, stroke, convertToFloat(strokeWidth)));
                            }
                            else if (line.find("line", 0) != std::string::npos) ///Searching for lines in the file
                            {
                                char x1[MAX_SIZE];
                                char y1[MAX_SIZE];
                                char x2[MAX_SIZE];
                                char y2[MAX_SIZE];
                                char fill[MAX_SIZE];
                                char stroke[MAX_SIZE];
                                char strokeWidth[MAX_SIZE];

                                //X1
                                find("x1=",x1,line);

                                //Y1
                                find("y1=",y1,line);

                                // X2
                                find("x2=", x2, line);

                                //Y2
                                find("y2=", y2, line);

                                //Fill
                                if (line.find("fill", 0) != std::string::npos)
                                    find("fill=", fill, line);
                                else
                                    strcpy(fill, "none");

                                //Stroke
                                if (line.find("stroke", 0) != std::string::npos)
                                    find("stroke=", stroke, line);
                                else
                                    strcpy(stroke, "none");

                                //Stroke-Width
                                if (line.find("stroke-width=", 0) != std::string::npos)
                                    find("stroke-width=", strokeWidth, line);
                                else
                                    strcpy(strokeWidth, "0");

                                figures.push_back(new Line("line", convertToFloat(x1), convertToFloat(y1), convertToFloat(x2), convertToFloat(y2), fill, stroke, convertToFloat(strokeWidth)));
                            }
                        }
                        getline(file, line); ///Line by line searching
                    }
                    file.close();
                }
            }
        }
        else if (operation == "print")
        {
            print(figures);
        }
        else if (operation == "erase")
        {
            erase(figures, changes, openFile);
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
        else if (operation == "saveas")
        {
            std::string fileN;
            std::cin >> fileN;
            saveAs(fileN, figures, openFile, changes);
        }
        else if (operation == "translate") ///Translates figure
        {
            if (figures.size() != 0)
            {
                std::string addition;
                std::getline(std::cin, addition);
                char horizontal[MAX_SIZE];
                char vertical[MAX_SIZE];
                char figureNumber[MAX_SIZE];
                if ((addition.find("vertical=", 0) != std::string::npos) && (addition.find("horizontal=", 0) != std::string::npos))
                {
                    size_t hFirstPos{addition.find("horizontal=", 0) + 11};
                    size_t hLastPos{0};
                    if (addition.find(' ', hFirstPos) == std::string::npos)
                        hLastPos = addition.length();
                    else
                        hLastPos = addition.find(' ', hFirstPos);
                    size_t hPos{hLastPos - hFirstPos};
                    size_t vFirstPos{addition.find("vertical=", 0) + 9};
                    size_t vLastPos{0};
                    if (addition.find(' ', vFirstPos) == std::string::npos)
                        vLastPos = addition.length();
                    else
                        vLastPos = addition.find(' ', vFirstPos);
                    size_t vPos{vLastPos - vFirstPos};
                    for (size_t i = 0; i < vPos; i++)
                        vertical[i] = addition[vFirstPos++];
                    for (size_t i = 0; i < hPos; i++)
                        horizontal[i] = addition[hFirstPos++];
                    vertical[vPos] = '\0';
                    horizontal[hPos] = '\0';
                    size_t lastPos = (vLastPos > hLastPos ? vLastPos : hLastPos);
                    char test = addition[addition.length() - 1];
                    while ((addition.length() - 1 >= lastPos) && (addition[addition.length() - 1] == ' '))
                    {
                        addition.resize(addition.size() - 1);
                    }
                    if ((addition[lastPos + 1] >= '0') && (addition[lastPos + 1] <= '9'))
                    {

                        size_t figureNumberLastPos = addition.length();
                        size_t figureNumberFirstPos = addition.rfind(' ', figureNumberLastPos) + 1;
                        size_t figureNumberPos = figureNumberLastPos - figureNumberFirstPos;
                        for (size_t i = 0; i < figureNumberPos + 1; i++)
                            figureNumber[i] = addition[figureNumberFirstPos++];
                        figureNumber[figureNumberPos] = '\0';
                        figures[convertToFloat(figureNumber) - 1]->translate(convertToFloat(horizontal), convertToFloat(vertical));
                        std::cout << "Translated " << figures[convertToFloat(figureNumber) - 1]->getType() << " (" << figureNumber << ") "
                                  << "by horizontal: " << horizontal << " and vertical: " << vertical;
                    }
                    else
                    {
                    for (size_t i = 0; i < figures.size(); i++)
                        figures[i]->translate(convertToFloat(horizontal), convertToFloat(vertical));
                    std::cout << "Translated all figures by horizontal: " << horizontal << " and vertical: " << vertical;
                    }
                    changes = true;
                }
                else std::cout << "Invalid option!\n";
            }
            else
            {
                std::cout << "There are no figures!\n";
                std::cin.ignore(1024, '\n');
            }
        }
        else std::cout << "Invalid command!\n";
    }
}