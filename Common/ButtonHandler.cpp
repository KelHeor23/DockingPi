#include "ButtonHandler.h"

#include <cstdio>
#include <termios.h>
#include <thread>
#include <unistd.h>

bool ButtonHandler::Button::kbhit()
{
    struct termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO); // Отключаем канонический режим и эхо
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    int ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

    if(ch != EOF) {
        ungetc(ch, stdin); // Возвращаем символ обратно в поток
        return true;
    }
    return false;
}

void ButtonHandler::Button::run()
{
    std::thread t([this](){
        char key;
        while (true){
            if (kbhit())  // Проверяем, нажата ли клавиша
                key = getchar(); // Считываем нажатую клавишу

            if (std::regex_match(std::string(1, key), allowedRegex))
                button = key;
        }

    });

    t.detach();
}

void ButtonHandler::Button::setAllowedRegex(const std::regex &newAllowedRegex)
{
    allowedRegex = newAllowedRegex;
}
