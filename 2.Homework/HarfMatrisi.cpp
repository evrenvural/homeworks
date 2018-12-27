#include <iostream>
#include <time.h>
#include <stdlib.h>

/****************************************************************************
**					         SAKARYA ÜNÝVERSÝTESÝ
**			         BÝLGÝSAYAR VE BÝLÝÞÝM BÝLÝMLERÝ FAKÜLTESÝ
**				          BÝLGÝSAYAR MÜHENDÝSLÝÐÝ BÖLÜMÜ
**				           PROGRAMLAMAYA GÝRÝÞÝ DERSÝ
**
**				ÖDEV NUMARASI…...: 2
**				ÖÐRENCÝ ADI......: Evren VURAL
**				ÖÐRENCÝ NUMARASI.: G181210373
**				DERS GRUBU.......: A
****************************************************************************/

// Bir matrisin içine tekrarý olmayacak ve rastgele þekilde alfabedeki tüm harfleri atar ve daha sonra bu matrisi sýralar.

using namespace std;

char matris[5][10];

void matrisOlustur();
void matrisYazdir();
void matrisSirala();

int main() {
	
	srand(time(NULL)); // Random komutunda farklý deðerler atanmasý için.

	matrisOlustur();
	matrisYazdir();
	cout << endl << endl;
	matrisSirala();
	matrisYazdir();
	cout << endl << endl;

	system("pause");
}

char harfUret(bool buyukHarfMi) {

	if (buyukHarfMi)
	{
		return rand() % (90 - 65 + 1) + 65; //Büyük harflerin Ascii'deki karþýlýðý için 65'ten 90'a kadar rastgele sayý üretir.
	}
	else
	{
		return rand() % (122 - 97 + 1) + 97; //Küçük harflerin Ascii'deki karþýlýðý için 97'den 122'a kadar rastgele sayý üretir.
	}
		
}

bool kontrol(char sayi) { // Üretilen harfin daha önce dizide olup olmadýðýný kontrol eder. Eðer var ise false, yok ise true döner.
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (matris[i][j] == sayi)
			{
				return false;
			}
		}
	}
	return true;
}

void matrisOlustur() {
	
	char geciciHarf;

	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (j%2==0) // Bir küçük harf, bir büyük harf oluþturmak için.
			{
				do 
				{
					geciciHarf = harfUret(true); // Büyük harf üretir.
				} while (!kontrol(geciciHarf)); // Üretilen harf, kontrol fonksiyonuna gider ve kontrol fonksiyonu false döndüðü sürece harf üretmeye devam eder. 

				matris[i][j] = geciciHarf;
			}
			else
			{
				do
				{
					geciciHarf = harfUret(false); // Küçük harf üretir.
				} while (!kontrol(geciciHarf)); // Üretilen harf, kontrol fonksiyonuna gider ve kontrol fonksiyonu false döndüðü sürece harf üretmeye devam eder.

				matris[i][j] = geciciHarf;
			}
			
		}
	}
}

void matrisYazdir() {
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			cout << matris[i][j] << " ";
		}
		cout << endl;
	}
}

void matrisSirala() { //
	
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			for (int k = 0; k < 5; k++)
			{
				for (int l = 0; l < 10; l++)
				{
					if (matris[i][j] < matris[k][l]) // Eðer harf kendinden sonrakinden küçük ise küçük olan sola, büyük olan saða gider.
					{
						char gecici = matris[i][j];
						matris[i][j] = matris[k][l];
						matris[k][l] = gecici;
					}
				}
			}

		}
	}
}