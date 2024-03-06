#include <iostream>
#include <ctime>
#include <regex>
#include "datetime.h"

using namespace std;

DateTime::DateTime()= default;

DateTime::DateTime(int seconds, int minutes, int hours, int day, int month, int year) {
    this->seconds = seconds;
    this->minutes = minutes;
    this->hours = hours;
    this->day = day;
    this->month = month;
    this->year = year;
}

DateTime::DateTime(DateTime &dt) {
    this->seconds = dt.seconds;
    this->minutes = dt.minutes;
    this->hours = dt.hours;
    this->day = dt.day;
    this->month = dt.month;
    this->year = dt.year;
}

DateTime::DateTime(DateTime &&dt) noexcept {
    this->seconds = dt.seconds;
    this->minutes = dt.minutes;
    this->hours = dt.hours;
    this->day = dt.day;
    this->month = dt.month;
    this->year = dt.year;
}

void DateTime::printByTemplate(int format) const {
    // format - 1: 'hh:mm:ss dd/mm/yyyy' 2: 'hh:mm:ss dd.mm.yyyy' 3: 'hh.mm.ss dd/mm/yyyy'
    switch (format) {
        case 1:
            printf("%.2d:%.2d:%.2d %.2d/%.2d/%.4d\n", hours, minutes, seconds, day, month, year);
            break;
        case 2:
            printf("%.2d:%.2d:%.2d %.2d.%.2d.%.4d\n", hours, minutes, seconds, day, month, year);
            break;
        case 3:
            printf("%.2d.%.2d.%.2d %.2d/%.2d/%.4d\n", hours, minutes, seconds, day, month, year);
            break;
        default:
            printf("Incorrect format\n");
    }
}

bool DateTime::verifyDate(int day, int month, int year) {
    if (year < 0 || year / 10000 > 0 || day < 0) return false;
    switch (month) {
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12:
            return day <= 31;
        case 2:
            return day <= 28;
        case 4:
        case 6:
        case 9:
        case 11:
            return day <= 30;
        default:
            return false;
    }
}

bool DateTime::verifyTime(int seconds, int minutes, int hours) {
    return (seconds >= 0 && seconds < 60 && minutes >= 0 && minutes < 60 && hours >= 0 && hours < 24);
}

//char *DateTime::currentDateTime() {
//    return asctime(localtime((time(nullptr)))));
//}

string DateTime::datetimeToString(int format) const {
    // format - 1: 'hh:mm:ss dd/mm/yyyy' 2: 'hh:mm:ss dd.mm.yyyy' 3: 'hh.mm.ss dd/mm/yyyy'
    string hours_str = hours >= 10 ? to_string(hours) : "0" + to_string(hours);
    string minutes_str = minutes >= 10 ? to_string(minutes) : "0" + to_string(minutes);
    string seconds_str = seconds >= 10 ? to_string(seconds) : "0" + to_string(seconds);
    string day_str = day >= 10 ? to_string(day) : "0" + to_string(day);
    string month_str = month >= 10 ? to_string(month) : "0" + to_string(month);
    string year_str;
    if (year >= 1000) year_str = to_string(year);
    else if (year >= 100) year_str = "0" + to_string(year);
    else if (year >= 10) year_str = "00" + to_string(year);
    else year_str = "000" + to_string(year);
    string datetime;
    switch (format) {
        case 1:
            datetime = hours_str + ":" + minutes_str + ":" + seconds_str + " " + day_str + "/" +
                    month_str + "/" + year_str;
            break;
        case 2:
            datetime = hours_str + ":" + minutes_str + ":" + seconds_str + " " + day_str + "." +
                       month_str + "." + year_str;
            break;
        case 3:
            datetime = hours_str + "." + minutes_str + "." + seconds_str + " " + day_str + "/" +
                       month_str + "/" + year_str;
            break;
        default:
            return "Incorrect format";
    }
    return datetime;
}

Date DateTime::date() {
    Date d = {day, month, year};
    return d;
}

Time DateTime::time() {
    Time t = {seconds, minutes, hours};
    return t;
}

//DateTime::getDateTimeFromString(const char *datetime, int format) {
//    // format - 1: 'hh:mm:ss dd/mm/yyyy' 2: 'hh:mm:ss dd.mm.yyyy' 3: 'hh.mm.ss dd/mm/yyyy'
//
//}

void DateTime::addYears(int years) {
    if (years <= 0) return;
    this->year += years;
    if (this->year >= 10000) this->year %= 10000;
}

void DateTime::addMonths(int months) {
    if (months <= 0) return;
    this->month += months;
    if (this->month > 12){
        addYears(this->month / 12);
        this->month %= 12;
    }
}

void DateTime::addDays(int days) {
    if (days <= 0) return;
    this->day += days;
    while (true){
        if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12){
            if (this->day > 31){
                addMonths(1);
                this->day -= 31;
            } else break;
        } else if (month == 4 || month == 6 || month == 9 || month == 11){
            if (this->day > 30){
                addMonths(1);
                this->day -= 30;
            } else break;
        } else if (month == 2 && this->day > 28){
            addMonths(1);
            this->day -= 28;
        } else break;
    }
}

void DateTime::addHours(int hours) {
    if (hours <= 0) return;
    this->hours += hours;
    if (this->hours >= 24){
        addDays(this->hours / 24);
        this->hours %= 24;
    }
}

void DateTime::addMinutes(int minutes) {
    if (minutes <= 0) return;
    this->minutes += minutes;
    if (this->minutes >= 60){
        addHours(this->minutes / 60);
        this->minutes %= 60;
    }
}

void DateTime::addSeconds(int seconds) {
    if (seconds <= 0) return;
    this->seconds += seconds;
    if (this->seconds >= 60){
        addMinutes(this->seconds / 60);
        this->seconds %= 60;
    }
}
