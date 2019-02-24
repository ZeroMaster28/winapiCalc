#include"calc.h"
#include<sstream>
#include<math.h>



#define NUM_(i) (1000+i) //flagi cyferek na kalkulatorze
#define PRECYZJA 10//precyzja wyœwietlanych liczb na ekranie kalkulatora
#define TYP TYP_LICZB_KALKULATORA
std::vector<unsigned> g_comaHelper;// pozycja przecinka ka¿dej z liczb, w przypadku cofania
static int nError; // czy dzielimy przez 0
std::vector<bool> bMinus;

using namespace std;


cCalc::cCalc()
{
	
	this->bVar = false;
	bNest[0] = 0;
	bNest[1] = 0;
	this->bComa = false;
}

void cCalc::decode(unsigned u)
{
	nError = 0;
	if ((!sequence.empty()) && (vTab.empty())) sequence.clear();//czyscimy ekran z wyniku podczas wprowadzania nowych danych
	bool temp_operation = false;

	if (!sOperations.empty())
	{
		if (sOperations.back() == ")") temp_operation = true;
	}
	if (bMinus.empty()) bMinus.push_back(false);//domyœlna flaga dla znaku pierwszej liczby w ci¹gu
	int state = -1; //pomocniczna
	switch (u)//selekcja komunikatu;
	{
	
	//czyszczenie ekraniku
	case NUM_(0):
	{ 
	sequence.clear();
	vTab.clear();
	bMinus.clear();
	bVar = false;
	bComa = false;
	bNest[0] = 0;
	bNest[1] = 0;
	}break;

	//operacje
	case NUM_(1):
	{
		if (!vTab.empty() && (bVar == 1 || temp_operation))
		{ 
		sOperations.push_back("/"); 
		sequence.push_back("/");
		bMinus.push_back(false);
		if (vTab.size()>g_comaHelper.size()) g_comaHelper.push_back(bComa); //wrzuca stan przecinka dla nowej liczby
		if (vTab.size() <= g_comaHelper.size()) g_comaHelper[vTab.size() - 1] = bComa; //poprawia stan przecinka w przypadku cofania i dok³adania kolejnych cyfr
		bVar = 0; bComa = 0; 
		}
	} break;
	case NUM_(2):
	{
		if (!vTab.empty() && (bVar == 1||temp_operation))
		{ 
		sOperations.push_back("*");
		sequence.push_back("*"); 
		bMinus.push_back(false);
		if (vTab.size()>g_comaHelper.size()) g_comaHelper.push_back(bComa);
		if (vTab.size() <= g_comaHelper.size()) g_comaHelper[vTab.size() - 1] = bComa;
		bVar = 0; bComa = 0; 
		}
	} break;
	case NUM_(7):
	{
		if (!vTab.empty() && (bVar == 1||temp_operation))
		{ 
			sOperations.push_back("-");
			sequence.push_back("-");
			bMinus.push_back(false);
			if (vTab.size()>g_comaHelper.size()) g_comaHelper.push_back(bComa);
			if (vTab.size() <= g_comaHelper.size()) g_comaHelper[vTab.size() - 1] = bComa;
			bVar = 0; bComa = 0; 
		}
	} break;
	case NUM_(11):
	{
		if (!vTab.empty() && (bVar == 1 || temp_operation))
		{ 
			sOperations.push_back("+"); 
			sequence.push_back("+"); 
			bMinus.push_back(false);
			if (vTab.size()>g_comaHelper.size()) g_comaHelper.push_back(bComa);
			if (vTab.size() <= g_comaHelper.size()) g_comaHelper[vTab.size() - 1] = bComa;
			bVar = 0; bComa = 0; 
		}
	} break;
	//liczby
	case NUM_(4): state = 7; break;
	case NUM_(5): state = 8; break;
	case NUM_(6): state = 9; break;
	case NUM_(8): state = 4; break;
	case NUM_(9): state = 5; break;
	case NUM_(10): state = 6; break;
	case NUM_(12): state = 1; break;
	case NUM_(13): state = 2; break;
	case NUM_(14): state = 3; break;
	case NUM_(16): state = 0; break;
	//pozosta³e
	case NUM_(3): //cofanie znaku
	{
		if (sequence.size() == 1)
		{
			vTab.pop_back();
			sequence.pop_back();
			bVar = 0;
			bComa = 0;
			g_comaHelper.clear();
			//bMinus.clear();
		}
		if (sequence.size() > 1)
		{
			if (bVar == 0) //usuwamy znak operacji arytmetycznej
			{
				bool pom123 = inString(sequence[sequence.size() - 2], "+-/*)(");
				if (inString(sequence[sequence.size() - 2], "+-/*)(")) bVar = 0;
				else
				{
					bVar = 1;
					bComa = g_comaHelper[vTab.size()-1];
				}
				if (sOperations.back() != "(" && sOperations.back() != ")") bMinus.pop_back();
				if (sequence.back() == "(") bNest[0]--;
				else if (sequence.back() == ")") bNest[1]--;
				sequence.pop_back();
				sOperations.pop_back();
				
			}
			else if (bVar == 1) //usuwamy liczbê
			{
				sequence.pop_back();
				vTab.pop_back();
				

				bComa = 0;
				bVar = 0;

			}

		}

	}break;
	case NUM_(15): //nawiasy
	{
		if (bVar == 0)
		{
			if (sOperations.empty()) break;//zak³adamy ¿e nie ma nawiasu "(" jako pierwszego znaku, mo¿na zmieniæ
			if (sOperations.back() == ")")
			{
				if (bNest[1]<bNest[0])
				{ 
				sOperations.push_back(")");
				sequence.push_back(")");
				bNest[1]++;
				bVar = 0;
				}
			}
			else{
				sOperations.push_back("(");
				sequence.push_back("(");
				bNest[0]++;
				bVar = 0;
			}
		}
		if (bVar == 1 && bNest[1]<bNest[0])
		{
			sOperations.push_back(")");
			sequence.push_back(")");
			bNest[1]++;
			bVar = 0;
			if (vTab.size()>g_comaHelper.size()) g_comaHelper.push_back(bComa);
			if (vTab.size() <= g_comaHelper.size()) g_comaHelper[vTab.size() - 1] = bComa;
		}
		
		
	}break;
	case NUM_(17):{if (bComa == 0) bComa = 1; } break;
	case NUM_(18)://zmiana znaku
	{
		
		if (!bMinus.empty())
		{
			if(bVar==0)bMinus.back() = !bMinus.back();
			
		}
	}break;
	case NUM_(19):
	{	
		
		while (bNest[0] > bNest[1])
		{
			sOperations.push_back(")");
			sequence.push_back(")");
			bNest[1]++;
			bVar = 0;
		}


		if ((bVar==1||bNest[1]>0)&& (!sOperations.empty())) //stan w którym mo¿emy dokonaæ obliczeñ
		{ 
		

		//zerujemy stan kalkulatora
		double result=compute();
		sequence.clear();
		sOperations.clear();
		vTab.clear();
		bMinus.clear();

		bVar = false;
		bComa = false;
		bNest[0] = 0;
		bNest[1] = 0;
		
		//wypisywany wynik
		std::stringstream strumyk;
		strumyk.precision(PRECYZJA);
		strumyk << result;
		sequence.push_back(strumyk.str());
		strumyk.str("");
		}
	}break;
	default: break;

	}
 
	bool pom_nest; //czy mo¿emy wpisywaæ liczbê w zale¿noœci od nawiasu ")"
	if (sOperations.empty()) pom_nest = true;
	if ((!sOperations.empty()) && (inString(sOperations[sOperations.size() - 1], ")"))) pom_nest = false;
	if ((!sOperations.empty()) && (!inString(sOperations[sOperations.size() - 1], ")"))) pom_nest = true;

	if (pom_nest)
	{ 
	std::stringstream str;
	str.precision(PRECYZJA);
		if (state >= 0 && state <= 9)
		{
			{if (bVar == 0)
			{
				vTab.push_back(state);
				if (bMinus.back() == true) vTab.back() *= (-1);

				str << vTab[vTab.size()-1];
				sequence.push_back(str.str());
				str.str("");
			}
			if (bVar == 1) {
				if (bComa == 0)
				{
					if (bMinus.back() == true) vTab.back() *= (-1);
					vTab[vTab.size() - 1] *= 10;
					vTab[vTab.size() - 1] += state;
					if (bMinus.back() == true) vTab.back() *= (-1);

					str << vTab[vTab.size()-1];
					sequence.pop_back();
					sequence.push_back(str.str());
					str.str("");

				}
				if (bComa > 0)
				{
					if (bMinus.back() == true) vTab.back() *= (-1);
					vTab[vTab.size() - 1] += state * pow(0.1, bComa);
					bComa++;
					if (bMinus.back() == true) vTab.back() *= (-1);

					str << vTab[vTab.size()-1];
					sequence.pop_back();
					sequence.push_back(str.str());
					str.str("");
				}
			}
			bVar = 1;
			} 
		}
	
	}
	}

