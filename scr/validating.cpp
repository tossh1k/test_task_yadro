#include "decl.h"

void validating(const std::string& file_) {
	std::regex valid_int{ "^[0-9]+$" };
	std::regex valid_table{ "[0-9]+$" };
	std::regex valid_time{ "^([0-1][0-9])|(2[0-3]):[0-5][0-9]" };
	std::regex valid_work_time{ "^([0-1][0-9]|2[0-3]):[0-5][0-9]\\s([0-1][0-9]|2[0-3]):[0-5][0-9]$" };
	std::regex valid_command{ "^([0-1][0-9]|2[0-3]):[0-5][0-9]\\s(1|3|4)\\s[a-z1-9_-]+$" };
	std::regex valid_command_id_2{ "^([0-1][0-9]|2[0-3]):[0-5][0-9]\\s2\\s[a-z1-9_-]+\\s[1-9][0-9]*$" };

	std::ifstream file(file_);
	std::string line;
	std::getline(file, line);
	if (!std::regex_match(line, valid_int))
		throw std::runtime_error(line + "\nInvalid number of tables.");
	int num_of_tables = stoi(line);

	std::getline(file, line);
	{
		if (!std::regex_match(line, valid_work_time))
			throw std::runtime_error(line + "\nInvalid working hours.");

		std::string h = { line[0], line[1] };
		std::string m = { line[3], line[4] };
		Time open(std::stoi(h), std::stoi(m));

		h = { line[6], line[7] };
		m = { line[9], line[10] };
		Time close(std::stoi(h), std::stoi(m));

		if (open > close) 
			throw std::runtime_error(line + "\nInvalid working hours.");
		
	}
	std::getline(file, line);
	if (!std::regex_match(line, valid_int)) 
		throw std::runtime_error(line + "\nInvalid cost.");

	std::getline(file, line);
	if (!(std::regex_match(line, valid_command) || std::regex_match(line, valid_command_id_2))) 
		throw std::runtime_error(line + "\nInvalid command.");

	std::string h = { line[0], line[1] };
	std::string m = { line[3], line[4] };
	Time prev_event(std::stoi(h), std::stoi(m));

	while (std::getline(file, line)) {
		if (!(std::regex_match(line, valid_command) || std::regex_match(line, valid_command_id_2))) 
			throw std::runtime_error(line + "\nInvalid command.");

		std::string h = { line[0], line[1] };
		std::string m = { line[3], line[4] };
		Time curr_event(std::stoi(h), std::stoi(m));
		if (curr_event < prev_event) 
			throw std::runtime_error(line + "\nInvalid sequence of events.");

		if (std::regex_match(line, valid_command_id_2)) {
			std::smatch sm;
			std::regex_search(line, sm, valid_table);
			if (stoi(sm[0]) > num_of_tables || stoi(sm[0]) == 0)
				throw std::runtime_error(line + "\nInvalid command.");
		}
	}
	
	file.seekg(0, std::ios::beg);
	file.close();
}