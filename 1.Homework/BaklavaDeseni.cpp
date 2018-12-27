#include <iostream>

using namespace std;

/****************************************************************************
**					        SAKARYA ÜNÝVERSÝTESÝ
**			         BÝLGÝSAYAR VE BÝLÝÞÝM BÝLÝMLERÝ FAKÜLTESÝ
**				        BÝLGÝSAYAR MÜHENDÝSLÝÐÝ BÖLÜMÜ
**				          PROGRAMLAMAYA GÝRÝÞÝ DERSÝ
**
**				ÖDEV NUMARASI…...: 1
**				ÖÐRENCÝ ADI......: Evren VURAL
**				ÖÐRENCÝ NUMARASI.: G181210373
**				DERS GRUBU.......: A
****************************************************************************/

// Bu program console ekranýnda yýldýzlar ile baklava deseni oluþturur. 


int main() {
	// 1. Kýsým

	int boslukSayaci = 2;
	for (int i = 5; i >= 1; i--) // Aþaðýya doðru 5 satýr yýldýz çizebilmek için
	{
		for (int j = 0; j < i; j++) // Sað tarafa doðru 5'ten baþlayýp 1'e kadar azalarak yýldýzlarý çizer. 
		{
			cout << "* ";
		}
		for (int j = 0; j < boslukSayaci; j++) // 2'den baþlayýp 4'er artarak boþluklarý bastýrýr.
		{
			cout << " ";
		}
		boslukSayaci += 4;
		for (int j = 0; j < i; j++) // Boþluklardan dolayý þekil ötelenir ve ayný yýldýzlar tekrar yazdýrýlýr.
		{
			cout << "* ";
		}
		cout << endl;
	}

	cout << endl;
	
	// 2. Kýsým

	boslukSayaci -= 4;
	
	for (int i = 1; i <= 5; i++) // Aþaðýya doðru 5 satýr yýldýz çizebilmek için
	{
		for (int j = 0; j < i; j++) // Sað tarafa doðru 1'den baþlayýp 5'e kadar artarak yýldýzlarý çizer. 
		{
			cout << "* ";
		}
		for (int j = 0; j < boslukSayaci; j++) // 18'den baþlayýp 4'er azalarak boþluklarý bastýrýr.
		{
			cout << " ";
		}
		boslukSayaci -= 4;
		for (int j = 0; j < i; j++) // Boþluklardan dolayý þekil ötelenir ve ayný yýldýzlar tekrar yazdýrýlýr.
		{
			cout << "* ";
		}
		cout << endl;
	}

	cout << endl;

	system("Pause");
}