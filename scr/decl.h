#pragma once
#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <queue>
#include <map>
#include <vector>
#include <regex>
#include <stdexcept>

void validating(const std::string& file_);

struct Time {
	int hours_;
	int minutes_;
	Time();
	Time(int hours, int minutes);
	bool operator==(const Time& time) const;
	bool operator>(const Time& time) const;
	bool operator<(const Time& time) const;
	Time operator-(const Time& time) const;
	Time operator+(const Time& time) const;
};
std::ostream& operator <<(std::ostream& os, const Time& time);
std::istream& operator >>(std::istream& is, Time& time);

struct Table {
	bool is_busy_;
	Time start_use_;
	Time in_use_;
	int pay_hours_;
	Table();
	void StartUsage(const Time& start);
	void StopUsage(const Time& end);
	int CalculateProfit(int cost);
};

class Club {
	int nums_of_tables_;
	Time open_;
	Time close_;
	int cost_;
	std::ifstream file_;
	std::queue<std::string> queue_;
	std::map<std::string, int> clients_;
	std::vector<Table> tables_;

	void ClientArrive(const Time& time, const std::string& name);
	void ClientSit(const Time& time, const std::string& name, int table);
	void ClientWait(const Time& time, const std::string& name);
	void ClientLeave(const Time& time, const std::string& name);
	void ClubClose();
	void Report();

	void InputEvent(const std::string& line);
	void YouShallNotPass(const Time& time);
	void NotOpenYet(const Time& time);
	void PlaceIsBusy(const Time& time);
	void ClientUnknown(const Time& timet);
	void ICanWaitNoLonger(const Time& time);
	void ClientForcedLeave(const Time& time, std::string client);
	void TakeSitFromQueue(const Time& time, std::string client, int table);
public: 
	Club() : nums_of_tables_(0), cost_(0) {}
	std::string id_1 = "1";
	std::string id_2 = "2";
	std::string id_3 = "3";
	std::string id_4 = "4";
	void Initialize(const std::string& file);
	void Parse(const std::string& file);
};