std::string cCalc::display(void)
{
	if (nError == 1) return "Error";
	if (sequence.empty()) return "0";
	else
	{
		std::string actual = "";
		for (int i = 0; i < sequence.size(); i++) actual += sequence[i];

		return actual;
	}

}

bool inString(std::string a, std::string b)
{
	if (b == "") return false;

	
	for (int i = 0; i < b.length(); i++)
		if (a[a.size()-1] == b[i]) return true;
	
	
	return false;
}

int inVector(std::string str, std::vector<std::string> vec) //do sprawdzania czy string jest w wektorze stringów
{
	if (vec.empty()) return 0;
	if (str.size() == 1)
	{
		for (int i = vec.size()-1; i >0; i--) if (str == vec[i]) return i + 1;
	}
	if (str.length() == 2)
	{
		for (int i = 0; i < vec.size(); i++)
		{
			if ((std::string(1, str[0]) == vec[i]) || (std::string(1, str[1]) == vec[i])) return i + 1;
		}
	}

	return 0;

}

TYP poorCompute(std::vector<std::string> str)
{
	std::stringstream napis;
	napis.precision(PRECYZJA);

	int place = -1;
	std::vector<std::string> pom = str;
		
	while (place = inVector("*/", pom))
	{
		std::string type = pom[place - 1];
		TYP var;
		if (type == "/" && (std::stod(pom[place]) == 0))
		{
			nError = 1;
			return 0;
		}
		if (type == "*")var = std::stod(pom[place - 2]) * std::stod(pom[place]);
		if (type == "/")var = std::stod(pom[place - 2]) / std::stod(pom[place]);
		
		pom.erase(pom.begin() + place - 2, pom.begin() + place + 1);
		napis << var;
		if (pom.empty() || pom.size()<place) pom.push_back(napis.str());
		else pom.insert(pom.begin() + place - 2, napis.str());
		napis.str("");
	}

	while (place = inVector("+-", pom))
	{
		std::string type = pom[place - 1];
		TYP var;
		if (type == "+")var = std::stod(pom[place - 2]) + std::stod(pom[place]);
		if (type == "-")var = std::stod(pom[place - 2]) - std::stod(pom[place]);

		pom.erase(pom.begin() + place - 2, pom.begin() + place + 1);
		napis << var;
		if (pom.empty() || pom.size()<place) pom.push_back(napis.str());
		else pom.insert(pom.begin() + place - 2, napis.str());
		napis.str("");
	}


	return std::stod(pom[0]);
}
TYP_LICZB_KALKULATORA cCalc::compute(void)
{
	if (bNest[0] == 0) return poorCompute(sequence);

	std::stringstream napis;
	napis.precision(PRECYZJA);
	std::vector<std::string> pom = sequence;
	int place = 0;

	while (place = inVector("(", pom))
	{
		int place1 = -1;//miejsce drugiego nawiasu
		for (int i = place; i < pom.size(); i++) 
		{

			if (pom[i] == ")")
			{
				place1 = i + 1;
				break;
			}
		}
		
		std::vector<std::string> str;
		for (int i = place ; i < place1-1; i++) str.push_back(pom[i]);

		TYP var = poorCompute(str);

		pom.erase(pom.begin() + place - 1, pom.begin() + place1);
		napis << var;
		if (pom.empty() || pom.size()<place) pom.push_back(napis.str());
		else pom.insert(pom.begin() + place - 1, napis.str());
		napis.str("");

	}

	return poorCompute(pom);
}//g³ówny compute kalkulatora





