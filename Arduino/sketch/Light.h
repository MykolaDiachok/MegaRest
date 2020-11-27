/*
class for enable/disable relay
*/
#ifndef Light_h
#define Light_h

#include "Arduino.h"

class Light
{
public:
    Light(int pin, bool on = HIGH)
    {
        _pin = pin;
        _on = on;
        _off = !on;
        pinMode(_pin, OUTPUT);
    }

    void ON()
    {
        digitalWrite(_pin, _on);
    }

    void OFF()
    {
        digitalWrite(_pin, _off);
    }

    void Switch(bool _state)
    {
        digitalWrite(_pin, _state);
    }

    bool Status()
    {
        return digitalRead(_pin);
    }

    int Function(String command)
    {
        if (command.length() == 0)
        {
            return Status();
        }
        // Get state from command
        int state = command.toInt();

        Switch(state);
        return Status();
    }

private:
    int _pin;
    bool _on;
    bool _off;
};

#endif
