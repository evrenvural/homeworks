#include <iostream>
#include <locale.h>					
#include <conio.h>

using namespace std;

/****************************************************************************
**					        SAKARYA �N�VERS�TES�
**			         B�LG�SAYAR VE B�L���M B�L�MLER� FAK�LTES�
**				        B�LG�SAYAR M�HEND�SL��� B�L�M�
**				          PROGRAMLAMAYA G�R��� DERS�
**
**				�DEV NUMARASI�...: 2
**				��RENC� ADI......: Evren VURAL
**				��RENC� NUMARASI.: G181210373
**				DERS GRUBU.......: A
****************************************************************************/

// Klavyeden girilen c�mledeki sesli harfleri sayar.

int main() {

	setlocale(LC_ALL, "Turkish");

	char cumle = 'a';
	
	int sesliHarfSayaci = 0, aSayaci = 0, eSayaci = 0, oSayaci = 0, uSayaci = 0, iSayaci = 0; // T�rk�e karakterler input al�nam�yor, o y�zden t�rk�e sesli harf tan�mlamad�m.
	
	cout << "C�mlenizi Giriniz: (C�mlenizde T�rk�e harf kullanmay�n�z.)" <<endl <<endl;
	
	// Enter tu�una basana kadar d�ng� devam eder. 
	
	while (cumle != '\r')
	{
		cumle = _getche();

		// E�er ko�ulda istenilen harf girilirse o harflere ait saya�lar birer artar.

		if (cumle == 'a' || cumle == 'A')
		{
			sesliHarfSayaci++;
			aSayaci++;
		}
		
		else if (cumle == 'e' || cumle == 'E')
		{
			sesliHarfSayaci++;
			eSayaci++;
		}

		else if (cumle == 'o' || cumle == 'O')
		{
			sesliHarfSayaci++;
			oSayaci++;
		}

		else if (cumle == 'u' || cumle == 'U')
		{
			sesliHarfSayaci++;
			uSayaci++;
			
		}
		else if (cumle == 'i' || cumle == 'I') {
			sesliHarfSayaci++;
			iSayaci++;
		}

	}
	
	cout << endl << endl;
	
	cout << "A harfi: " << aSayaci << endl;
	cout << "E harfi: " << eSayaci << endl;
	cout << "O harfi: " << oSayaci << endl;
	cout << "U harfi: " << uSayaci << endl;
	cout << "I/i harfi: " << iSayaci << endl << endl;
	cout << "Toplam Sesli Harf: " << sesliHarfSayaci << endl << endl ;
	
	system("pause");
}