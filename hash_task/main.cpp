#include <iostream>
#include <filesystem>
#include <sstream>
#include "hash.hpp"
#include <fstream>
#include <vector>


void get_filenames(const std::string &path, std::vector<std::string> &filenames)
{
	for (const auto &entry : std::filesystem::directory_iterator(path))
		if (entry.is_regular_file())
			filenames.push_back(entry.path().string());
}

int find_duplicates(const std::vector<std::string> &filenames, int (*hashfunc)(const std::string &))
{
	std::vector<int> hashes;
	int counter_repeats = 0;
	for (auto filename : filenames) {
		std::ifstream file(filename);
		if (!file.is_open())
			return -1;
		std::stringstream buf;
		buf << file.rdbuf();
		int h = hashfunc(buf.str());
		if (std::find(hashes.begin(), hashes.end(), h) != hashes.end())
			counter_repeats++;
		else
			hashes.push_back(h);
		file.close();
	}
	return counter_repeats;
}

int main()
{
	const int funcs_count = 4;
	const std::string funcs_names[funcs_count] = {"CRC", "PJW", "BUZ", "CPP"};
	const std::string dir = "out";

	std::vector<std::string> filenames;
	filenames.reserve(600);
	get_filenames(dir, filenames);
	make_rand();

	int (*hashes[])(const std::string &) = {hash_crc_func, hash_pjw_func, hash_buz_func, string_to_hash};

	for (int i = 0; i < funcs_count; i++) {
		auto time_start = clock();
		int count_files = find_duplicates(filenames, hashes[i]);

		std::cout << "Hash func name - " << funcs_names[i] << " ";
		std::cout << "time - " << clock() - time_start << "ms, ";
		std::cout << "files reapeated - " << count_files << "\n";
	}
	return 0;
}