#include <iostream>

using namespace std;

/****************************************************************************
**							SAKARYA �N�VERS�TES�
**			         B�LG�SAYAR VE B�L���M B�L�MLER� FAK�LTES�
**						B�LG�SAYAR M�HEND�SL��� B�L�M�
**				          PROGRAMLAMAYA G�R��� DERS�
**
**				�DEV NUMARASI�...:	4
**				��RENC� ADI......:	Evren VURAL
**				��RENC� NUMARASI.:	G181210373
**				DERS GRUBU.......:	2. ��retim A Grubu
****************************************************************************/

// D��ar�dan girilen metini Vigenere algoritmas�na g�re �ifreler ve de�ifre eder.

int sifreBoyut, alfabeBoyut, metinBoyut;

struct Harf {
	char harf;
	int sayi;
};

int harfeKarsilikGelenSayiyiBul(char charHarf, Harf *_harf) {
	for (int i = 0; i < alfabeBoyut; i++)	// Alfabedeki b�t�n harfleri taramak i�in 
	{
		if (_harf[i].harf == charHarf)	//	Parametre olarak al�nan harfin alfabede ka��nc� harfe denk geldi�ini bulur ve o say� d�nd�r�l�r.
		{
			return _harf[i].sayi;
		}
		
	}
}

char sayiyaKarsilikGelenHarfiBul(int sayi, Harf *_harf) {
	for (int i = 0; i < alfabeBoyut; i++)	//	Alfabedeki b�t�n harfleri taramak i�in
	{
		if (_harf[i].sayi == sayi)	//	Parametre olarak al�nan say�, alfabedeki hangi harfe kar��l�k geldi�ini bulur ve o harfi d�nd�r�r. 
		{
			return _harf[i].harf;
		}
		if (sayi > _harf[i].sayi)	// E�er say� alfabedeki say�lardan b�y�k ise alfabe boyutuna g�re modu al�n�r.
		{
			int temp = sayi % alfabeBoyut;
			if (_harf[i].sayi == temp)	// Modu al�nan say�, alfabede hangi harfe kar��l�k geliyorsa o harf d�nd�r�l�r.
			{
				return _harf[i].harf;
			}
		
		}
	
		if (sayi < _harf[i].sayi){ // E�er say� alfabedeki say�lardan k���k ise alfabe boyutu �zerine eklenir.
			int temp = sayi + alfabeBoyut;
			if (_harf[i].sayi == temp)	// Eklenen say�, alfabede hangi harfe kar��l�k geliyorsa o harf d�nd�r�l�r.
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
	
	if (kontrol == 'E' || kontrol == 'e')	// Girilen harf E ya da e ise bu kod blo�una girilir.
	{
		cout << "ALFABEYI CAPS LOCK ACIK GIRERSENIZ SIFRE VE METINI DE CAPS LOCK ACIK, \nKAPALI GIRERSENIZ SIFRE VE METINI DE CAPS LOCK KAPALI GIRINIZ" << endl<<endl;
		cout << "ALFABE			: ";
		cin >> alfabe;
		alfabeBoyut = strlen(alfabe);

		Harf *harf = new Harf[alfabeBoyut];

		for (int i = 0; i < alfabeBoyut; i++) // D��ar�dan girilen alfabenin boyutu kadar sayar.
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
	else // Girilen harf E ya da e de�ilse bu kod blo�una girilir.
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
