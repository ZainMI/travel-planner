#include <vector>
#include <map>
#include <iostream>
#include <iomanip>
#include <ostream>
#include <fstream>
#include <set>
#include <string>
#include <list>
#include <cmath>
#include <algorithm>

#include "destination.h"
#include "activity.h"
#include "date.h"

template <class T>
void print(T obj){
	std::cout << obj << std::endl;
}



void save(std::string file, std::set<Destination>& itenerary){
	std::ofstream outfile(file);
	outfile << std::fixed << std::setprecision(2);
	std::set<Destination>::iterator itr = itenerary.begin();
	while (itr != itenerary.end()){
		std::string cit = itr->getCity();
		for (int x = 0; x < (int)cit.length(); ++x){
			if (cit[x] == ' ')
				cit[x] = '_';

		}
		outfile << "Destination: " << cit << " " << itr->start.getDate() << " " << itr->start.getTime() << " " << itr->end.getDate() 
									<< " " << itr->end.getTime() << " " << itr->amount() << std::endl;
		std::set<Activity> agenda = itr->get();
		for (std::set<Activity>::iterator i = agenda.begin(); i != agenda.end(); ++i){
			std::string tmp = i->get();
			for (int x = 0; x < (int)tmp.length(); ++x){
				if (tmp[x] == ' ')
					tmp[x] = '_';

			}
			outfile << tmp << " " << i->s.getDate() << " " << i->s.getTime() << " " << i->e.getDate() << " " << i->e.getTime()
					<< " " << i->amount() << " " << i->getLink() << std::endl;
		}
		outfile << std::endl;
		++itr;
	}
	outfile.close();
}

void loadIndex(std::string file, std::list<std::string>& trips){
	std::ifstream old(file);
	std::string in;
	while (old >> in){
		for (int i = 0; i < (int)in.length(); ++i){
			if (in[i] == '_')
				in[i] = ' ';
		}
		trips.push_back(in);
	}
}

void saveIndex(std::string file, std::list<std::string>& trips){
	std::ofstream outfile(file);
	std::list<std::string>::iterator itr = trips.begin();
	while (itr != trips.end()){
		std::string tmp = *itr;
		for (int i = 0; i < (int)tmp.length(); ++i){
			if (tmp[i] == ' ')
				tmp[i] = '_';
		}
		outfile << tmp << std::endl;
		++itr;
	}
}

void index(std::string file, std::list<std::string> trips) {
	std::ofstream outfile(file);
	outfile << "<!DOCTYPE html>" << std::endl;
	outfile << "<html>" << std::endl;
	outfile << "\t<head>" << std::endl;
	outfile << "\t\t<link rel=\"stylesheet\" href=\"style.css\">" << std::endl;
	outfile << "\t\t<title>My Trips</title>" << std::endl;
	outfile << "\t</head>" << std::endl;
	outfile << "\t<body>" << std::endl;
	outfile << "\t\t<h2>My Trips</h2>" << std::endl;
	outfile << "\t\t<ul class=\"no-indent-and-bullets\">" << std::endl;
	std::list<std::string>::iterator itr = trips.begin();
	while (itr != trips.end()) {
		outfile << "\t\t\t<li><h2><a href=\"" << *itr << ".html\" class=link-blue>" << *itr << "</a></h2></li>" << std::endl;
		++itr;
	}
	outfile << "\t\t</ul>" << std::endl;
	outfile << "\t</body>" << std::endl;
	outfile << "</html>" << std::endl;
	outfile.close();
}


