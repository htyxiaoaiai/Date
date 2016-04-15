# Date
c++实现万年历
#include <iostream>

using namespace std;

class Date
{
	friend ostream& operator<<(ostream& os, Date& d);
	friend istream& operator>>(istream& os, Date& d);
public:
	//构造函数
	Date(int year = 1900, int month = 1, int day = 1)
		:_year(year)
		,_month(month)
		,_day(day)
	{
		if ((year < 1900) || ((month < 1) || (month > 12)) || ((day < 1) || (day > DateMonth())))
		{
			_year = 1900;
			_month = 1;
			_day = 1;
		}
	}
	//拷贝构造函数 
	Date(Date& d)
	{
		_year = d._year;
		_month = d._month;
		_day = d._day;
	}
	//赋值运算符重载
	Date& operator = (Date& d)
	{
		if (this != &d)
		{
			_year = d._year;
			_month = d._month;
			_day = d._day;
		}
		return *this;
	}
public:
	int DateMonth()
	{
		int Months[13] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
		if (IsLeap())
		{
			Months[2] = 29;
		}
		return Months[_month];
	}
	bool IsLeap()
	{
		if (((_year % 4 == 0) && (_year % 100 != 0)) || (_year % 400 == 0))
		{
			return true;
		}
		return false;
	}
	void ToCorrect()
	{
		while (_day > DateMonth())
		{
			if (_month == 12)
			{
				_year++;
				_day -= DateMonth();
				_month = 1;
			}
			else
			{
				_day -= DateMonth();
				_month++;
			}
		}

		while (_day < 0)
		{
			if (_month == 1)
			{
				_year--;
				_month = 12;
			}
			else
			{
				_month--;
			}
			_day += DateMonth();
		}

	}
public:
	Date operator + (int day)
	{
		Date temp(*this);
		Date ret(*this);
		_day += day;
		ToCorrect();
		ret = *this;
		*this = temp;
		return ret;
	}
	Date operator - (int day)
	{
		Date temp(*this);
		Date ret(*this);
		_day -= day;
		ToCorrect();
		ret = *this;
		*this = temp;
		return ret;
	}
	Date& operator += (int day)
	{
		_day += day;
		ToCorrect();
		return *this;
	}
	Date operator -= (int day)
	{
		_day -= day;
		ToCorrect();
		return *this;
	}
	bool operator == (Date d)
	{
		return ((_year == d._year) && (_month == d._month) && (_day == d._day));
	}
	bool operator !=(Date d)
	{
		return !(*this == d);
	}
	bool operator > (Date& d)
	{
		if (_year > d._year)
		{
			return true;
		}
		else
		{
			if (_year == d._year)
			{
				if (_month > d._month)
				{
					return true;
				}
				else
				{
					if (_month == d._month)
					{
						if (_day > d._day)
						{
							return true;
						}
					}
				}
			}
		}
		return false;
	}
	
	int operator - (Date& d)
	{
		Date d1(*this);
		Date d2(d);
		Date temp;
		int day = 0;
		int flag = 1;
		if (d2 > d1)
		{
			temp = d1;
			d1 = d2;
			d2 = temp;
			flag = -1;
		}
		else
		{
			flag = 1;
		}
		while (d1 != d2)
		{
			d2 ++;
			day++;
		}
		return (day * flag);
	}

	Date& operator++()
	{
		_day++;
		ToCorrect();
		return *this;
	}

	Date operator++(int)
	{
		Date temp(*this);
		_day++;
		ToCorrect();
		return temp;
	}
private:
	int _year;
	int _month;
	int _day;
};

ostream& operator<<(ostream& os, Date& d)
{
	os << d._year << "-" << d._month << "-" << d._day << endl;
	return os;
}
istream& operator >>(istream& in, Date& d)
{
	in >> d._year >> d._month >> d._day;
	return in;
}

int main()
{
	Date d(2016, 3, 2);
	/*d = d - 8888;
	cout << d;*/
	Date d1(1994, 10, 12);
	/*d1= d1 - 100;*/
	cout <<d1 - d << endl;
	getchar();
	return 0;
}
