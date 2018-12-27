#include <iostream>

using namespace std;

/****************************************************************************
**							SAKARYA ÜNÝVERSÝTESÝ
**			         BÝLGÝSAYAR VE BÝLÝÞÝM BÝLÝMLERÝ FAKÜLTESÝ
**						BÝLGÝSAYAR MÜHENDÝSLÝÐÝ BÖLÜMÜ
**				          PROGRAMLAMAYA GÝRÝÞÝ DERSÝ
**
**				ÖDEV NUMARASI…...:	4
**				ÖÐRENCÝ ADI......:	Evren VURAL
**				ÖÐRENCÝ NUMARASI.:	G181210373
**				DERS GRUBU.......:	2. Öðretim A Grubu
****************************************************************************/

// Dýþarýdan girilen metini Vigenere algoritmasýna göre þifreler ve deþifre eder.

int sifreBoyut, alfabeBoyut, metinBoyut;

struct Harf {
	char harf;
	int sayi;
};

int harfeKarsilikGelenSayiyiBul(char charHarf, Harf *_harf) {
	for (int i = 0; i < alfabeBoyut; i++)	// Alfabedeki bütün harfleri taramak için 
	{
		if (_harf[i].harf == charHarf)	//	Parametre olarak alýnan harfin alfabede kaçýncý harfe denk geldiðini bulur ve o sayý döndürülür.
		{
			return _harf[i].sayi;
		}
		
	}
}

char sayiyaKarsilikGelenHarfiBul(int sayi, Harf *_harf) {
	for (int i = 0; i < alfabeBoyut; i++)	//	Alfabedeki bütün harfleri taramak için
	{
		if (_harf[i].sayi == sayi)	//	Parametre olarak alýnan sayý, alfabedeki hangi harfe karþýlýk geldiðini bulur ve o harfi döndürür. 
		{
			return _harf[i].harf;
		}
		if (sayi > _harf[i].sayi)	// Eðer sayý alfabedeki sayýlardan büyük ise alfabe boyutuna göre modu alýnýr.
		{
			int temp = sayi % alfabeBoyut;
			if (_harf[i].sayi == temp)	// Modu alýnan sayý, alfabede hangi harfe karþýlýk geliyorsa o harf döndürülür.
			{
				return _harf[i].harf;
			}
		
		}
	
		if (sayi < _harf[i].sayi){ // Eðer sayý alfabedeki sayýlardan küçük ise alfabe boyutu üzerine eklenir.
			int temp = sayi + alfabeBoyut;
			if (_harf[i].sayi == temp)	// Eklenen sayý, alfabede hangi harfe karþýlýk geliyorsa o harf döndürülür.
			{
				return _harf[i].harf;
			}
		}
	}
}


class Sifre {
public:
	Sifre(char *_sifre, Harf *_harf) {
		
		harf = _harf;
		sifreKelimesi = _sifre;
	}
	Sifre() {
		alfabeBoyut = 26;
		char alfabe[100] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
		Harf *hAlfabe = new Harf[alfabeBoyut];

		for (int i = 0; i < alfabeBoyut; i++) // Alfabe boyutu kadar sayar.
		{
			hAlfabe[i].harf = alfabe[i];
			hAlfabe[i].sayi = i + 1;
		}
		harf = hAlfabe;
		
	}

	char *sifrele(char *metin) {

		int metinSayi[100];

		for (int i = 0; i < 100; i++)	// metinSayi dizisinin boyutu kadar sayar.
		{
			metinSayi[i] = harfeKarsilikGelenSayiyiBul(metin[i], harf);
		}
		
		for (int i = 0; i < metinBoyut; i++)	//Girilen metinin boyutu kadar sayar.
		{
			metinSayi[i] += harfeKarsilikGelenSayiyiBul(sifreKelimesi[i % sifreBoyut], harf);
		}
		
		for (int i = 0; i < metinBoyut; i++)	//Girilen metinin boyutu kadar sayar.
		{
			metin[i] = sayiyaKarsilikGelenHarfiBul(metinSayi[i], harf);
		}
		return metin;
	}
	char *sifreCoz(char *metin) {
		int metinSayi[100];

		for (int i = 0; i < 100; i++)	// metinSayi dizisinin boyutu kadar sayar.
		{
			metinSayi[i] = harfeKarsilikGelenSayiyiBul(metin[i], harf);
		}

		for (int i = 0; i < metinBoyut; i++)	//Girilen metinin boyutu kadar sayar.
		{
			metinSayi[i] -= harfeKarsilikGelenSayiyiBul(sifreKelimesi[i % sifreBoyut], harf);
		}

		for (int i = 0; i < metinBoyut; i++)	//Girilen metinin boyutu kadar sayar.
		{
			metin[i] = sayiyaKarsilikGelenHarfiBul(metinSayi[i], harf);
		}
		return metin;
	}
	void sifreKelimesiAta(char *_sifre) {
		sifreKelimesi = _sifre;
	}
	
private:
	char *sifreKelimesi;
	Harf *harf;
};

char alfabe[26];
char sifre[100];
char metin[100];

char kontrol;

int main() {
	cout << "KENDI ALFABENIZI GIRMEK ICIN E'YE, INGILIZ ALFABESINI KULLANMAK ICIN HERHANGI BIR TUSA BASINIZ \n\nSECIMINIZ: " ;  cin >> kontrol;
	cout << endl;
	
	if (kontrol == 'E' || kontrol == 'e')	// Girilen harf E ya da e ise bu kod bloðuna girilir.
	{
		cout << "ALFABEYI CAPS LOCK ACIK GIRERSENIZ SIFRE VE METINI DE CAPS LOCK ACIK, \nKAPALI GIRERSENIZ SIFRE VE METINI DE CAPS LOCK KAPALI GIRINIZ" << endl<<endl;
		cout << "ALFABE			: ";
		cin >> alfabe;
		alfabeBoyut = strlen(alfabe);

		Harf *harf = new Harf[alfabeBoyut];

		for (int i = 0; i < alfabeBoyut; i++) // Dýþarýdan girilen alfabenin boyutu kadar sayar.
		{
			harf[i].harf = alfabe[i];
			harf[i].sayi = i + 1;
		}
		cout << "SIFRE			: ";
		cin >> sifre;
		sifreBoyut = strlen(sifre);

		Sifre cSifre(sifre, harf);

		cout << "METIN			: ";
		cin >> metin;
		metinBoyut = strlen(metin);

		cout << "SIFRELENMIS METIN	: " << cSifre.sifrele(metin) << endl;

		cout << "DESIFRE METIN		: " << cSifre.sifreCoz(metin) << endl;

		cout << endl;
	}
	else // Girilen harf E ya da e deðilse bu kod bloðuna girilir.
	{
		
		Sifre cSifre;
		
		cout << "SIFRE			: ";
		cin >> sifre;
		sifreBoyut = strlen(sifre);

		
		cSifre.sifreKelimesiAta(sifre);

		cout << "METIN			: ";
		cin >> metin;
		metinBoyut = strlen(metin);

		cout << "SIFRELENMIS METIN	: " << cSifre.sifrele(metin) << endl;

		cout << "DESIFRE METIN		: " << cSifre.sifreCoz(metin) << endl;

		cout << endl;
	}


	
	
	
	system("pause");
}
