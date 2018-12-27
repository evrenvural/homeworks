#include <iostream>
#include <time.h>
#include <stdlib.h>

/****************************************************************************
**					         SAKARYA �N�VERS�TES�
**			         B�LG�SAYAR VE B�L���M B�L�MLER� FAK�LTES�
**				          B�LG�SAYAR M�HEND�SL��� B�L�M�
**				           PROGRAMLAMAYA G�R��� DERS�
**
**				�DEV NUMARASI�...: 2
**				��RENC� ADI......: Evren VURAL
**				��RENC� NUMARASI.: G181210373
**				DERS GRUBU.......: A
****************************************************************************/

// Bir matrisin i�ine tekrar� olmayacak ve rastgele �ekilde alfabedeki t�m harfleri atar ve daha sonra bu matrisi s�ralar.

using namespace std;

char matris[5][10];

void matrisOlustur();
void matrisYazdir();
void matrisSirala();

int main() {
	
	srand(time(NULL)); // Random komutunda farkl� de�erler atanmas� i�in.

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
		return rand() % (90 - 65 + 1) + 65; //B�y�k harflerin Ascii'deki kar��l��� i�in 65'ten 90'a kadar rastgele say� �retir.
	}
	else
	{
		return rand() % (122 - 97 + 1) + 97; //K���k harflerin Ascii'deki kar��l��� i�in 97'den 122'a kadar rastgele say� �retir.
	}
		
}

bool kontrol(char sayi) { // �retilen harfin daha �nce dizide olup olmad���n� kontrol eder. E�er var ise false, yok ise true d�ner.
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
			if (j%2==0) // Bir k���k harf, bir b�y�k harf olu�turmak i�in.
			{
				do 
				{
					geciciHarf = harfUret(true); // B�y�k harf �retir.
				} while (!kontrol(geciciHarf)); // �retilen harf, kontrol fonksiyonuna gider ve kontrol fonksiyonu false d�nd��� s�rece harf �retmeye devam eder. 

				matris[i][j] = geciciHarf;
			}
			else
			{
				do
				{
					geciciHarf = harfUret(false); // K���k harf �retir.
				} while (!kontrol(geciciHarf)); // �retilen harf, kontrol fonksiyonuna gider ve kontrol fonksiyonu false d�nd��� s�rece harf �retmeye devam eder.

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
					if (matris[i][j] < matris[k][l]) // E�er harf kendinden sonrakinden k���k ise k���k olan sola, b�y�k olan sa�a gider.
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