#include <iostream>
#include "datetime.h"

using namespace std;

int main() { // format - 1: 'hh:mm:ss dd/mm/yyyy' 2: 'hh:mm:ss dd.mm.yyyy' 3: 'hh.mm.ss dd/mm/yyyy'
    DateTime dt1 = DateTime::getDateTimeFromString("23:59:59 31/12/1000", 1);

    dt1.addSeconds(1);
    dt1.printByTemplate(1);
    dt1.addMinutes(60);
    dt1.printByTemplate(1);
    dt1.addDays(30);
    dt1.printByTemplate(1);
    dt1.addDays(28);
    dt1.printByTemplate(1);
    dt1.addDays(1);
    dt1.printByTemplate(1);
    dt1.addHours(23);
    dt1.printByTemplate(1);
    dt1.addDays(365);
    dt1.printByTemplate(1);
    dt1.addSeconds(100000000);
    dt1.printByTemplate(1);

    DateTime dt2 = DateTime::getDateTimeFromString("23:59:59 31/12/2023", 1);

    cout << "\n" << dt2.dateTimeToString(1) << "\n\n\n";

    DateTime dt3 = DateTime::currentDateTime();

    dt1.printByTemplate(1);
    dt2.printByTemplate(1);
    dt3.printByTemplate(1);
//    dt2.addSeconds(5874936);
//    dt2.printByTemplate(1);
//    dt1.addSeconds(32130481937);
//    dt1.printByTemplate(1);

    Date d = dt1.date();
    Time t = dt1.time();

    cout << d.day << " " << d.month << " " << d.year << " " << t.seconds << " " << t.minutes << " " << t.hours << "\n";

    cout << endl;
    cout << DateTime::daysTo(dt1, dt3) << endl;
    cout << DateTime::daysTo(dt2, dt3) << endl;
    cout << endl;
    cout << DateTime::secondsTo(dt1, dt3) << endl;
    cout << DateTime::secondsTo(dt2, dt3) << endl;

    return 0;
}
