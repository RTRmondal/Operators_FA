#include <iostream>

class Time
{
private:
    int time_in_sec_;
public:
    Time(int time_in_sec = 0)
    {
        time_in_sec_ = time_in_sec;
    }

    void set_time(int time_in_sec)
    {
        time_in_sec_ = time_in_sec;
    }

    void set_time(int hour, int minute, int second)
    {
        time_in_sec_ = hour * 3600 + minute * 60 + second;
    }

    operator int()
    {
        return (int)time_in_sec_;
    }

    Time operator+(const Time &rhs) const
    {
        return Time(time_in_sec_ + rhs.time_in_sec_);
    }

    Time operator-(const Time &rhs) const
    {
        return Time(time_in_sec_ - rhs.time_in_sec_);
    }

    Time operator*(int scalar) const
    {
        return Time(scalar * time_in_sec_);
    }

    friend std::ostream &operator<<(std::ostream &stream, Time &rhs)
    {
        int minutes = rhs.time_in_sec_ / 60;
        int seconds = rhs.time_in_sec_ % 60;
        int hours = minutes / 60;
        if(hours != 0)
        {
            minutes = minutes - (hours * 60);
            stream << hours << "h:";
        }
        if(minutes != 0)
        {
            stream << minutes << "m:";
        }
        stream << seconds << "s";

        stream << '\n';
        return stream;
    }

};

int main()
{
    Time t1(200);
//    Time t1(20000); // 5h:33m:20s
    std::cout << t1 << std::endl; // displays 03m:20s

    Time t2;
    //std::cin >> t2; // user enters 10h:12m:01s
    t2.set_time(10, 12, 1);
    std::cout << t2;

    Time t3 = t2 - t1; // 10h:8m:41s
    int t3s = t3; // 36521
    std::cout << t3 << "In seconds - " << t3s;
    
    
    return 0;
}
