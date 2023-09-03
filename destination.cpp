#include <vector>
#include <map>
#include <iostream>
#include <ostream>
#include <set>
#include <fstream>
#include <string>
#include <cmath>

#include "destination.h"

int Destination::getDays() const{
	double minutes = 0;
	double years = end.year - start.year;
	int months = end.month - start.month;
	int days = end.day - start.day;
	minutes += years * 365 * 24 * 60;
	minutes += months * 30 * 24 * 60;
	minutes += days * 24 * 60;
	int hours = end.hours - start.hours;
	int min = end.mins - start.mins;
	minutes += hours * 60;
	minutes += min;
	double num_days = minutes/1440;
	int d = std::ceil(num_days);
	return d;
}

bool Destination::operator==(const Destination& obj) const {
	return city == obj.city;
}

bool Destination::operator<(const Destination& rhs) const{
    if (start < rhs.start) {
        return true;
    } else if (rhs.start < start) {
        return false;
    } else {
        return end < rhs.end;
    }
}