#include <vector>
#include <map>
#include <iostream>
#include <set>
#include <ostream>
#include <fstream>
#include <string>

#include "activity.h"

bool Activity::operator==(const Activity& obj) const {
	return activity == obj.activity;
}

bool Activity::operator<(const Activity& rhs) const{
    if (s < rhs.s) {
        return true;
    } else if (rhs.s < s) {
        return false;
    } else {
        return e < rhs.e;
    }
}


double Activity::getDays() const{
	double minutes = 0;
	double years = e.year - s.year;
	int months = e.month - s.month;
	int days = e.day - s.day;
	minutes += years * 365 * 24 * 60;
	minutes += months * 30 * 24 * 60;
	minutes += days * 24 * 60;
	int hours = e.hours - s.hours;
	int min = e.mins - s.mins;
	minutes += hours * 60;
	minutes += min;
	double num_days = minutes/1440;
	return num_days;
}

Activity::Activity(const std::string& n, const double& p, const Date& start, const Date& end, const std::string& l){
	activity = n;
	price = p;
	s = start;
	e = end;
	link = l;

}