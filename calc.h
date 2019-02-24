#include<string>
#include<vector>

#define TYP_LICZB_KALKULATORA double

class cCalc
{
private:
	//s�u�y tylko do wy�wietlania
	std::vector<std::string> sequence; //ci�g do wy�wietlania na ekranie (musi by� stringiem)
	
	//na nich wykonujemy kalkulacje
	std::vector<std::string> sOperations; //wektor dzia�a� (niekoniecznie musi by� stringiem)
	std::vector<TYP_LICZB_KALKULATORA> vTab;  //wektor liczb 

	bool bVar;//0- operations 1-vTab (stan wpisanych znakk�w)
	int bNest[2]; //liczba nawias�w,[0] lewy i [1] prawy
	int bComa; //miejsca po przecinku
	
public:
	cCalc();
	void decode(unsigned);
	std::string display(void);
	TYP_LICZB_KALKULATORA compute(void);
	friend bool inString(std::string, std::string);

	
};

