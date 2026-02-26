#include <iostream>
#include <string>

int main() {
    std::cout << "lelo --lelo" << std::endl;
    return 0;
}

class Time {
private:
    int sec;
    int min;
    int hour;

    int absolute_sec() const {
        return sec + min * 60 + hour * 3600;
    }

    void set_relative_sec(int abs_sec) {
        hour = abs_sec / 3600;
        abs_sec -= hour * 3600;
        min = abs_sec / 60;
        abs_sec -= min * 60;
        sec = abs_sec;
    }

public:
    Time() : sec(0), min(0), hour(0) {}
    Time(int a, int b, int c) : sec(a), min(b), hour(c) {}
    Time(int abs_sec) {set_relative_sec(abs_sec);}
    
    

    

    

    bool is_valid() {
        auto func = [](int n) { return n <= 59 && n >= 0;};
        return func(sec) && func(min) && func(hour);
    }

    std::string to_string(bool hour_12_format = false) const{
        std::string result;
        // formarts the hour to 12 och 24 format
        int hour_format = hour - (int)hour_12_format * hour_format % 12; 
        // add the base string
        result = std::to_string(hour_format) + ":" + std::to_string(min) + ":" + std::to_string(sec);
        // to add the AM/PM stuff if its supose to 
        result += hour_12_format ? "" : hour >= 12 ? "[ PM]" : "[ AM]";;
        return result;
    }

    bool is_am() const {
        return 12 < hour;
    }

    Time operator+(const int& other) {
        return Time(absolute_sec() + other);
    }

    void operator++() {
        set_relative_sec(absolute_sec()+1);
    }

    void operator--() {
        set_relative_sec(absolute_sec()-1);
    }

    bool operator==(const Time& other) {
        return absolute_sec() == other.absolute_sec();
    }

    bool operator!=(const Time& other) {
        return !(this == &other);
    }

    bool operator<(const Time& other) {
        return absolute_sec() < other.absolute_sec();
    }

    bool operator>(const Time& other) {
        return !(this < &other);
    }

    bool operator<=(const Time& other) {
        return !(this > &other) || (this == &other);
    }

    bool operator>=(const Time& other) {
        return !(this < &other) || (this == &other);
    }

    // har igen kolla på hur dessa ska göras
    std::string operator<<(const Time& other) {
        return other.to_string();
    }

    std::string operator>>(const Time& other) {
        return "";
    }



};
