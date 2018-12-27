#include <iostream>
#include <iomanip>

using namespace std;

/****************************************************************************
**							SAKARYA �N�VERS�TES�
**			         B�LG�SAYAR VE B�L���M B�L�MLER� FAK�LTES�
**						B�LG�SAYAR M�HEND�SL��� B�L�M�
**				          PROGRAMLAMAYA G�R��� DERS�
**
**				�DEV NUMARASI�...:	3
**				��RENC� ADI......:	Evren VURAL	
**				��RENC� NUMARASI.:	G181210373
**				DERS GRUBU.......:	2. ��retim A Grubu
****************************************************************************/

// Programa daha �nce girilen matris ile d��ar�dan kullan�c� taraf�ndan al�nan matrisi belirli bir kurala g�re �arpar.

const int SATIR = 5, SUTUN = 5;

struct Islem
{
	int giris[SATIR][SUTUN] = { {3,2,5,1,4}, {6,2,1,0,7}, {3,0,0,2,0}, {1,1,3,2,2}, {0,3,1,0,0} };
	int kaymaMiktari;
	int cekirdekBoyutu;
};

int sonuc_dizisi_boyut_bulucu(int giris, int cekirdek, int kayma);
bool islem_uygun_mu(int cekirdek, int kayma, int sonuc, int satir);

int main() {
	Islem islem;
	
	cout << "Cekirdek boyutunu giriniz: "; cin >> islem.cekirdekBoyutu;
	cout << endl;
	cout << "Kayma miktarini giriniz: "; cin >> islem.kaymaMiktari;
	cout << endl;
	
	int boyut = sonuc_dizisi_boyut_bulucu(SATIR, islem.cekirdekBoyutu, islem.kaymaMiktari);	//	Sonu� matrisinin boyutu; integer de�er d�nd�ren bu fonksiyon yard�m�yla bulunur.

	if (!islem_uygun_mu(islem.cekirdekBoyutu,islem.kaymaMiktari,boyut,SATIR))	//
	{																			//	E�er bool d�nd�ren islem_uygun_mu fonksiyonu false olursa bu i�lem uygun de�il demektir. 
		cout << "Bu islem yapilamaz..." << endl << endl;						//	Program sonland�r�l�r.
		system("pause");														//
		return 0;																//
	}

	int **cekirdekMatris = new int*[islem.cekirdekBoyutu];	//
	for (int i = 0; i < islem.cekirdekBoyutu; i++)			//
	{														//	�ekirdek matrisin boyutu d��ar�dan bir de�er ile girildi�i i�in pointer yard�m�yla tan�mlan�r.
		cekirdekMatris[i] = new int[islem.cekirdekBoyutu];	//
	}														//

	for (int i = 0; i < islem.cekirdekBoyutu; i++)											//
	{																						//
		for (int j = 0; j < islem.cekirdekBoyutu; j++)										//
		{																					//	 D��ar�dan �ekirdek matrisin elemanlar� girilir.
			cout << "Matris[" << i << "][" << j << "] = "; cin >> cekirdekMatris[i][j];		//
		}																					//
	}																						//

	int **sonucMatrisi = new int*[boyut];	//
	for (int i = 0; i < boyut; i++)			//
	{										//	Sonu� matrisinin boyutu da kesin olmayan bir de�er ile tan�mlanaca��ndan dolay�, bu matris pointer yard�m�yla tan�mlan�r.
		sonucMatrisi[i] = new int[boyut];	//
	}										//
	
	for (int i = 0; i < boyut; i++)		//
	{									//
		for (int j = 0; j < boyut; j++)	//
		{								//	Sonu� matrisinin i�i 0 ile doldurulur.
			sonucMatrisi[i][j] = 0;		//
		}								//
	}									//

	int a = -1, b = -1;
	for (int i = 0; i + (islem.cekirdekBoyutu - islem.kaymaMiktari) < SATIR; i += islem.kaymaMiktari)	//
	{																									//	�ekirdek ile giri� matrisi bu d�ng�de �arp�l�r. 
		a++;																							//
		b = -1;																							//		��i 0 ile doldurulan sonu� matrisi burada cekirdek matrisinin
		for (int j = 0; j + (islem.cekirdekBoyutu-islem.kaymaMiktari) < SATIR; j += islem.kaymaMiktari)	//	boyuna g�re �arp�larak toplan�r ve ortaya sonu� matrisi ��kar.
		{																								//
			b++;																						//
			for (int k = 0; k < islem.cekirdekBoyutu; k++)												//
			{																							//
				for (int l = 0; l < islem.cekirdekBoyutu; l++)											//
				{																						//
					sonucMatrisi[a][b] += cekirdekMatris[k][l] * islem.giris[k + i][l + j];				//
				}																						//
			}																							//
		}																								//
	}																									//
	
	cout << endl;
	for (int i = 0; i < boyut; i++)									//
	{																//
		for (int j = 0; j < boyut; j++)								//
		{															//
			cout << setw(5) << sonucMatrisi[i][j] << setw(5) ;		//	Sonu� matrisi ekrana bast�r�l�r.
		}															//
		cout << endl;												//
	}																//
	cout << endl;													//

	system("pause");
	
}

int sonuc_dizisi_boyut_bulucu(int giris, int cekirdek, int kayma) {
	return (giris - cekirdek) / kayma + 1;								// Sonu� dizisinin boyutu bu ba��nt� ile bulunur.
}

bool islem_uygun_mu(int cekirdek, int kayma, int sonuc, int satir) {
	return cekirdek + kayma * (sonuc - 1) == satir;						// Bu ba��nt� e�er true d�nerse i�lem yap�lmaya uygundur, �ekirdek matrisi �er�eve d���na ta�maz.
}