void HTML(std::string file, std::set<Destination>& itenerary, std::string trip){
    std::ofstream outfile(file);
    outfile << std::fixed << std::setprecision(2);
    outfile << "<!DOCTYPE html>" << std::endl;
    outfile << "<html>" << std::endl;
    outfile << "\t<head>" << std::endl;
    outfile << "\t\t<meta charset=\"UTF-8\">" << std::endl;
    outfile << "\t\t<link rel=\"stylesheet\" href=\"style.css\">" << std::endl;
    outfile << "\t\t<title>" << trip << "</title>" << std::endl;
    outfile << "\t</head>" << std::endl;
    outfile << "\t<body>" << std::endl;
    outfile << "\t\t<div class=\"" << trip << "\">" << std::endl;
    outfile << "\t\t<div class=\"trip-font\">" << std::endl;
    outfile << "\t\t\t<h3>My Trip To " << trip << "</h3>" << std::endl;
    double price = 0;
    std::set<Destination>::iterator itr = itenerary.begin();
    while (itr != itenerary.end()){
        Date start, end;
        std::set<Activity> agenda = itr->get();
        std::set<Activity>::iterator aitr = agenda.begin();
        if (aitr != agenda.end()){
            start = aitr->s;
            aitr = agenda.end();
            if ((int)agenda.size() > 0){
                --aitr;
                end = aitr->e;
            }
            else
                end = start;
        }
        outfile << "\t\t\t<span class=\"bold\">Destination: " << itr->getCity() << "</span><br>" << std::endl;
        outfile << "\t\t\t" << start.getDate() << " - " << end.getDate() << "<br>" << std::endl;
        int nights = std::ceil(itr->getDays()) - 1;
        if (nights < 0)
            nights = 0;
        if (nights == 0 && itr->start != itr->end)
            nights = 1;
        outfile << "\t\t\t" << itr->getDays() << " day(s) " << nights << " night(s)" << " $" << itr->amount() << "<br>" << std::endl;
        price += itr->amount();
        outfile << "\t\t\tAgenda:<ol>" << std::endl;
        agenda = itr->get();
        for (std::set<Activity>::iterator i = agenda.begin(); i != agenda.end(); ++i){
            std::string tmp = i->get();
            for (int x = 0; x < (int)tmp.length(); ++x){
                if (tmp[x] == '_')
                    tmp[x] = ' ';
            }
            if (i->getLink() == "no")
                outfile << "\t\t\t\t<li>" << tmp << ": $" << i->amount() << "<ul class=\"no-bullets\">" << std::endl;
            else
                outfile << "\t\t\t\t<li><a href=\"" << i->getLink() << "\" class=link-blue target=\"_blank\">" << tmp << ":</a> $" << i->amount() << "<ul class=\"no-bullets\">" << std::endl;
            outfile << "\t\t\t\t\t<li>" << "Start: " << i->s.getDate() << " " << i->s.getTime() << "</li>" << std::endl;
            outfile << "\t\t\t\t\t<li>" << "End:&nbsp;&nbsp;" << i->e.getDate() << " " << i->e.getTime() << "</li>" << std::endl;
            outfile << "\t\t\t\t</ul></li>" << std::endl;
        }
        outfile << "\t\t\t</ol>";
        outfile << std::endl;
        ++itr;
    }
    itr = itenerary.begin();
		Date start, end;
		while (itr != itenerary.end()){
			std::set<Activity> agenda = itr->get();
			std::set<Activity>::iterator aitr = agenda.begin();
			if ((int)agenda.size() > 0){
				start = aitr->s;
				itr = itenerary.end();
				--itr;
				agenda = itr->get();
				aitr = agenda.end();
				--aitr;
				end = aitr->e;
				break;
			}
			else ++itr;
		}
    Activity tot("TOTAL",price,start,end,"no");
    outfile << "\t\t\t<span class=\"bold\">TOTAL:</span><br>" << std::endl;
    outfile << "\t\t\t" << tot.s.getDate() << " - " << tot.e.getDate() << "<br>" << std::endl;
    int nights = std::ceil(tot.getDays()) - 1;
    if (nights < 0)
        nights = 0;
    if (nights == 0 && tot.s != tot.e)
        nights = 1;
    outfile << "\t\t\t" << (int)std::ceil(tot.getDays())  << " day(s) " << nights 
            << " night(s)" << " $" << price << "<br>" << std::endl;
    outfile << "\t\t\t<br>" << std::endl;
    outfile << "\t\t\t<a href=\"index.html\" class=link-blue>Home</a><br>" << std::endl;
    outfile << "\t\t</div>" << std::endl;
    outfile << "\t\t</div>" << std::endl;
    outfile << "\t\t<div id=\"" << trip << "\"></div>" << std::endl;
    outfile << "\t\t<script  src=\"script.js\"></script>" << std::endl;
    outfile << "\t</body>" << std::endl;
    outfile << "</html>" << std::endl;
    outfile.close();
}




