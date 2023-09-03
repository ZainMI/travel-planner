#ifndef __date_h_
#define __date_h_
#include <vector>
#include <map>
#include <iostream>
#include <ostream>
#include <fstream>
#include <set>
#include <string>

class Date {
public:
	Date() { month = 0; year = 0; day = 0; hours = 0; mins = 0; }
	Date(int m, int d, int y, int h, int mi) { month = m; day = d; year = y; hours = h; mins = mi; }

	int year;
	int day;
	int month;
	int hours;
	int mins;

	std::string getDate() const;
	std::string getTime() const;
	bool operator==(const Date& obj) const;
	bool operator<(const Date& right) const;
	bool operator<=(const Date& obj);
	bool operator!=(const Date& obj) const;


};

#endif