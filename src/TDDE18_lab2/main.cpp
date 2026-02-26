#include <iostream>
#include <string>

int main() {
    std::cout << "lelo --lelo" << std::endl;
    return 0;
}

struct time_obj {
    int sec;
    int min;
    int hour;
    bool hour_24_format = false;

    time_obj() : sec(0), min(0), hour(0) {}
    time_obj(int a, int b, int c) : sec(a), min(b), hour(c) {}

    bool is_valid() {
        auto func = [](int n) { return n <= 59 && n >= 0;};
        return func(sec) && func(min) && func(hour);
    }

    std::string to_string() {
        if (hour_24_format) {
            return std::to_string(hour) + ":" + std::to_string(min) + ":" + std::to_string(sec);
        } else {
            return 
        }
    }
};