void load(std::string file, std::set<Destination>& prev){
	std::ifstream old(file);
	std::string city, days, token, price, date, time,link;
	std::set<Destination>::iterator itr;
	while (old >> city){
		if (city == "Destination:"){
			old >> city >> date >> time;
			for (int x = 0; x < (int)city.length(); ++x){
				if (city[x] == '_')
					city[x] = ' ';
			}
			Date s(std::stoi(date.substr(0,2)),std::stoi(date.substr(3,2)),std::stoi(date.substr(6,4)),
					std::stoi(time.substr(0,2)),std::stoi(time.substr(3,2)));
			old >> date >> time >> price;
			Date e(std::stoi(date.substr(0,2)),std::stoi(date.substr(3,2)),std::stoi(date.substr(6,4)),
					std::stoi(time.substr(0,2)),std::stoi(time.substr(3,2)));
			itr = prev.insert(Destination(city,std::stod(price),s,e)).first;
		}
		else{
			for (int i = 0; i < (int)city.length(); ++i){
				if(city[i] == '_')
					city[i] = ' ';
			}
			old >> date >> time;
			Date s(std::stoi(date.substr(0,2)),std::stoi(date.substr(3,2)),std::stoi(date.substr(6,4)),
					std::stoi(time.substr(0,2)),std::stoi(time.substr(3,2)));
			old >> date >> time >> price >> link;
			Date e(std::stoi(date.substr(0,2)),std::stoi(date.substr(3,2)),std::stoi(date.substr(6,4)),
					std::stoi(time.substr(0,2)),std::stoi(time.substr(3,2)));
			Destination ptr = *itr;
			ptr.add(Activity(city,stod(price),s,e,link));
			prev.erase(itr);
			itr = prev.insert(ptr).first;
		}

	}

	old.close();
}

std::map<std::string,std::pair<Date,Date>> printAgenda(const std::set<Activity>& agenda) {
  	std::map<std::string,std::pair<Date,Date>> loc;
  	std::cout << "The current agenda is:" << std::endl << std::endl;
  	std::set<Activity>::iterator aitr = agenda.begin();
 	while (aitr != agenda.end()){
    	std::set<Activity>::iterator tmp = aitr;
    	++tmp;
    	if (tmp == agenda.end()){
      		std::cout << aitr->get() << "($" << aitr->amount() << ")";
      		loc[aitr->get()] = {aitr->s,aitr->e};
      		break;
    	}
    	std::cout << aitr->get() << "($" << aitr->amount() << ")" << " -> ";
    	loc[aitr->get()] = {aitr->s,aitr->e};
    	++aitr;
  	}
  std::cout << std::endl << std::endl;
  return loc;
}

