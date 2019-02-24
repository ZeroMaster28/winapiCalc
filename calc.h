#include<string>
#include<vector>

#define TYP_LICZB_KALKULATORA double

class cCalc
{
private:
	//s³u¿y tylko do wyœwietlania
	std::vector<std::string> sequence; //ci¹g do wyœwietlania na ekranie (musi byæ stringiem)
	
	//na nich wykonujemy kalkulacje
	std::vector<std::string> sOperations; //wektor dzia³añ (niekoniecznie musi byæ stringiem)
	std::vector<TYP_LICZB_KALKULATORA> vTab;  //wektor liczb 

	bool bVar;//0- operations 1-vTab (stan wpisanych znakków)
	int bNest[2]; //liczba nawiasów,[0] lewy i [1] prawy
	int bComa; //miejsca po przecinku
	
public:
	cCalc();
	void decode(unsigned);
	std::string display(void);
	TYP_LICZB_KALKULATORA compute(void);
	friend bool inString(std::string, std::string);

	
};

