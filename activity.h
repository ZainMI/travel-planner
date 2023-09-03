#ifndef __activity_h_
#define __activity_h_
#include <vector>
#include <map>
#include <iostream>
#include <ostream>
#include <set>
#include <fstream>
#include <string>
#include <chrono>
#include <ctime>

#include "date.h"
class Date;

class Activity {
public:
	Activity(const std::string& n, const double& p, const Date& start, const Date& end, const std::string& l);
	Activity(const std::string& n, const Date& start, const Date& end) {activity = n; price = 0; s = start; e = end;}
	std::string get() const { return activity; }
	std::string getLink() const { return link; }
	double amount() const { return price; };
	double getDays() const;
	bool operator<(const Activity& obj) const;
	bool operator==(const Activity& obj) const;
	Date getStart() const { return s; }
	Date getEnd() const { return e; }
	Date s;
	Date e;

private:
	std::string activity;
	std::string link;
	double price;

};


#endif