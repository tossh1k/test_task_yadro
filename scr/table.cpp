#include "decl.h"

Table::Table() : is_busy_(false), pay_hours_(0), start_use_(0, 0), in_use_(0, 0) {}

void Table::StartUsage(const Time& start) {
	is_busy_ = true;
	start_use_ = start;
}

void Table::StopUsage(const Time& end_use) {
	Time time_in_use = end_use - this->start_use_;
	pay_hours_ += time_in_use.hours_;
	if (time_in_use.minutes_) 
		pay_hours_++;
	in_use_ = in_use_ + time_in_use;
	is_busy_ = false;
}

int Table::CalculateProfit(int cost) {
	return cost * pay_hours_;
}