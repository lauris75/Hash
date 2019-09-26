#include <sekmes.h>

std::vector<std::string> Nuskaitymas()
{
	std::string pavadinimas;
	std::vector<std::string> eilutes;
	std::cout << "Iveskite nuskaitomo failo pavadinima - ";
	std::cin >> pavadinimas;
	pavadinimas = pavadinimas + ".txt";
	std::ifstream PD(pavadinimas);
	if (PD)
	{
		while (!PD.eof())
		{
			std::getline(PD, pavadinimas);
			eilutes.push_back(pavadinimas);
		}
		PD.close();
	}
	else
	{
		std::cout << "Failo su tokiu pavadinimu aplankale nera, isitikinkite, kad jis yra programos aplankale..." << std::endl;
		eilutes = Nuskaitymas();
	}
	return eilutes;
}

std::vector<std::string> GetString()
{
	std::vector<std::string> eilute;
	std::string t;
	for (int i = 0; i < 1; i++) {
		std::cout << "Pasirinkite, kaip norite ivesti sifruojama eilute (ranka ar failas)? ";
		std::cin >> t;
		if (t != "ranka" && t != "failas")
		{
			i--;
			std::cout << "Klaidingai ivesta..." << std::endl;
		}
	}
	if (t == "failas") eilute = Nuskaitymas();
	else {
		signed int temp;
		for (int i = 0; i < 1; i++) {
			std::cout << "Iveskite, kiek bus hash'uojamu eiluciu: ";
			std::cin >> temp;
			if (std::cin.fail() || temp < 1)
			{
				std::cin.clear();
				std::cin.ignore();
				std::cout << "Kazka blogai ivedei, bandyk vel... " << std::endl;
				i--;
			}
		}
		temp++;
		for (int i = 0; i < temp; i++)
		{
			if (i != 0)std::cout << "Iveskite hash'uojama eilute:" << std::endl;
			std::getline(std::cin, t);
			eilute.push_back(t);
		}
	}
	eilute.erase(eilute.begin());
	return eilute;
}

std::vector<std::string> Hashinimas(std::vector<std::string> eilutes)
{
	std::vector<int> skaiciai;
	std::vector<std::string> hex;
	int a;
	for (int i = 0; i < eilutes.size(); i++)
	{
		sekmes l;
		for (int o = 0; o < eilutes.at(i).size(); o++)
		{
			a = int(eilutes.at(i).at(o));
			l.daugyba(a+o);
		}
		l.hashinimas();
		hex.push_back(l.GetHex());
		l.clear();
	}
	return hex;
}

void spausdinimas(std::vector<std::string> hex)
{
	std::ofstream RZ("hashai.txt");
	for (int i = 0; i < hex.size(); i++)
	{
		RZ << hex.at(i) << std::endl;
	}
}

int main()
{
	std::vector<std::string> eilute = GetString();
	auto begin = std::chrono::high_resolution_clock::now();
	std::vector<std::string> hex = Hashinimas(eilute);
	auto end = std::chrono::high_resolution_clock::now();
	std::cout << "Hashinimui prireike " << std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count() << " nanosekundziu" << std::endl;
	spausdinimas(hex);
	return 0;
}