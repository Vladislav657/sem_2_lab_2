#include <iostream>
#include <ctime>
#include "datetime.h"

using namespace std;
int months[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

DateTime::DateTime(): d({0, 0, 0}), t({0, 0, 0}){}

DateTime::DateTime(int seconds, int minutes, int hours, int day, int month, int year):
        d({day, month, year}), t({seconds, minutes, hours}){
    if (verifyTime(seconds, minutes, hours) && verifyDate(day, month, year)) {
        this->t = {seconds, minutes, hours};
        this->d = {day, month, year};
    } else {
        this->t = {0, 0, 0};
        this->d = {0, 0, 0};
    }
}

DateTime::DateTime(DateTime &dt): d(dt.d), t(dt.t){
    this->t = dt.t;
    this->d = dt.d;
}

DateTime::DateTime(DateTime &&dt) noexcept: d(dt.d), t(dt.t){
    this->t = dt.t;
    this->d = dt.d;
}

void DateTime::printByTemplate(int format) const {
    // format - 1: 'hh:mm:ss dd/mm/yyyy' 2: 'hh:mm:ss dd.mm.yyyy' 3: 'hh.mm.ss dd/mm/yyyy'
    printf("%s\n", this->dateTimeToString(format));
}

bool DateTime::verifyDate(int day, int month, int year) {
    return (year >= 0 && year / 10000 == 0 && month > 0 && month <= 12 && day > 0 && day <= months[month - 1]);
}

bool DateTime::verifyTime(int seconds, int minutes, int hours) {
    return (seconds >= 0 && seconds < 60 && minutes >= 0 && minutes < 60 && hours >= 0 && hours < 24);
}

DateTime DateTime::currentDateTime() {
    time_t t = ::time(nullptr);
    tm *t1 = localtime(&t);
    DateTime dt = DateTime(t1->tm_sec, t1->tm_min, t1->tm_hour, t1->tm_mday,
                           t1->tm_mon + 1, t1->tm_year + 1900);
    return dt;
}

char *DateTime::dateTimeToString(int format) const {
    // format - 1: 'hh:mm:ss dd/mm/yyyy' 2: 'hh:mm:ss dd.mm.yyyy' 3: 'hh.mm.ss dd/mm/yyyy'
    char *datetime = new char [20];
    switch (format) {
        case 1:
            sprintf(datetime, "%.2d:%.2d:%.2d %.2d/%.2d/%.4d", t.hours, t.minutes, t.seconds,
                    d.day, d.month, d.year);
            break;
        case 2:
            sprintf(datetime, "%.2d:%.2d:%.2d %.2d.%.2d.%.4d", t.hours, t.minutes, t.seconds,
                    d.day, d.month, d.year);
            break;
        case 3:
            sprintf(datetime, "%.2d.%.2d.%.2d %.2d/%.2d/%.4d", t.hours, t.minutes, t.seconds,
                    d.day, d.month, d.year);
            break;
        default:
            return (char *) "Incorrect format";
    }
    return datetime;
}

Date DateTime::date() {
    return this->d;
}

Time DateTime::time() {
    return this->t;
}

DateTime DateTime::getDateTimeFromString(char *datetime, int format) {
    // format - 1: 'hh:mm:ss dd/mm/yyyy' 2: 'hh:mm:ss dd.mm.yyyy' 3: 'hh.mm.ss dd/mm/yyyy'
    DateTime dt;
    switch (format) {
        case 1:
            sscanf(datetime, "%2d:%2d:%2d %2d/%2d/%4d", &dt.t.hours, &dt.t.minutes, &dt.t.seconds,
                   &dt.d.day, &dt.d.month, &dt.d.year);
            break;
        case 2:
            sscanf(datetime, "%2d:%2d:%2d %2d.%2d.%4d", &dt.t.hours, &dt.t.minutes, &dt.t.seconds,
                   &dt.d.day, &dt.d.month, &dt.d.year);
            break;
        case 3:
            sscanf(datetime, "%2d.%2d.%2d %2d/%2d/%4d", &dt.t.hours, &dt.t.minutes, &dt.t.seconds,
                   &dt.d.day, &dt.d.month, &dt.d.year);
            break;
        default:
            dt.t = {0, 0, 0};
            dt.d = {0, 0, 0};
    }
    return dt;
}

void DateTime::addYears(int years) {
    if (years <= 0) return;
    this->d.year += years;
    if (this->d.year >= 10000) this->d.year %= 10000;
}

void DateTime::addMonths(int month) {
    if (month <= 0) return;
    this->d.month += month;
    if (this->d.month > 12){
        addYears(this->d.month / 12);
        this->d.month %= 12;
    }
}

void DateTime::addDays(int days) {
    if (days <= 0) return;
    this->d.day += days;
    while (true){
        if (this->d.day > months[this->d.month - 1]){
            this->d.day -= months[this->d.month - 1];
            addMonths(1);
        }
        else break;
    }
}

void DateTime::addHours(long long hours) {
    if (hours <= 0) return;
    long long all_hours = this->t.hours + hours;
    if (all_hours >= 24){
        addDays((int)all_hours / 24);
        all_hours %= 24;
    }
    this->t.hours = (int) all_hours;
}

void DateTime::addMinutes(long long minutes) {
    if (minutes <= 0) return;
    long long all_minutes = this->t.minutes + minutes;
    if (all_minutes >= 60){
        addHours(all_minutes / 60);
        all_minutes %= 60;
    }
    this->t.minutes = (int) all_minutes;
}

void DateTime::addSeconds(long long seconds) {
    if (seconds <= 0) return;
    long long all_seconds = this->t.seconds + seconds;
    if (all_seconds >= 60){
        addMinutes(all_seconds / 60);
        all_seconds %= 60;
    }
    this->t.seconds = (int) all_seconds;
}

long long DateTime::daysTo(DateTime& dt1, DateTime& dt2) {
    long long days1 = (long long) dt1.d.year * 365 + dt1.d.day;
    for (int i = 0; i < dt1.d.month; ++i) days1 += months[i];
    long long days2 = (long long) dt2.d.year * 365 + dt2.d.day;
    for (int i = 0; i < dt2.d.month; ++i) days2 += months[i];
    return days2 - days1;
}

long long DateTime::secondsTo(DateTime& dt1, DateTime& dt2) {
    long long seconds1 = (long long) dt1.d.year * 365 * 24 * 60 * 60 + dt1.d.day * 24 * 60 * 60 +
            dt1.t.hours * 60 * 60 + dt1.t.minutes * 60 + dt1.t.seconds;
    for (int i = 0; i < dt1.d.month; ++i) seconds1 += months[i] * 24 * 60 * 60;
    long long seconds2 = (long long) dt2.d.year * 365 * 24 * 60 * 60 + dt2.d.day * 24 * 60 * 60 +
            dt2.t.hours * 60 * 60 + dt2.t.minutes * 60 + dt2.t.seconds;
    for (int i = 0; i < dt2.d.month; ++i) seconds2 += months[i] * 24 * 60 * 60;
    return seconds2 - seconds1;
}
