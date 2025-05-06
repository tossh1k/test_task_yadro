#include "decl.h"

void Club::ClientArrive(const Time& time, const std::string& name) {
	if (time < open_ || time > close_) { 
		NotOpenYet(time); 
		return;
	}
	
	auto it = clients_.find(name);
	
	if (it == clients_.end()) {
		clients_[name] = 0;
	}
	else {
		YouShallNotPass(time);
	}
}

void Club::ClientSit(const Time& time, const std::string& name, int table) {
	auto it = clients_.find(name);

	if (it == clients_.end()) {
		ClientUnknown(time);
		return;
	}

	if (tables_[table].is_busy_) {
		PlaceIsBusy(time);
		return;
	}
	else {
		it->second = table;
		tables_[table].StartUsage(time);
	}
}

void Club::ClientWait(const Time& time, const std::string& name) {
	auto it = clients_.find(name);

	if (it == clients_.end()) {
		ClientUnknown(time);
		return;
	}

	for (int i = 1; i <= nums_of_tables_; ++i) {
		if (!tables_[i].is_busy_) {
			ICanWaitNoLonger(time);
			return;
		}
	}

	if (queue_.size() < nums_of_tables_) {
		queue_.push(name);
	}
	else { 
		clients_.erase(name); 
		ClientForcedLeave(time, name);
	}
}

void Club::ClientLeave(const Time& time, const std::string& name) {
	auto it = clients_.find(name);

	if (it == clients_.end()) {
		ClientUnknown(time);
		return;
	}

	if (queue_.front() == name) {
		queue_.pop();
		return;
	}

	if (!queue_.empty() && it->second != 0) {
		clients_[queue_.front()] = it->second;
		tables_[it->second].StopUsage(time);
		tables_[it->second].StartUsage(time);
		TakeSitFromQueue(time, queue_.front(), it->second);
		queue_.pop();
		clients_.erase(name);
		return;
	}

	tables_[it->second].StopUsage(time);
	clients_.erase(name);
}

void Club::ClubClose() {
	for (auto i : clients_) 
		ClientForcedLeave(close_, i.first);
	for (int i = 1; i <= nums_of_tables_; ++i) {
		if (tables_[i].is_busy_ == true)
			tables_[i].StopUsage(close_);
	}
}

void Club::Report() {
	for (int i = 1; i <= nums_of_tables_; ++i) {
		std::cout << i << ' ' << tables_[i].CalculateProfit(cost_) << ' ' << tables_[i].in_use_ << '\n';
	}
}

void Club::InputEvent(const std::string& line) {
	std::cout << line << '\n';
}

void Club::YouShallNotPass(const Time& time) {
	std::cout << time << " 13 YouShallNotPass" << '\n';
}

void Club::NotOpenYet(const Time& time) {
	std::cout << time << " 13 NotOpenYet" << '\n';
}

void Club::PlaceIsBusy(const Time& time) {
	std::cout << time << " 13 PlaceIsBusy" << '\n';
}

void Club::ClientUnknown(const Time& time) {
	std::cout << time << " 13 ClientUnknown" << '\n';
}

void Club::ICanWaitNoLonger(const Time& time) {
	std::cout << time << " 13 ICanWaitNoLonger!" << '\n';
}

void Club::ClientForcedLeave(const Time& time, std::string client) {
	std::cout << time << " 11 " << client << '\n';
}

void Club::TakeSitFromQueue(const Time& time, std::string client, int table) {
	std::cout << time << " 12 " << client << ' ' << table << '\n';
}

void Club::Initialize(const std::string& file) {
	file_.open(file);
	file_ >> nums_of_tables_ >> open_ >> close_ >> cost_;
}

void Club::Parse(const std::string& file) {
	file_.open(file);
	file_ >> nums_of_tables_ >> open_ >> close_ >> cost_;

	for (int i = 0; i <= nums_of_tables_; ++i) {
		Table table;
		tables_.push_back(table);
	}

	std::cout << open_ << '\n';
	while (true) {
	Time curr_time;	std::string id, name;
		file_ >> curr_time >> id >> name;
		if (file_.eof()) break;
		std::cout << curr_time << ' ' << id << ' ' << name;
		if (id == id_1) {
			std::cout << '\n';
			ClientArrive(curr_time, name);
		}
		else if (id == id_2) {
			int table; file_ >> table;
			std::cout << ' ' << table << '\n';
			ClientSit(curr_time, name, table);
		}
		else if (id == id_3) {
			std::cout << '\n';
			ClientWait(curr_time, name);
		}
		else if (id == id_4) {
			std::cout << '\n';
			ClientLeave(curr_time, name);
		}
	}

	ClubClose();
	std::cout << close_ << '\n';
	Report();
	file_.close();
}