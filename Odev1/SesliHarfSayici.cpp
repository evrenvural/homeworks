#include <iostream>
#include <locale.h>					
#include <conio.h>

using namespace std;

/****************************************************************************
**					        SAKARYA ÜNÝVERSÝTESÝ
**			         BÝLGÝSAYAR VE BÝLÝÞÝM BÝLÝMLERÝ FAKÜLTESÝ
**				        BÝLGÝSAYAR MÜHENDÝSLÝÐÝ BÖLÜMÜ
**				          PROGRAMLAMAYA GÝRÝÞÝ DERSÝ
**
**				ÖDEV NUMARASI…...: 2
**				ÖÐRENCÝ ADI......: Evren VURAL
**				ÖÐRENCÝ NUMARASI.: G181210373
**				DERS GRUBU.......: A
****************************************************************************/

// Klavyeden girilen cümledeki sesli harfleri sayar.

int main() {

	setlocale(LC_ALL, "Turkish");

	char cumle = 'a';
	
	int sesliHarfSayaci = 0, aSayaci = 0, eSayaci = 0, oSayaci = 0, uSayaci = 0, iSayaci = 0; // Türkçe karakterler input alýnamýyor, o yüzden türkçe sesli harf tanýmlamadým.
	
	cout << "Cümlenizi Giriniz: (Cümlenizde Türkçe harf kullanmayýnýz.)" <<endl <<endl;
	
	// Enter tuþuna basana kadar döngü devam eder. 
	
	while (cumle != '\r')
	{
		cumle = _getche();

		// Eðer koþulda istenilen harf girilirse o harflere ait sayaçlar birer artar.

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