#ifndef GLHL_EVENT_HPP
#define GLHL_EVENT_HPP

namespace glhl {

enum class EventTypes {
    QUIT,
    KEY_PRESSED,
    KEY_RELEASED,
    KEY_REPEAT,
};

class Event {
public:
    const EventTypes type;
    const int value;

    Event(EventTypes type, int value = -1);
};

}

#endif