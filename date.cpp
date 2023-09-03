#include <vector>
#include <map>
#include <iostream>
#include <ostream>
#include <fstream>
#include <string>
#include <set>

#include "date.h"

bool Date::operator<=(const Date& obj) {
	return ((*this < obj) || *this == obj);
}

bool Date::operator==(const Date& obj) const{
	return (year == obj.year && day == obj.day && month == obj.month && hours == obj.hours && mins == obj.mins);
}

bool Date::operator!=(const Date& obj) const {
	return !(*this == obj);
}

bool Date::operator<(const Date& rhs) const{
    if (year < rhs.year) {
        return true;
    } else if (year == rhs.year) {
        if (month < rhs.month) {
            return true;
        } else if (month == rhs.month) {
            if (day < rhs.day) {
                return true;
            } else if (day == rhs.day) {
                if (hours < rhs.hours) {
                    return true;
                } else if (hours == rhs.hours) {
                    return mins < rhs.mins;
                }
            }
        }
    }
    return false;
}



std::string Date::getDate() const{
	std::string m = std::to_string(month);
	std::string d = std::to_string(day);
	std::string y = std::to_string(year);
	if (month < 10)
		m = '0' + m;
	if (day < 10)
		d = '0' + d;
	if (year < 10)
		y = '0' + y;
	if (year < 100)
		y = '0' + y;
	if (year < 1000)
		y = '0' + y;
	return m + '/' + d + '/' + y;
}

std::string Date::getTime() const{
	std::string h = std::to_string(hours);
	std::string m = std::to_string(mins);
	if (hours < 10)
		h = '0' + h;
	if (mins < 10)
		m = '0' + m;
	return h + ':' + m;
}