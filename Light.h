/*
class for enable/disable relay
*/
#ifndef Light_h
#define Light_h

#include "Arduino.h"

class Light
{
public:
    Light(byte pin, bool on = HIGH)
    {
        
        _pin = pin;
        _on = HIGH;
        _off = LOW;
        pinMode(_pin, OUTPUT);
        OFF();
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
        if (_state)
            digitalWrite(_pin, _on);
        else
            digitalWrite(_pin, _off);
    }

    bool Status()
    {
        bool _status = digitalRead(_pin);
        return _status;
        
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
