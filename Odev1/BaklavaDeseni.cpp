#include <iostream>

using namespace std;

/****************************************************************************
**					        SAKARYA �N�VERS�TES�
**			         B�LG�SAYAR VE B�L���M B�L�MLER� FAK�LTES�
**				        B�LG�SAYAR M�HEND�SL��� B�L�M�
**				          PROGRAMLAMAYA G�R��� DERS�
**
**				�DEV NUMARASI�...: 1
**				��RENC� ADI......: Evren VURAL
**				��RENC� NUMARASI.: G181210373
**				DERS GRUBU.......: A
****************************************************************************/

// Bu program console ekran�nda y�ld�zlar ile baklava deseni olu�turur. 


int main() {
	// 1. K�s�m

	int boslukSayaci = 2;
	for (int i = 5; i >= 1; i--) // A�a��ya do�ru 5 sat�r y�ld�z �izebilmek i�in
	{
		for (int j = 0; j < i; j++) // Sa� tarafa do�ru 5'ten ba�lay�p 1'e kadar azalarak y�ld�zlar� �izer. 
		{
			cout << "* ";
		}
		for (int j = 0; j < boslukSayaci; j++) // 2'den ba�lay�p 4'er artarak bo�luklar� bast�r�r.
		{
			cout << " ";
		}
		boslukSayaci += 4;
		for (int j = 0; j < i; j++) // Bo�luklardan dolay� �ekil �telenir ve ayn� y�ld�zlar tekrar yazd�r�l�r.
		{
			cout << "* ";
		}
		cout << endl;
	}

	cout << endl;
	
	// 2. K�s�m

	boslukSayaci -= 4;
	
	for (int i = 1; i <= 5; i++) // A�a��ya do�ru 5 sat�r y�ld�z �izebilmek i�in
	{
		for (int j = 0; j < i; j++) // Sa� tarafa do�ru 1'den ba�lay�p 5'e kadar artarak y�ld�zlar� �izer. 
		{
			cout << "* ";
		}
		for (int j = 0; j < boslukSayaci; j++) // 18'den ba�lay�p 4'er azalarak bo�luklar� bast�r�r.
		{
			cout << " ";
		}
		boslukSayaci -= 4;
		for (int j = 0; j < i; j++) // Bo�luklardan dolay� �ekil �telenir ve ayn� y�ld�zlar tekrar yazd�r�l�r.
		{
			cout << "* ";
		}
		cout << endl;
	}

	cout << endl;

	system("Pause");
}