bool isFree(Activity& a, std::set<Destination>& plan, std::set<Destination>::iterator& citr) {
	bool free = true;
	Destination ptr = *citr;
	Date def;
	if (a.s < ptr.start || ptr.start == def)
		ptr.start = a.s;
	if (ptr.end < a.e)
		ptr.end = a.e;
	for (std::set<Destination>::iterator itr = plan.begin(); itr != plan.end(); ++itr){
		std::set<Activity> agenda = itr->get();
		for (std::set<Activity>::iterator aitr = agenda.begin(); aitr != agenda.end(); ++aitr){
			if ((a.get() != aitr->get()) && ((aitr->getStart() <= a.getStart() && a.getStart() < aitr->getEnd()) ||
				(a.getEnd() <= aitr->getEnd() && aitr->getStart() < a.getEnd()) ||
				(a.getStart() <= aitr->getStart() && aitr->getStart() < a.getEnd()) ||
				(aitr->getEnd() <= a.getEnd() && a.getStart() < aitr->getEnd()))){
				std::cout << std::endl << "Error: " << a.get() << " will conflict with " 
							<< aitr->get() << " in: " << itr->getCity() << std::endl; 
				std::cout << aitr->s.getDate() << " " << aitr->s.getTime() << " - " 
							<< aitr->e.getDate() << " " << aitr->e.getTime() << std::endl;
				free = false;
			}
		}
		if ((itr->getCity() != citr->getCity()) && ((itr->getStart() <= ptr.getStart() && ptr.getStart() < itr->getEnd()) ||
			(ptr.getEnd() <= itr->getEnd() && itr->getStart() < ptr.getEnd()) ||
			(ptr.getStart() <= itr->getStart() && itr->getStart() < ptr.getEnd()) ||
			(itr->getEnd() <= ptr.getEnd() && ptr.getStart() < itr->getEnd()))){
			std::cout << std::endl << "Error: " << ptr.getCity() << " will conflict with " 
						<< itr->getCity() << std::endl; 
			std::cout << itr->start.getDate() << " " << itr->start.getTime() << " - " << itr->end.getDate() << " " 
						<< itr->end.getTime() << std::endl;
			free = false;
		}
	}
	if (!free)
		std::cout << std::endl;
	return free;
}

std::set<Activity> edit(std::set<Destination>& plan, std::set<Destination>::iterator& itr);

