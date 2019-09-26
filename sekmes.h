#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <math.h>
#include <chrono>

class sekmes
{
public:
	sekmes()
	{
		intas.reserve(1);
		intas.push_back(1);
	};

	~sekmes(){};

	void clear()
	{
		intas.clear();
	}

	void sutvarkymas()
	{
		int t;
		for (int i = 0; i < intas.size(); i++)
		{
			t = intas.at(i) / 1000000;
			if (intas.at(i) > 1000000) {
				if (i + 1 == intas.size())didinimas(t);
				else intas.at(i + 1) = intas.at(i + 1) + t;
				intas.at(i) = intas.at(i) % 1000000;
			}
		}
	}

	void sutvarkymas2()
	{
		int t;
		while (intas.at(5) > 339)
		{
			for (int i = 0; i < intas.size(); i++)
			{
				t = intas.at(i) % 10;
				intas.at(i) = intas.at(i) / 10;
				if (i != 0) intas.at(i - 1) = intas.at(i - 1) + t * 100000;
			}
		}
	}

	void daugyba(int a)
	{
		int t;
		for (int i = 0; i < intas.size(); i++)
		{
			intas.at(i) = intas.at(i) * a;

		}
		sutvarkymas();
	}

	void hashinimas()
	{
		int  t, i = 2;
		while (intas.size() < 9)
		{
			daugyba(i);
			i++;
		};
		for (int y = 0; y < 5; y++)
		{
			daugyba(i);
			i++;
		};
		for (int i = 0; i < intas.size(); i++)
		{
			t = intas.at(i) % 1000;
			intas.at(i) = intas.at(i) / 1000;
			if (i != 0) intas.at(i - 1) = intas.at(i - 1) + (t * 1000);
		};
		intas.erase(intas.begin());
	}

	std::string GetHex()
	{
		sutvarkymas2();
		std::string hex = "";
		int  r;
		char ati[] = { '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F' };
		while (intas.at(0) > 0)
		{
			r = intas.at(0) % 16;
			hex = ati[r] + hex;
			for (int i = 0; i < intas.size(); i++)
			{
				if (i != 0) intas.at(i-1) = intas.at(i-1) + ((intas.at(i) % 16) * 1000000);
				intas.at(i) = intas.at(i) / 16;
			}
		}
		return hex;
	};

private:
	std::vector<int> intas;

	inline void didinimas(int a)
	{
		intas.push_back(a);
	};
};