#include <iostream>
#include <iomanip>

using namespace std;

/****************************************************************************
**							SAKARYA ÜNÝVERSÝTESÝ
**			         BÝLGÝSAYAR VE BÝLÝÞÝM BÝLÝMLERÝ FAKÜLTESÝ
**						BÝLGÝSAYAR MÜHENDÝSLÝÐÝ BÖLÜMÜ
**				          PROGRAMLAMAYA GÝRÝÞÝ DERSÝ
**
**				ÖDEV NUMARASI…...:	3
**				ÖÐRENCÝ ADI......:	Evren VURAL	
**				ÖÐRENCÝ NUMARASI.:	G181210373
**				DERS GRUBU.......:	2. Öðretim A Grubu
****************************************************************************/

// Programa daha önce girilen matris ile dýþarýdan kullanýcý tarafýndan alýnan matrisi belirli bir kurala göre çarpar.

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
	
	int boyut = sonuc_dizisi_boyut_bulucu(SATIR, islem.cekirdekBoyutu, islem.kaymaMiktari);	//	Sonuç matrisinin boyutu; integer deðer döndüren bu fonksiyon yardýmýyla bulunur.

	if (!islem_uygun_mu(islem.cekirdekBoyutu,islem.kaymaMiktari,boyut,SATIR))	//
	{																			//	Eðer bool döndüren islem_uygun_mu fonksiyonu false olursa bu iþlem uygun deðil demektir. 
		cout << "Bu islem yapilamaz..." << endl << endl;						//	Program sonlandýrýlýr.
		system("pause");														//
		return 0;																//
	}

	int **cekirdekMatris = new int*[islem.cekirdekBoyutu];	//
	for (int i = 0; i < islem.cekirdekBoyutu; i++)			//
	{														//	Çekirdek matrisin boyutu dýþarýdan bir deðer ile girildiði için pointer yardýmýyla tanýmlanýr.
		cekirdekMatris[i] = new int[islem.cekirdekBoyutu];	//
	}														//

	for (int i = 0; i < islem.cekirdekBoyutu; i++)											//
	{																						//
		for (int j = 0; j < islem.cekirdekBoyutu; j++)										//
		{																					//	 Dýþarýdan çekirdek matrisin elemanlarý girilir.
			cout << "Matris[" << i << "][" << j << "] = "; cin >> cekirdekMatris[i][j];		//
		}																					//
	}																						//

	int **sonucMatrisi = new int*[boyut];	//
	for (int i = 0; i < boyut; i++)			//
	{										//	Sonuç matrisinin boyutu da kesin olmayan bir deðer ile tanýmlanacaðýndan dolayý, bu matris pointer yardýmýyla tanýmlanýr.
		sonucMatrisi[i] = new int[boyut];	//
	}										//
	
	for (int i = 0; i < boyut; i++)		//
	{									//
		for (int j = 0; j < boyut; j++)	//
		{								//	Sonuç matrisinin içi 0 ile doldurulur.
			sonucMatrisi[i][j] = 0;		//
		}								//
	}									//

	int a = -1, b = -1;
	for (int i = 0; i + (islem.cekirdekBoyutu - islem.kaymaMiktari) < SATIR; i += islem.kaymaMiktari)	//
	{																									//	Çekirdek ile giriþ matrisi bu döngüde çarpýlýr. 
		a++;																							//
		b = -1;																							//		Ýçi 0 ile doldurulan sonuç matrisi burada cekirdek matrisinin
		for (int j = 0; j + (islem.cekirdekBoyutu-islem.kaymaMiktari) < SATIR; j += islem.kaymaMiktari)	//	boyuna göre çarpýlarak toplanýr ve ortaya sonuç matrisi çýkar.
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
			cout << setw(5) << sonucMatrisi[i][j] << setw(5) ;		//	Sonuç matrisi ekrana bastýrýlýr.
		}															//
		cout << endl;												//
	}																//
	cout << endl;													//

	system("pause");
	
}

int sonuc_dizisi_boyut_bulucu(int giris, int cekirdek, int kayma) {
	return (giris - cekirdek) / kayma + 1;								// Sonuç dizisinin boyutu bu baðýntý ile bulunur.
}

bool islem_uygun_mu(int cekirdek, int kayma, int sonuc, int satir) {
	return cekirdek + kayma * (sonuc - 1) == satir;						// Bu baðýntý eðer true dönerse iþlem yapýlmaya uygundur, çekirdek matrisi çerçeve dýþýna taþmaz.
}