std::set<Activity> addingTo(std::set<Destination>& plan, std::set<Destination>::iterator& itr, std::string activity) {
	std::set<Activity> agenda = itr->get();
	std::string token,link;
	if (activity == ""){
		std::cout << "What is the name of the activity: ";
		std::cin.sync();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::getline(std::cin,activity);
	}
	double p;
	int m,d,y,h,mi;
	bool valid_date = false;
	while (!valid_date) {
	    std::cout << "What is the start date for this activity (MM/DD/YYYY): ";
	    std::cin >> token;
	    try {
	        if (token.length() != 10){
	            throw std::invalid_argument("Error: Please make sure the date is in the format (MM/DD/YYYY) and try again");
	        	std::cout << std::endl;
	        }
	        m = std::stoi(token.substr(0,2));
	        d = std::stoi(token.substr(3,2));
	        y = std::stoi(token.substr(6,4));
	        valid_date = true;
	    } catch (const std::invalid_argument& e) {
	    	std::cout << std::endl;
	        std::cout << "Error: Please make sure the date is in the format (MM/DD/YYYY) and try again" << std::endl;
	        std::cout << std::endl;
	    } catch (const std::out_of_range& e) {
	    	std::cout << std::endl;
	        std::cout << "Error: Please make sure the date is in the format (MM/DD/YYYY) and try again" << std::endl;
	        std::cout << std::endl;
	    }
	}
	bool valid_time = false;
	while (!valid_time) {
	    std::cout << "What is the start time for this activity (00:00 - 24:00): ";
	    std::cin >> token;
	    try {
	        if (token.length() != 5){
	            throw std::invalid_argument("Error: Please make sure the time is in the format (01:23) and try again");
	            std::cout << std::endl;
	        }
	        h = std::stoi(token.substr(0,2));
	        mi = std::stoi(token.substr(3,2));
	        valid_time = true;
	    } catch (const std::invalid_argument& e) {
	    	std::cout << std::endl;
	        std::cout << "Error: Please make sure the time is in the format (01:23) and try again" << std::endl;
	        std::cout << std::endl;
	    } catch (const std::out_of_range& e) {
	    	std::cout << std::endl;
	        std::cout << "Error: Please make sure the time is in the format (01:23) and try again" << std::endl;
	        std::cout << std::endl;
	    }
	}
	Date s(m,d,y,h,mi);
	valid_date = false;
	while (!valid_date) {
	    std::cout << "What is the end date for this activity (MM/DD/YYYY): ";
	    std::cin >> token;
	    try {
	        if (token.length() != 10){
	            throw std::invalid_argument("Error: Please make sure the date is in the format (MM/DD/YYYY) and try again");
	            std::cout << std::endl;
	        }
	        m = std::stoi(token.substr(0,2));
	        d = std::stoi(token.substr(3,2));
	        y = std::stoi(token.substr(6,4));
	        valid_date = true;
	    } catch (const std::invalid_argument& e) {
	    	std::cout << std::endl;
	        std::cout << "Error: Please make sure the date is in the format (MM/DD/YYYY) and try again" << std::endl;
	        std::cout << std::endl;
	    } catch (const std::out_of_range& e) {
	    	std::cout << std::endl;
	        std::cout << "Error: Please make sure the date is in the format (MM/DD/YYYY) and try again" << std::endl;
	        std::cout << std::endl;
	    }
	}
	valid_time = false;
	while (!valid_time) {
	    std::cout << "What is the end time for this activity (00:00 - 24:00): ";
	    std::cin >> token;
	    try {
	        if (token.length() != 5){
	            throw std::invalid_argument("Error: Please make sure the time is in the format (01:23) and try again");
	            std::cout << std::endl;
	        }
	        h = std::stoi(token.substr(0,2));
	        mi = std::stoi(token.substr(3,2));
	        valid_time = true;
	    } catch (const std::invalid_argument& e) {
	    	std::cout << std::endl;
	        std::cout << "Error: Please make sure the time is in the format (01:23) and try again" << std::endl;
	        std::cout << std::endl;
	    } catch (const std::out_of_range& e) {
	    	std::cout << std::endl;
	        std::cout << "Error: Please make sure the time is in the format (01:23) and try again" << std::endl;
	        std::cout << std::endl;
	    }
	}
	Date e(m,d,y,h,mi);
	std::cout << "Price: ";
	std::cin >> token;
	p = std::stod(token);
	std::cout << "Would you like to add a link (yes/no): ";
	std::cin >> link;
	if (link != "no") {
		std::cout << "Please paste the link here: ";
		std::cin >> link;
	}
	Activity b(activity,p,s,e,link);
	if (isFree(b,plan,itr)){
		agenda.insert(b);
		Date def;
		Destination dum = *itr;
		dum.addPrice(p);
		if (b.s < dum.start || dum.start == def)
			dum.start = b.s;
		if (dum.end < b.e)
			dum.end = b.e;
		plan.erase(itr);
		itr = plan.insert(dum).first;
		std::cout << activity << " was successfully added." << std::endl;
	}
	else std::cout << "Adding '" << activity << "' was unsuccessful." << std::endl;
	return agenda;
}

