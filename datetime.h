#ifndef LAB_2_DATETIME_H
#define LAB_2_DATETIME_H

struct Date{
    int day;
    int month;
    int year;
};

struct Time{
    int seconds;
    int minutes;
    int hours;
};

class DateTime{
private:
    int seconds = 0;
    int minutes = 0;
    int hours = 0;
    int day = 0;
    int month = 0;
    int year = 0;

public:
    DateTime();

    DateTime(int, int, int, int, int, int);

    DateTime(DateTime&);

    DateTime(DateTime&&) noexcept ;

    inline int getSeconds() const{
        return this->seconds;
    }

    inline void setSeconds(int seconds){
        this->seconds = seconds;
    }

    inline int getMinutes() const{
        return this->minutes;
    }

    inline void setMinutes(int minutes){
        this->minutes = minutes;
    }

    inline int getHours() const{
        return this->hours;
    }

    inline void setHours(int hours){
        this->hours = hours;
    }

    inline int getDay() const{
        return this->day;
    }

    inline void setDay(int day){
        this->day = day;
    }

    inline int getMonth() const{
        return this->month;
    }

    inline void setMonth(int month){
        this->month = month;
    }

    inline int getYear() const{
        return this->year;
    }

    inline void setYear(int year){
        this->year = year;
    }

    void printByTemplate(int) const;

    static bool verifyDate(int, int, int);

    static bool verifyTime(int, int, int);

    static std::string currentDateTime();

    std::string datetimeToString(int) const;

    Date date();

    Time time();

    static DateTime getDateTimeFromString(const char *, int);

    void addSeconds(int);

    void addMinutes(int);

    void addHours(int);

    void addDays(int);

    void addMonths(int);

    void addYears(int);

    int daysTo();

    int secondsTo();
};

#endif //LAB_2_DATETIME_H
