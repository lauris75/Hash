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
			l.daugyba(a + o);
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

std::vector<char> skirstymas(std::vector<char> mas, std::string hex)
{
	for (int i = 0; i < hex.length(); i++)
	{
		if(hex.at(i) == '0')
		{
			mas.push_back('0');
			mas.push_back('0');
			mas.push_back('0');
			mas.push_back('0');
		}
		if (hex.at(i) == '1')
		{
			mas.push_back('0');
			mas.push_back('0');
			mas.push_back('0');
			mas.push_back('1');
		}
		if (hex.at(i) == '2')
		{
			mas.push_back('0');
			mas.push_back('0');
			mas.push_back('1');
			mas.push_back('0');
		}
		if (hex.at(i) == '3')
		{
			mas.push_back('0');
			mas.push_back('0');
			mas.push_back('1');
			mas.push_back('1');
		}
		if (hex.at(i) == '4')
		{
			mas.push_back('0');
			mas.push_back('1');
			mas.push_back('0');
			mas.push_back('0');
		}
		if (hex.at(i) == '5')
		{
			mas.push_back('0');
			mas.push_back('1');
			mas.push_back('0');
			mas.push_back('1');
		}
		if (hex.at(i) == '6')
		{
			mas.push_back('0');
			mas.push_back('1');
			mas.push_back('1');
			mas.push_back('0');
		}
		if (hex.at(i) == '7')
		{
			mas.push_back('0');
			mas.push_back('1');
			mas.push_back('1');
			mas.push_back('1');
		}
		if (hex.at(i) == '8')
		{
			mas.push_back('1');
			mas.push_back('0');
			mas.push_back('0');
			mas.push_back('0');
		}
		if (hex.at(i) == '9')
		{
			mas.push_back('1');
			mas.push_back('0');
			mas.push_back('0');
			mas.push_back('1');
		}
		if (hex.at(i) == 'A')
		{
			mas.push_back('1');
			mas.push_back('0');
			mas.push_back('1');
			mas.push_back('0');
		}
		if (hex.at(i) == 'B')
		{
			mas.push_back('1');
			mas.push_back('0');
			mas.push_back('1');
			mas.push_back('1');
		}
		if (hex.at(i) == 'C')
		{
			mas.push_back('1');
			mas.push_back('1');
			mas.push_back('0');
			mas.push_back('0');
		}
		if (hex.at(i) == 'D')
		{
			mas.push_back('1');
			mas.push_back('1');
			mas.push_back('0');
			mas.push_back('1');
		}
		if (hex.at(i) == 'E')
		{
			mas.push_back('1');
			mas.push_back('1');
			mas.push_back('1');
			mas.push_back('0');
		}
		if (hex.at(i) == 'F')
		{
			mas.push_back('1');
			mas.push_back('1');
			mas.push_back('1');
			mas.push_back('1');
		}
	}
	return mas;
}

void lyginimas(std::vector<std::string> hex)
{
	int t, v = 0, m = 100, d = 0;
	std::vector<char> pirmas, antras;
	for (int i = 0; i < hex.size(); i++)
	{
		t = 0;
		pirmas = skirstymas(pirmas, hex.at(i));
		antras = skirstymas(antras, hex.at(i + 1));
		for (int y = 0; y < pirmas.size(); y++)
		{
			if (pirmas.at(y) == antras.at(y)) t++;
		}
		t = t * 100;
		t = t / pirmas.size();
		if (t < m)m = t;
		if (t > d)d = t;
		v = v + t;
		i++;
	}
	v = v / hex.size() * 2;
	std::cout << "maziausiai sutapusiu % yra - " << m << std::endl;
	std::cout << "daugiausiai sutapusiu % yra - " << d << std::endl;
	std::cout << "vidurkis sutapusiu % yra - " << v << std::endl;
}

int main()
{
	std::vector<std::string> eilute = GetString();
	std::vector<std::string> hex = Hashinimas(eilute);
	spausdinimas(hex);
	lyginimas(hex);
	return 0;
}