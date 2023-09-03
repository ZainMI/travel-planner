#ifndef __destination_h_
#define __destination_h_
#include <vector>
#include <map>
#include <iostream>
#include <ostream>
#include <set>
#include <fstream>
#include <string>

#include "activity.h"

class Destination {
public:
	Destination(const std::string& n) { city = n; price = 0; }
	Destination(const std::string& n, const Date& s, const Date& e) { city = n; start = s; end = e; price = 0; }
	Destination(const std::string& n, const double& p, const Date& s, const Date& e) { city = n; price = p;
																						start = s; end = e; }
	std::set<Activity> get() const { return agenda; }
	std::string getCity() const { return city; };
	void set(const std::set<Activity>& old) { agenda = old; }
	int size() const { return agenda.size(); }
	void add(const Activity& n) { agenda.insert(n); }
	int getDays() const;
	double amount() const {return price; }
	void removePrice(const double& d) { price -= d; }
	void addPrice(const double& d) { price += d; }
	bool operator<(const Destination& obj) const;
	bool operator==(const Destination& obj) const;
	Date getStart() const { return start; }
	Date getEnd() const { return end; }
	Date start;
	Date end;

private:
	std::set<Activity> agenda;
	std::string city;
	double price;


};

#endif