std::set<Activity> edit(std::set<Destination>& plan, std::set<Destination>::iterator& itr) {
	std::string token, activity, link;
	std::set<Activity>::iterator aitr;
	std::set<Activity> agenda = itr->get();
	std::map<std::string,std::pair<Date,Date>> loc = printAgenda(agenda);
	std::cout << "What activity would you like to edit: ";
	std::cin.sync();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::getline(std::cin,activity);
	std::map<std::string,std::pair<Date,Date>>::iterator loci = loc.find(activity);
	if (loci == loc.end()){
		std::cout << activity << " was not found, would you like to add it to the agenda (yes/no): ";
		std::cin >> token;
		if (token == "yes")
			agenda = addingTo(plan,itr,activity);
	}
	else {
		Activity found(activity,loci->second.first,loci->second.second);
		aitr = agenda.find(found);
		bool end = false;
		bool beg = false;
		if (aitr->e == itr->end)
			end = true;
		else if (aitr->s == itr->start)
			beg = true;
		int m,d,y,h,mi;
		std::cout << "If unchanged type 'same'." << std::endl;
		bool valid_date = false;
		while (!valid_date) {
    		std::cout << "What is the new start date for this activity (MM/DD/YYYY): ";
    		std::cin >> token;
    		if (token == "same")
    			break;
    		try {
        		if (token.length() != 10){
            		throw std::invalid_argument("Error: Please make sure the date is in the format (MM/DD/YYYY) and try again");
            		std::cout << std::endl;
        		}
       			m = std::stoi(token.substr(0,2));
        		d = std::stoi(token.substr(3,2));
        		y = std::stoi(token.substr(6,4));
        		valid_date = true;
   			} catch (const std::invalid_argument& e) {
   				std::cout << std::endl;
        		std::cout << "Error: Please make sure the date is in the format (MM/DD/YYYY) and try again" << std::endl;
        		std::cout << std::endl;
    		} catch (const std::out_of_range& e) {
    			std::cout << std::endl;
        		std::cout << "Error: Please make sure the date is in the format (MM/DD/YYYY) and try again" << std::endl;
        		std::cout << std::endl;
    		}
		}
		if (token == "same"){
			m = aitr->s.month;
			d = aitr->s.day;
			y = aitr->s.year;
		}
		bool valid_time = false;
		while (!valid_time) {
		    std::cout << "What is the new start time for this activity (00:00 - 24:00): ";
		    std::cin >> token;
		    if (token == "same")
		    	break;
		    try {
		        if (token.length() != 5){
		            throw std::invalid_argument("Error: Please make sure the time is in the format (01:23) and try again");
		            std::cout << std::endl;
		        }
		        h = std::stoi(token.substr(0,2));
		        mi = std::stoi(token.substr(3,2));
		        valid_time = true;
		    } catch (const std::invalid_argument& e) {
		    	std::cout << std::endl;
		        std::cout << "Error: Please make sure the time is in the format (01:23) and try again" << std::endl;
		        std::cout << std::endl;
		    } catch (const std::out_of_range& e) {
		    	std::cout << std::endl;
		        std::cout << "Error: Please make sure the time is in the format (01:23) and try again" << std::endl;
		        std::cout << std::endl;
		    }
		}
		if (token == "same"){
			h = aitr->s.hours;
			mi = aitr->s.mins;
		}
		Date s(m,d,y,h,mi);
		valid_date = false;
		while (!valid_date) {
    		std::cout << "What is the new end date for this activity (MM/DD/YYYY): ";
    		std::cin >> token;
    		if (token == "same")
    			break;
    		try {
        		if (token.length() != 10){
            		throw std::invalid_argument("Error: Please make sure the date is in the format (MM/DD/YYYY) and try again");
            		std::cout << std::endl;
        		}
       			m = std::stoi(token.substr(0,2));
        		d = std::stoi(token.substr(3,2));
        		y = std::stoi(token.substr(6,4));
        		valid_date = true;
   			} catch (const std::invalid_argument& e) {
   				std::cout << std::endl;
        		std::cout << "Error: Please make sure the date is in the format (MM/DD/YYYY) and try again" << std::endl;
        		std::cout << std::endl;
    		} catch (const std::out_of_range& e) {
    			std::cout << std::endl;
        		std::cout << "Error: Please make sure the date is in the format (MM/DD/YYYY) and try again" << std::endl;
        		std::cout << std::endl;
    		}
		}
		if (token == "same"){
			m = aitr->e.month;
			d = aitr->e.day;
			y = aitr->e.year;
		}
		valid_time = false;
		while (!valid_time) {
		    std::cout << "What is the new end time for this activity (00:00 - 24:00): ";
		    std::cin >> token;
		    if (token == "same")
		    	break;
		    try {
		        if (token.length() != 5){
		            throw std::invalid_argument("Error: Please make sure the time is in the format (01:23) and try again");
		            std::cout << std::endl;
		        }
		        h = std::stoi(token.substr(0,2));
		        mi = std::stoi(token.substr(3,2));
		        valid_time = true;
		    } catch (const std::invalid_argument& e) {
		    	std::cout << std::endl;
		        std::cout << "Error: Please make sure the time is in the format (01:23) and try again" << std::endl;
		        std::cout << std::endl;
		    } catch (const std::out_of_range& e) {
		    	std::cout << std::endl;
		        std::cout << "Error: Please make sure the time is in the format (01:23) and try again" << std::endl;
		        std::cout << std::endl;
		    }
		}
		if (token == "same"){
			h = aitr->e.hours;
			mi = aitr->e.mins;
		}
		Date e(m,d,y,h,mi);
		std::cout << "What is the new price: ";
		std::cin >> token;
		double p;
		if (token == "same")
			p = aitr->amount();
		else
			p = std::stod(token);
		std::cout << "What is the new link (remove/same/'link'): ";
		std::cin >> link;
		if (link == "same")
			link = aitr->getLink();
		else if (link == "remove")
			link = "no";
		Activity b(activity,p,s,e,link);
		if (isFree(b,plan,itr)){
			double tmpPrice = aitr->amount();
			agenda.erase(aitr);
			agenda.insert(b);
			Destination ptr = *itr;
			ptr.removePrice(tmpPrice);
			ptr.addPrice(p);
			Date def;
			if (b.s < ptr.start || ptr.start == def)
				ptr.start = b.s;
			if (ptr.end < b.e)
				ptr.end = b.e;
			plan.erase(itr);
			itr = plan.insert(ptr).first;
			if (beg) {
				Destination restart = *itr;
				aitr = agenda.begin();
				restart.start = aitr->s;
				itr = plan.insert(restart).first;
			}
			else if (end) {
				Destination rend = *itr;
				aitr = agenda.end();
				--aitr;
				rend.end = aitr->e;
				plan.erase(itr);
				itr = plan.insert(rend).first;

			}
			std::cout << activity << " was successfully edited." << std::endl;
		}
		else std::cout << "Editing '" << activity << "' was unsuccessful." << std::endl;
	}
	return agenda;
}


