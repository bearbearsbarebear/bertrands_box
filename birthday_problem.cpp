#include <stdio.h>
#include <chrono>
#include <random>
#include <vector>
#include <algorithm>

/*
 * In probability theory, the birthday problem asks for the probability that, 
 * in a set of n randomly chosen people, at least two will share a birthday. 
 * The birthday paradox is that, counterintuitively, the probability of a shared 
 * birthday exceeds 50% in a group of only 23 people.
*/

bool is_date_valid(int month, int day)
{
	if (month < 1 || month > 12) return false;
	
	if (day < 1 || day > 31) return false;
	
	if (month == 2) {
		return day <= 28;
	} else if (month == 4 || month == 6 || month == 9 || month == 11) {
		return day <= 30;
	}
	
	return true;
}

int main(int argc, char* argv[])
{
	std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());

	std::uniform_int_distribution<int> month_range(1, 12);
	std::uniform_int_distribution<int> day_range(1, 31);

	int total = 10000;
	int collisions = 0;

	for (int _i = 0; _i < total; ++_i) {
		std::vector<std::pair<int, int>> dates;

		for (int i = 0; i < 23; ++i) {
			int month = month_range(rng);
			int day = day_range(rng);

			while (!is_date_valid(month, day)) {
				month = month_range(rng);
				day = day_range(rng);
			}

			dates.emplace_back(month, day);
		}

		for (const auto& date:dates) {
			if (std::count(dates.begin(), dates.end(), date) > 1) {
				++collisions;
				break;
			}
		}
	}

	printf("Number of collisions out of %d tries: %d", total, collisions);

	return 0;
}
