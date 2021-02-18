#pragma once
#include <vector>


class BalanceSheet
{
public:

	struct gunStatProduct
	{
		int value;
		int cost;
		int refund;
	};

	std::vector<gunStatProduct> damage = 
	{ 
		{ 1,    0,   0},
		{ 2,    3,   2}, 
		{ 3,    5,   4},
		{ 4,   10,   8},
		{ 5,   20,  16},
		{ 6,   50,  40},
		{ 7,  100,  80},
		{ 8,  200, 160},
		{ 9,  500, 400},
		{10, 1000, 800},
	};

	std::vector<gunStatProduct> speed =
	{
		{ 100,    0,   0},
		{ 200,    3,   2},
		{ 300,    5,   4},
		{ 400,   10,   8},
		{ 500,   20,  16},
		{ 600,   50,  40},
		{ 700,  100,  80},
		{ 800,  200, 160},
		{ 900,  500, 400},
		{1000, 1000, 800},
	};

	std::vector<gunStatProduct> roundsPerShot =
	{
		{ 1,    0,   0},
		{ 3,    3,   2},
		{ 5,    5,   4},
		{ 10,   10,   8}
	};

	std::vector<gunStatProduct> spread =
	{
		{ 50,    0,   0},
		{ 40,    3,   2},
		{ 30,    5,   4},
		{ 20,   10,   8},
		{ 10,   20,  16},
		{ 5,   50,  40}
	};

	std::vector<gunStatProduct> AmmoCount =
	{
		{ 6,    0,   0},
		{ 7,    3,   2},
		{ 11,    5,   4},
		{ 16,   10,   8},
		{ 21,   20,  16},
		{ 32,   50,  40},
		{ 64,  100,  80},
		{ 101,  200, 160},
		{ 501,  500, 400},
		{1001, 1000, 800},
	};
};