void add_agenda(std::set<Destination>& plan, std::set<Destination>::iterator& itr){
	std::string activity, token;
	std::set<Activity> agenda = itr->get();
	std::cout << "What would you like to do to this agenda (view/edit/remove/new): ";
	std::cin >> activity;
	std::set<Activity>::iterator aitr;
	if (activity == "view"){
		printAgenda(agenda);
	}
	else if (activity == "remove"){
		std::map<std::string,std::pair<Date,Date>> loc = printAgenda(agenda);
		std::cout << "What activity would you like to remove: ";
		std::cin.sync();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::getline(std::cin,activity);
		std::map<std::string,std::pair<Date,Date>>::iterator loci = loc.find(activity);
		if (loci == loc.end()){
			std::cout << activity << " is not part of the agenda" << std::endl;
		}
		else{
			Activity found(activity,loci->second.first,loci->second.second);
			aitr = agenda.find(found);
			Destination dum = *itr;
			dum.removePrice(aitr->amount());
			if (aitr->s == dum.start){
				if (dum.size() > 1){
					std::set<Activity>::iterator t = agenda.begin();
					++t;
					dum.start = t->s;
				}
				else{
					Date t;
					dum.start = t;
				}
			}
			if (aitr->e == dum.end){
				if (dum.size() > 1){
					std::set<Activity>::iterator t = agenda.end();
					--t;
					--t;
					dum.start = t->s;
				}
				else{
					Date t;
					dum.end = t;
				}
			}
			plan.erase(itr);
			itr = plan.insert(dum).first;
			agenda.erase(aitr);
			std::cout << activity << " was successfully removed." << std::endl;
		}
	}
	else if (activity == "edit"){
		agenda = edit(plan,itr);
	}
	else{
		agenda = addingTo(plan,itr,"");
	}
	Destination ptr = *itr;
	ptr.set(agenda);
	plan.erase(itr);
	itr = plan.insert(ptr).first;
	std::cout << "Would you like to do anything else to this agenda (yes/no): ";
	std::cin >> token;
	if (token == "yes"){
		std::cout << std::endl;
		add_agenda(plan,itr);
	}
}

	
int main(){
	std::cout << std::fixed << std::setprecision(2);
	bool done = false;
	bool first = false;
	std::string trip, yes;
	std::list<std::string> trips;
	loadIndex("index.txt",trips);
	std::list<std::string>::iterator tripitr = trips.begin();
	std::cout << "Your previous trips:" << std::endl << std::endl;
	while (tripitr != trips.end()){
		std::cout << *tripitr << "  ";
		++tripitr;
	}
	std::cout << std::endl << std::endl;
	std::cout << "Which trip is this: ";
	std::cin.sync();
	std::getline(std::cin, trip);
	while (std::find(trips.begin(),trips.end(),trip) == trips.end()){
		std::cout << "This trip does not exist, would you like to create it (yes/no): ";
		std::cin >> yes;
		if (yes == "yes"){
			trips.push_back(trip);
		}
		else {
			done = true;
			break;
		}
	} 
	std::string file = trip + ".txt";
	std::string html = trip + ".html";
	while (!done){
		std::string c,token;
		std::set<Destination> prev;
		load(file,prev);
		std::set<Destination>::iterator itr = prev.begin();
		bool isIn = false;
		itr = prev.begin();
		std::cout << "This trip contains: " << std::endl;
		std::cout << std::endl;
		std::map<std::string,std::pair<Date,Date>> loc;
		while (itr != prev.end()){
			std::set<Destination>::iterator tmp = itr;
			++tmp;
			if (tmp == prev.end()){
				std::cout << itr->getCity() << "(" << itr->size() << ")" << "($" << itr->amount() << ")";
				loc[itr->getCity()] = {itr->start,itr->end};
				break;
			}
			std::cout << itr->getCity() << "(" << itr->size() << ")" << "($" << itr->amount() << ")" << " -> ";
			loc[itr->getCity()] = {itr->start,itr->end};
			++itr;
		}
		std::cout << std::endl << std::endl;
		std::cout << "What is the destination: ";
		std::cin.sync();
		if (first)
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::getline(std::cin, c);
		std::map<std::string,std::pair<Date,Date>>::iterator loci = loc.find(c);
		Destination found(c,loci->second.first,loci->second.second);
		itr = prev.find(found);
		if (itr != prev.end()) isIn = true;
		if (!isIn){
			std::cout << "This destination does not exist, would you like to add it (yes/no): ";
			std::cin >> yes;
			if (yes == "yes"){
				Destination a(c);
				itr = prev.insert(a).first;
			}
			else break;
		}
		std::cout << "What would you like to do (agenda/remove): ";
		std::cin >> token;
		if (token == "remove"){
			prev.erase(itr);
			std::cout << c << " was successfully removed." << std::endl;
		}
		else{
			add_agenda(prev,itr);
		}

		save(file,prev);
		saveIndex("index.txt",trips);
		index("index.html",trips);
		HTML(html,prev,trip);
		std::cout << "Would you like to do anything else to this trip (yes/no): ";
		std::cin >> token;
		if (token == "no") done = true;
		else first = true;
		std::cout << std::endl;

	}

	std::cout << "Thank You, bye!" << std::endl;

	return 1;

}