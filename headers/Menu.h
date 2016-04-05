#include "Generator.h"
#include <string>

const int nOptions = 7;

class Menu
{
public:

    Menu();

    void loop();

private:

    Generator generator_;

    void generate();
    void output();
    void edit();
    void reset();
    void test();
    void exit();

    void initialise();

    void displayOptionList();
    void chooseOption();

    std::string optionNames[nOptions];

    bool isRunning;

    bool isReset;
};
