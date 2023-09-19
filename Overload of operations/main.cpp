#include <iostream>
#include <process.h>
#include <string.h>
#include <string>
#include <conio.h>
using namespace std;

class time12 {
private:
	bool pm;
	int hour;
	int min;
public:
	time12() : pm(true), hour(0), min(0) {}
	//time12(time24);
	time12(bool ap, int h, int m) : pm(ap), hour(h), min(m) {}

	void display()const {
		if (hour < 10) cout << 0;
		cout << hour << ":";
		if (min < 10) cout << 0;
		cout << min << " ";
		string am_pm = pm ? "p.m." : "a.m.";
		cout << am_pm << endl;
	}
};

class time24 {
private:
	int hours;
	int minutes;
	int seconds;
public:
	time24() : hours(0), minutes(0), seconds(0) {}
	time24(int h, int m, int s) : hours(h), minutes(m), seconds(s) {}

	void display()const {
		if (hours < 10) cout << 0;
		cout << hours << ":";
		if (minutes < 10) cout << 0;
		cout << minutes << ":";
		if (seconds < 10) cout << 0;
		cout << seconds << endl;
	}

	//int getHrs();
	//int getMins();
	//int getSecs();
	time24 operator+(time24)const;
	time24 operator++();
	time24 operator++(int);
	time24 operator--();
	time24 operator--(int);
	operator time12() const;
};

int main() {
	int h, m, s;
	char dm='a';

	//check operator++ and operator-- working
	/*time24 t_1(0, 1, 20), t_2;
	while (dm!='0') {
		t_2 = t_1++;
		t_2.display();
		dm = _getche();
	}*/

	//check operator+ working///////////////////////////////
	cout << "Enter time 1 in 24 hours format: ";
	cin >> h >> dm >> m >> dm >> s;
	if (h > 23 || m > 60 || s > 60) {
		cout << "Incorrect values";
		return(1);
	}
	time24 t1(h, m, s);

	cout << "Enter time 2 in 24 hours format: ";
	cin >> h >> dm >> m >> dm >> s;
	if (h > 23 || m > 60 || s > 60) {
		cout << "Incorrect values";
		return(1);
	}
	time24 t2(h, m, s);

	time24 t3 = t1 + t2;
	t3.display();
	time12 t3_12(t3);
	t3_12.display();
	/////////////////////////////////////////////////////////

	//check working of transform from format 24 to format 12 
	while (true) {
		cout << "Enter time in 24 hours format: ";
		cin >> h >> dm >> m >> dm >> s;
		if (h > 23 || m > 60 || s > 60) {
			cout << "Incorrect values";
			return(1);
		}

		time24 t24(h, m, s);
		cout << "Original time: "; t24.display();

		time12 t12 = t24;
		cout << "In 12 hours format: ";
		t12.display();
		cout << "\n\n";
		break;
	}////////////////////////////////////////////////////////

	return 0;
}

time24 time24::operator++(int) { //postfix format
	int h = hours, m = minutes, s = seconds;
	seconds++;
	if (seconds == 60) {
		seconds = 0;
		minutes++;
	}
	if (minutes == 60) {
		minutes = 0;
		hours++;
	}
	if (hours == 24) {
		hours = 0;
	}
	time24 t(h, m, s);
	return t;
}

time24 time24::operator++() {
	++seconds;
	if (seconds == 60) {
		seconds = 0;
		++minutes;
	}
	if (minutes == 60) {
		minutes = 0;
		++hours;
	}
	if (hours == 24) {
		hours = 0;
	}
	int h = hours, m = minutes, s = seconds;
	time24 t(h, m, s);
	return t;
}

time24 time24::operator--(int) { //postfix format
	int h = hours, m = minutes, s = seconds;
	seconds--;
	if (seconds == -1) {
		seconds = 59;
		minutes--;
	}
	if (minutes == -1) {
		minutes = 59;
		hours--;
	}
	if (hours == -1) {
		hours = 23;
	}
	time24 t(h, m, s);
	return t;
}

time24 time24::operator--() {
	--seconds;
	if (seconds == -1) {
		seconds = 59;
		--minutes;
	}
	if (minutes == -1) {
		minutes = 59;
		--hours;
	}
	if (hours == -1) {
		hours = 23;
	}
	int h = hours, m = minutes, s = seconds;
	time24 t(h, m, s);
	return t;
}

time24 time24::operator+(time24 t2) const {
	int h, m, s;
	h = hours + t2.hours;
	m = minutes + t2.minutes;
	s = seconds + t2.seconds;

	if (s >= 60) {
		s -= 60;
		m++;
	}
	if (m >= 60) {
		m -= 60;
		h++;
	}
	if (h >= 24) 
		h -= 24;

	return time24(h, m, s);
}

time24::operator time12() const {
	int h24 = hours;
	bool pm = hours < 12 ? false : true;

	int roundMins = (seconds < 30) ? minutes : minutes + 1;

	if (roundMins == 60) {
		roundMins = 0;
		h24++;
	}

	int h12 = (h24 < 13) ? h24 : h24 - 12;
	if (h12 == 0 || h24 == 24) {
		h12 = 12;
		pm = false;
	}

	return time12(pm, h12, roundMins);
}

//time12::time12(time24 t24) {
//	int hrs24 = t24.getHrs();
//	pm = (t24.getHrs() < 12) ? false : true;
//	
//	min = (t24.getSecs() < 30) ? t24.getMins() : t24.getMins() + 1;
//	if (min == 60) {
//		min = 0;
//		hour++;
//		if (hrs24 == 12 || hrs24 == 24)
//			pm = (pm == true) ? false : true;
//	}
//
//	hour = (hrs24 < 13) ? hrs24 : hrs24 - 12;
//	if (hour == 0 || hrs24 == 24) {
//		hour = 12;
//		pm = false;
//	}
//}
