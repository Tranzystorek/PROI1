#include "Menu.h"

#include <iostream>
#include <fstream>

#include <ctime>
#include <cstdlib>

Menu::Menu()
{
    optionNames[0] = "Generate new map";
    optionNames[1] = "Write map to file MAP.txt";
    optionNames[2] = "Edit specific tile";
    optionNames[3] = "Reset map";
    optionNames[4] = "Calibrate and reset";
    optionNames[5] = "Automatic test";
    optionNames[6] = "Exit";

    isReset = false;
}

void Menu::loop()
{
    isRunning = true;

    while(isRunning)
    {
        displayOptionList();

        chooseOption();
    }
}//loop

void Menu::displayOptionList()
{
    for(int i=0;i<nOptions;i++)
        std::cout << i+1 << ". " << optionNames[i] << std::endl;
}//displayOptionList

void Menu::chooseOption()
{
    enum {GEN = 1, OUTPUT, EDIT, RESET, CAL, TEST, EXIT};

    int choice = -1;

    std::cout << "> ";

    std::cin >> choice;

    if(std::cin.fail())
    {
        std::cin.clear();
        std::cin.ignore(256, '\n');
    }

    switch(choice)
    {
        case GEN:
            generate();
            break;

        case OUTPUT:
            output();
            break;

        case EDIT:
            edit();
            break;

        case RESET:
            reset();
            std::cout << "Done" << std::endl;
            break;

        case CAL:
            initialise();
            break;

        case TEST:
            test();
            break;

        case EXIT:
            exit();
            break;

        default:
            std::cout << "Incorrect choice" << std::endl;
    }//switch
}//chooseOption

void Menu::initialise()
{
    enum {S = 1, M, L};
    enum {E = 1, N, H};

    Constants::Size s;
    Constants::Difficulty d;

    int choice = -1;

    bool chosen;

    do
    {
        chosen = true;

        std::cout << "Choose size:" << std::endl
                  << "1. Small" << std::endl
                  << "2. Medium" << std::endl
                  << "3. Large" << std::endl
                  << "> ";

        std::cin >> choice;

        if(std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(256, '\n');

            chosen = false;
        }

        switch(choice)
        {
            case S:
                s = Constants::SMALL;
                break;

            case M:
                s = Constants::MEDIUM;
                break;

            case L:
                s = Constants::LARGE;
                break;

            default:
                std::cout << "Incorrect choice" << std::endl;
                chosen = false;
        }
    }while(!chosen);

    choice = -1;

    do
    {
        chosen = true;

        std::cout << "Choose dificulty:" << std::endl
                  << "1. Easy" << std::endl
                  << "2. Normal" << std::endl
                  << "3. Hard" << std::endl
                  << "> ";

        std::cin >> choice;

        if(std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(256, '\n');
        }

        switch(choice)
        {
            case E:
                d = Constants::EASY;
                break;

            case N:
                d = Constants::NORMAL;
                break;

            case H:
                d = Constants::HARD;
                break;

            default:
                std::cout << "Incorrect choice" << std::endl;
                chosen = false;
        }
    }while(!chosen);

    generator_ = Generator(s, d);
}//initialise

void Menu::generate()
{
    if(!isReset)
    {
        std::cout << "Initialising..." << std::endl;

        initialise();
        isReset = true;
    }

    if(generator_.isGenerated())
    {
        std::cout << "Warning! The map has already been generated!" << std::endl
                  << "Do you want to reset and generate again? (y/n): ";

        char answer;

        std::cin >> answer;

        if(answer == 'y' || answer == 'Y')
            generator_.reset();
    }

    generator_.generateMap();
}//generate

void Menu::output()
{
    std::ofstream out("MAP.txt");

    out << generator_.getCurrentMap().toString();

    out.close();

    std::cout << "Done" << std::endl;
}//output

void Menu::edit()
{
    const int W = generator_.getCurrentMap().getWidth();
    const int H = generator_.getCurrentMap().getHeight();

    int x, y;

    std::cout << "Specify X: ";

    std::cin >> x;

    if(x < 0 || x >= W)
    {
        std::cout << "Incorrect coordinate" << std::endl;
        return;
    }

    std::cout << "Specify Y: ";

    std::cin >> y;

    if(y < 0 || y >= H)
    {
        std::cout << "Incorrect coordinate" << std::endl;
        return;
    }

    enum {G = 1, WL, M, E};

    int choice;

    std::cout << "Select tile type:" << std::endl
              << "1. Ground" << std::endl
              << "2. Wall" << std::endl
              << "3. Mine" << std::endl
              << "4. Explosive" << std::endl
              << "> ";

    std::cin >> choice;

    switch(choice)
    {
        case G:
            generator_.editTile(x, y, Tile::GRND);
            break;

        case WL:
            generator_.editTile(x, y, Tile::WALL);
            break;

        case M:
            generator_.editTile(x, y, Tile::MINE);
            break;

        case E:
            generator_.editTile(x, y, Tile::EXPL);
            break;

        default:
            std::cout << "Incorrect choice" << std::endl;
            return;
    }

    std::cout << "Edit complete. Output to file to see changes." << std::endl;
}//edit

void Menu::reset()
{
    generator_.reset();

    isReset = true;
}//reset

void Menu::test()
{
    std::cout << "Initiating..." << std::endl;

    srand(time(NULL));

    int s, d;

    s = rand() % 3;
    d = rand() % 3;

    std::cout << "Selected setting:" << std::endl
              << "Size: ";

    switch(s)
    {
        case Constants::SMALL:
            std::cout << "Small" << std::endl;
            break;

        case Constants::MEDIUM:
            std::cout << "Medium" << std::endl;
            break;

        case Constants::LARGE:
            std::cout << "Large" << std::endl;
    }

    std::cout << "Difficulty: ";

    switch(d)
    {
        case Constants::EASY:
            std::cout << "Easy" << std::endl;
            break;

        case Constants::NORMAL:
            std::cout << "Normal" << std::endl;
            break;

        case Constants::HARD:
            std::cout << "Hard" << std::endl;
    }

    std::cout << "Generating map..." << std::endl;

    generator_ = Generator((Constants::Size)s, (Constants::Difficulty)d);

    generator_.generateMap();

    std::cout << "Writing map to file..." << std::endl;

    std::ofstream out("MAP.txt");

    out << generator_.getCurrentMap().toString();

    out.close();

    std::cout << "Done" << std::endl;
}//test

void Menu::exit()
{
    std::cout << "Goodbye!" << std::endl;

    isRunning = false;
}//exit
