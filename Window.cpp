#include "Window.h"
#include <iostream>
#include <fstream>

using namespace std;

Window::Window()
{
    open = true;
    timeBusy = 0;
    timeIdle = 0;
}

Window::~Window()
{

}

void Window::setTimeBusy(int num)
{
    timeBusy = num;
}

void Window::increaseIdle()
{
    timeIdle++;
}

void Window::decreaseBusy()
{
    timeBusy--;
}

bool Window::isOpen()
{
    if(timeBusy == 0)
    {
        return true;
    }
    return false;
}

int Window::getTimeBusy()
{
    return timeBusy;
}

int Window::getTimeIdle()
{
    return timeIdle;
}

void Window::resetIdle()
{
    timeIdle = 0;
}
