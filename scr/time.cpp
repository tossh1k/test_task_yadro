#include "decl.h"

Time::Time() : hours_(0), minutes_(0) {}
Time::Time(int hours, int minutes) : hours_(hours), minutes_(minutes) {}

bool Time::operator==(const Time& time) const {
	return this->hours_ == time.hours_ && this->minutes_ == time.minutes_;
}

bool Time::operator>(const Time& time) const{
	return this->hours_ > time.hours_ || (this->hours_ == time.hours_ && this->minutes_ > time.minutes_);
}

bool Time::operator<(const Time& time) const{
	return this->hours_ < time.hours_ || (this->hours_ == time.hours_ && this->minutes_ < time.minutes_);
}

Time Time::operator-(const Time& time) const{
	int diff = (this->hours_ - time.hours_) * 60 + this->minutes_ - time.minutes_;
	return { diff / 60, diff % 60 };
}

Time Time::operator+(const Time& time) const{
	int sum = (this->hours_ + time.hours_) * 60 + this->minutes_ + time.minutes_;
	return { sum / 60, sum % 60 };
}

std::ostream& operator <<(std::ostream& os, const Time& time) {
	std::string h; std::string m;

	if (time.hours_ >= 10 && time.hours_ != 0)
		h = std::to_string(time.hours_);
	else
		h = '0' + std::to_string(time.hours_);

	if
		(time.minutes_ >= 10 && time.minutes_ != 0) m = std::to_string(time.minutes_);
	else
		m = '0' + std::to_string(time.minutes_);

	std::string str_time = h + ':' + m;
	return os << str_time;
}

std::istream& operator >>(std::istream& is, Time& time) {
	int h, m; char c;
	is >> h >> c >> m;
	time.hours_ = h;
	time.minutes_ = m;
	return is;
}