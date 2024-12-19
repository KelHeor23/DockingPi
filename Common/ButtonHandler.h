#ifndef BUTTONHANDLER_H
#define BUTTONHANDLER_H

#include <atomic>
#include <regex>

namespace ButtonHandler {

class Button
{
public:
    Button(){}
    void setAllowedRegex(const std::regex &newAllowedRegex);
    void run();

    char getButton(){
        return button.load();
    }

private:
    bool kbhit();

private:
    std::atomic_char button;
    std::regex allowedRegex{"[A-Za-z0-9]"};
};
}

#endif // BUTTONHANDLER_H
