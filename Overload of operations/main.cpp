#include <iostream>
#include <process.h>
#include <string.h>
#include <string>
using namespace std;

class time12 {
private:
	bool pm;
	int hour;
	int min;
public:
	time12() : pm(true), hour(0), min(0) {}
	time12(bool ap, int h, int m) : pm(ap), hour(h), min(m) {}

	void display()const {
		if (hour < 10) cout << 0;
		cout << hour << ":";
		if (min < 10) cout << 0;
		cout << min << " ";
		string am_pm = pm ? "p.m." : "a.m.";
		cout << am_pm;
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

	operator time12() const;
};

time24::operator time12() const {
	int h24 = hours;
	bool pm = hours < 12 ? false : true;

	int roundMins = (seconds < 30) ? minutes : minutes+1;

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

int main() {
	int h, m, s;
	char dm;
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
		//break;
	}

	return 0;
}