#include <iostream>

using namespace std;

class Window
{
public:
    Window();
    ~Window();
    void setTimeBusy(int num);
    void increaseIdle();
    int getTimeBusy();
    int getTimeIdle();
    bool isOpen();
    void decreaseBusy();
    void resetIdle();

private:
    bool open;
    int timeBusy;
    int timeIdle;
};
