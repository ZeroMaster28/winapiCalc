#define WIN32_LEAN_AND_MEAN
#include<windows.h>
#include<string>
#include<sstream>
#include"calc.h"
//kalkulator
//#include"calc.h"

//komunikaty przycisków
#define NUM_(i) (1000+i)

//wymiary przycisków i przesuniêcie
#define DISTANCEpx 45
#define DISTANCEmoveX 5
#define DISTANCEmoveY 45
#define BUTTON_SIZE 45

#define key(i) (0x30)+i+48


std::string g_strKlasaOkna = "clOkno";
cCalc Kalkulator;

void refresh(HWND hWindow) //odœwie¿anie ekranu kalkulatora
{
	RECT rc;
	GetClientRect(hWindow, &rc);
	rc.left = 10;
	rc.bottom = 40;
	rc.top = 5;
	rc.right = 180;
	SetFocus(hWindow);
	InvalidateRect(hWindow, &rc, true);

}

LRESULT CALLBACK WindowEventProc(HWND hWindow, UINT uMsg,
	WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CLOSE:
		DestroyWindow(hWindow);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	
	case WM_KEYDOWN: //obs³uga zdarzeñ z klawiatury
	{
		switch ((int)wParam)
		{
		case VK_ESCAPE:
			DestroyWindow(hWindow);
			break;
		case key(7):Kalkulator.decode(NUM_(4)); break;
		case key(8):Kalkulator.decode(NUM_(5)); break;
		case key(9):Kalkulator.decode(NUM_(6)); break;
		case key(4):Kalkulator.decode(NUM_(8)); break;
		case key(5):Kalkulator.decode(NUM_(9)); break;
		case key(6):Kalkulator.decode(NUM_(10)); break;
		case key(1):Kalkulator.decode(NUM_(12)); break;
		case key(2):Kalkulator.decode(NUM_(13)); break;
		case key(3):Kalkulator.decode(NUM_(14)); break;
		case key(0):Kalkulator.decode(NUM_(16)); break;
		case 46: Kalkulator.decode(NUM_(0)); break;
		case 111: Kalkulator.decode(NUM_(1)); break;
		case 106: Kalkulator.decode(NUM_(2)); break;
		case 8: Kalkulator.decode(NUM_(3)); break;
		case 109: Kalkulator.decode(NUM_(7)); break;
		case 107: Kalkulator.decode(NUM_(11)); break;
		case 110: Kalkulator.decode(NUM_(17)); break;
		case 13: Kalkulator.decode(NUM_(19)); break;
		case 38: Kalkulator.decode(NUM_(15)); break;
		case 40: Kalkulator.decode(NUM_(18)); break;
		}
			//odœwie¿amy ekran kalkulatora
		refresh(hWindow);
		return 0;
	}
	case WM_COMMAND://obs³uga zdarzeñ z klikniêæ mysz¹
	{
			
			for (int i = 0; i < 20; i++)
				if (wParam == NUM_(i)) { Kalkulator.decode(NUM_(i));}
				if (wParam == 0x31) Kalkulator.decode(NUM_(12));
			
			//odœwie¿anie ekranu kalkulatora
			refresh(hWindow);
			return 0;
			
		}
	case WM_PAINT://g³ówne rysowanie ekranu kalulatora
		{
			
		std::string text =Kalkulator.display();
		if (text.length()>21)//przerzucanie do nowej linii jeœli jest zbyt d³ugi
		{
			text = text.substr(0, 21) + "\n" + text.substr(21, text.length() - 21);
		}

		RECT rc;
		rc.left = 10;
		rc.bottom = 40;
		rc.top = 5;
		rc.right = 180;

		HBRUSH hBrush=CreateSolidBrush(RGB(141, 247, 64));

		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWindow, &ps);
		FillRect(hdc, &rc,(HBRUSH)WHITE_BRUSH);
		DrawText(hdc,text.c_str(),
			(int)text.length(),
			&rc,
			TA_TOP|TA_RIGHT);
		EndPaint(hWindow, &ps);
		return 0;
		
		}
	}
	

	return DefWindowProc(hWindow, uMsg, wParam, lParam);
}


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR, int nCmdShow)
{
	/* rejestrujemy klasê okna */
	WNDCLASSEX KlasaOkna;

	// wype³niamy strukturê WNDCLASSEX
	ZeroMemory(&KlasaOkna, sizeof(WNDCLASSEX));
	KlasaOkna.cbSize = sizeof(WNDCLASSEX);
	KlasaOkna.hInstance = hInstance;
	KlasaOkna.lpfnWndProc = WindowEventProc;
	KlasaOkna.lpszClassName = g_strKlasaOkna.c_str();
	KlasaOkna.hCursor = LoadCursor(NULL, IDC_ARROW);
	KlasaOkna.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	KlasaOkna.hbrBackground = (HBRUSH)GRAY_BRUSH;

	// rejestrujemy klasê okna
	
	if (!RegisterClassEx(&KlasaOkna))                                   
	{
		MessageBox(NULL, "Rejestracja okna zakoñczona niepowodzeniem.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return false;                                           
	}

	//czcionka do okna
	HFONT hFontOkno = (HFONT)GetStockObject(DEFAULT_GUI_FONT);
	
	//tworzymy g³ówne okno
	HWND hOkno;
	hOkno = CreateWindowEx(NULL, // rozszerzony styl
		g_strKlasaOkna.c_str(), // klasa okna - jej podana nazwa
		"BasicCalc", // tekst na p. tytu³u
		WS_OVERLAPPEDWINDOW - WS_THICKFRAME - WS_MAXIMIZEBOX, // styl okna
		CW_USEDEFAULT, // wspó³rzêdna X
		CW_USEDEFAULT, // wspó³rzêdna Y
		1+(5 * DISTANCEmoveX) + (4 * BUTTON_SIZE), // szerokoœæ
		(2*DISTANCEmoveY)+5*(BUTTON_SIZE), // wysokoœæ
		NULL, // okno nadrzêdne
		NULL, // uchwyt do paska menu
		hInstance, // instancja aplikacji z WinMain
		NULL); // LPVOID lpParam - dodatkowe dane (no needs)
	SendMessage(hOkno, WM_SETFONT, (WPARAM)hFontOkno, 0);



	//czcionka do przycisków
	HFONT hNormalFont = (HFONT)GetStockObject(DEFAULT_GUI_FONT);

	//przyciski
	int num_j = -1;
	HWND hNumButton[20];
	std::string sign[20] = { "C", "/", "*", "<", "7", "8", "9", "-", "4", "5", "6", "+", "1", "2", "3", "()", "0", ",", "+/-", "=" };
	
	for (int i = 0; i < 20; i++)
	{
		if (i % 4 == 0) num_j++;
		hNumButton[i] = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", sign[i].c_str(), WS_CHILD | WS_VISIBLE,
			DISTANCEmoveX+DISTANCEpx*(i%4),DISTANCEmoveY+DISTANCEpx*num_j, BUTTON_SIZE, BUTTON_SIZE, hOkno, (HMENU) NUM_(i), hInstance, NULL);
		
		SendMessage(hNumButton[i], WM_SETFONT, (WPARAM)hNormalFont, 0);
	}
	


	//pokazujemy okno
	ShowWindow(hOkno, nCmdShow);


	MSG msgKomunikat;
	while (GetMessage(&msgKomunikat, NULL, 0, 0))
	{
		TranslateMessage(&msgKomunikat);
		DispatchMessage(&msgKomunikat);
	}
	
	return static_cast<int>(msgKomunikat.wParam);

	
}