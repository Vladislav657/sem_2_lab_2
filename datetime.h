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
    Date d;
    Time t;

public:
    DateTime();

    DateTime(int seconds, int minutes, int hours, int day, int month, int year);

    DateTime(DateTime&);

    DateTime(DateTime&&) noexcept;

    inline int getSeconds() const{
        return this->t.seconds;
    }

    inline void setSeconds(long long seconds){
        this->t.seconds = 0;
        this->addSeconds(seconds);
    }

    inline int getMinutes() const{
        return this->t.minutes;
    }

    inline void setMinutes(long long minutes){
        this->t.minutes = 0;
        this->addMinutes(minutes);
    }

    inline int getHours() const{
        return this->t.hours;
    }

    inline void setHours(long long hours){
        this->t.hours = 0;
        this->addHours(hours);
    }

    inline int getDay() const{
        return this->d.day;
    }

    inline void setDay(int day){
        this->d.day = 0;
        this->addDays(day);
    }

    inline int getMonth() const{
        return this->d.month;
    }

    inline void setMonth(int month){
        this->d.month = 0;
        this->addMonths(month);
    }

    inline int getYear() const{
        return this->d.year;
    }

    inline void setYear(int year){
        this->d.year = 0;
        this->addYears(year);
    }

    void printByTemplate(int) const;

    static bool verifyDate(int, int, int);

    static bool verifyTime(int, int, int);

    static DateTime currentDateTime();

    char *dateTimeToString(int) const;

    Date date();

    Time time();

    static DateTime getDateTimeFromString(char *, int);

    void addSeconds(long long);

    void addMinutes(long long);

    void addHours(long long);

    void addDays(int);

    void addMonths(int);

    void addYears(int);

    static long long daysTo(DateTime&, DateTime&);

    static long long secondsTo(DateTime&, DateTime&) ;
};

#endif //LAB_2_DATETIME_H
