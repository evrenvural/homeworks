#include <iostream>
#include <Windows.h>
#include <stdlib.h>
#include <time.h>

/****************************************************************************
**								SAKARYA �N�VERS�TES�
**						 B�LG�SAYAR VE B�L���M B�L�MLER� FAK�LTES�
**							B�LG�SAYAR M�HEND�SL��� B�L�M�
**								PROGRAMLAMAYA G�R��� DERS�
**
**				�DEV NUMARASI�...: 1. Proje - Tasar�m
**				��RENC� ADI......: Evren VURAL
**				��RENC� NUMARASI.: G181210373
**				DERS GRUBU.......: 2. ��retim - A Grubu
****************************************************************************/

// Eski model nokia telefonlarda bulunan Space oyununun benzeri.

using namespace std;

struct Karakter {
	int x;
	int y;
	bool can = true;
};

time_t timer;
Karakter ucak;
Karakter kursun[50];
Karakter dusman[8];

int kursununSayaci, dusmaninSayaci;
int skorr = 0;
bool saniyeGectiMi, saniyeGectiMi2;
bool oyun = true;

const int genislik = 80, yukseklik = 20;
char oyunTahtasi[yukseklik][genislik];
char tuslar[256];


void tahta_ciz();
void ucakCiz();
void tahtayi_temizle(); 
void ucak_kontrol();
void kursunHareketEttir();
void kursunCiz();
void tumDusmanlariOldur();
void dusmaniOlustur();
void dusmaniCiz();
void dusmanHareketEttir();
void carpisma();
void skorHesapla();


int main() {
	srand(time(NULL));

	kursununSayaci = 0;
	dusmaninSayaci = 0;

	ucak.y = 5;
	
	tumDusmanlariOldur();

	cout << "********* Welcome to The Space Game *********" << endl << endl << "1) Press W to move up the space ship," << endl << "2) Press S to move down the space ship," << endl << "3) Press Space to fire." << endl << endl;
	cout << "The purpose of the game is to survive. Keep alive and earn scores..." << endl << endl;
	system("Pause");
	
	while (oyun)	// Oyun de�i�keni true oldu�u s�rece devam eder.
	{
		
		tahtayi_temizle();
		ucakCiz();
		kursunCiz();
		kursunHareketEttir();
		dusmaniOlustur();
		dusmaniCiz();
		dusmanHareketEttir();
		tahta_ciz();
		ucak_kontrol();
		carpisma();
		skorHesapla();
		Sleep(10);
		
	}
	
	cout << endl << "********* Space Game *********" << endl << endl << "Score: " << skorr << endl << endl;
	
	system("pause");
}

void tahta_sinirlari_ciz() {
	for (int i = 0; i < genislik; i++)	// Tahtan�n �st ve alt s�n�rlar�n� �izer.
	{
		oyunTahtasi[0][i] = 219;
		oyunTahtasi[yukseklik - 1][i] = 219;
	}
	for (int i = 0; i < yukseklik; i++)	// Tahtan�n sa� ve sol s�n�rlar�n� �izer.
	{
		oyunTahtasi[i][0] = 219;
		oyunTahtasi[i][genislik - 1] = 219;
	}
}

void tahtayi_temizle() {
	for (int i = 0; i < yukseklik; i++)		//
	{										//	Tahtay�, yani oyunTahtasi matrisini ' ' ile doldurur.
		for (int j = 0; j < genislik; j++)	//
		{
			oyunTahtasi[i][j] = ' ';
		}
	}
}

void kursoruGizle() {
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = false;
	SetConsoleCursorInfo(out, &cursorInfo);
}

void gotoxy(int x, int y) {
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void tahta_ciz() {
	kursoruGizle();
	tahta_sinirlari_ciz();
	gotoxy(0, 0);
	
	for (int i = 0; i < yukseklik; i++)		//
	{										//	Tahtay� �izer, yani oyunTahtasi matrisini cout ile konsol ekran�na bast�r�r.
		for (int j = 0; j < genislik; j++)	//
		{
			cout << oyunTahtasi[i][j];
		}
		cout << endl;
	}
}

void ucakCiz() {
	int y = ucak.y;
	oyunTahtasi[y][1] = 219;
	oyunTahtasi[y+1][2] = 219;
	oyunTahtasi[y+2][3] = 219;
	oyunTahtasi[y+3][2] = 219;
	oyunTahtasi[y+4][1] = 219;
}

void klavyeOku(char tuslar[]) {
	for (int i = 0; i < 256; i++)	// tuslar dizisine klavyedeki t�m tu�lar� ekler.
	{
		tuslar[i] = (char)(GetAsyncKeyState(i) >> 8);
	}
}

void kursunKoordinatAta() {
	for (int i = 0; i < 50; i++)	// Ba�lang��ta t�m mermileri oyun tahtas�n�n sol �st k��esine koyar.
	{
		kursun[i].x = 0;
		kursun[i].y = 0;
		
	}
}

void kursunCiz() {
	for (int i = 0; i < 50; i++)	// T�m mermileri kursun objesinin koordinatlar�na g�re �izer.
	{
		int x = kursun[i].x;
		int y = kursun[i].y;
		oyunTahtasi[y][x] = 219;
	}
}

void kursunOlustur() {
	if (kursununSayaci <= 0 || kursununSayaci >= 50)	// kursununSayaci'nda ba�lang��ta 0 de�eri atad���m halde bazen -601531 gibi bir say� d�nd�r�yodu.
		{												// O hatay� engellemek i�in e�er 0'�n alt�nda bir de�er atan�rsa bu fonksiyonun i�inde tekrar 0 de�eri atan�r.	
			kursununSayaci = 0;							// Ayr�ca kursununSayaci dizisinin boyutu olan 50'yi a�mas�n diye 50 ve 50'den y�ksek olan de�erlerde tekrar 0 de�eri atan�r.
		}

		kursun[kursununSayaci].x = 4;
		kursun[kursununSayaci].y = ucak.y + 2;
		kursun[kursununSayaci].can = true;
		kursununSayaci++;
	
}

void kursunHareketEttir() {
	for (int i = 0; i < 50; i++)	// A�a��da yap�lan i�lemleri t�m kur�unlarda yap�lmas� i�in 50'ye kadar t�m kur�unlar taran�r.
	{
		if (kursun[i].can)	// E�er kur�unun can de�eri true ise yani oyun tahtas�nda �iziliyor ise x koordinat� +2 artt�r�l�r.
		{
			kursun[i].x += 2;
		}

		if (kursun[i].x >=genislik)	// E�er oyun tahtas�n�n boyutunu a�arsa kur�un ilk koordinat�na yani sol �st k��eye atan�r ve can de�eri false olur, kur�un �ld�r�l�r.
		{
			kursun[i].x = 0;
			kursun[i].can = false;
		}
	
	}
}

void ucak_kontrol() {
	klavyeOku(tuslar);

	if (tuslar['S'] != 0)	// S tu�una bas�ld���nda u�ak a�a�� gider.
	{
		ucak.y++;
	}
	else if (tuslar['W'] != 0)	//	W tu�una bas�ld���nda u�ak yukar� gider.
	{
		ucak.y--;
	}
	if (tuslar[32])	// Space'e bas�ld���nda kur�un olu�turulur.
	{
		kursunOlustur();
	}

	if (ucak.y > yukseklik-6)	// U�ak e�er oyun tahtas�n�n en alt�na inerse daha fazla a�a�� inemez. B�ylece dizi boyutu a��lmaz.
	{
		ucak.y = yukseklik -6;
	}
	if (ucak.y < 1)	// U�ak e�er oyun tahtas�n�n en �st�ne ��karsa daha fazla yukar� ��kamaz. B�ylece dizi boyutu a��lmaz.	
	{
		ucak.y = 1;
	}
}

void tumDusmanlariOldur(){
	for (int i = 0; i < 8; i++)	// T�m d��manlar oyun ba�lamadan �nce �ld�r�l�r ki daha sonra tek tek s�reye g�re �izilebilsin.
	{
		dusman[i].can = false;
	}
}

void dusmaniOlustur() {
	int zaman = time(&timer);
	if (zaman % 2 == 0)	// zaman de�i�keninin son iki rakam� saniyeyi veriyor. zaman her �ift say� oldu�unda saniyeGectiMi de�i�keni true olur.
	{
		saniyeGectiMi = true;
	}
	if (zaman % 2 == 1 && saniyeGectiMi)	// zaman de�i�keni her tek say� oldu�unda ve saniyeGectiMi de�i�keni true oldu�unda bu ko�ulun i�ine girilir. Bunu bu �ekilde yapmam�n sebebi 
	{										// while d�ng�s� �ok h�zl� d�n�yor ancak ben bu ko�ulun saniyede bir kere sa�lanmas�n� istiyorum.
		
		if (dusmaninSayaci <= 0 || dusmaninSayaci >= 8)	// dusmaninSayaci'nda ba�lang��ta 0 de�eri atad���m halde bazen -601531 gibi bir say� d�nd�r�yodu.
		{												// O hatay� engellemek i�in e�er 0'�n alt�nda bir de�er atan�rsa bu fonksiyonun i�inde tekrar 0 de�eri atan�r.
			dusmaninSayaci = 0;							// Ayr�ca dusmaninSayaci dizisinin boyutu olan 8'i a�mas�n diye 8 ve 8'den y�ksek olan de�erlerde tekrar 0 de�eri atan�r.
		}

		dusman[dusmaninSayaci].x = genislik - 4;
		dusman[dusmaninSayaci].y = 1 + (rand() % (yukseklik - 4 ));
		dusman[dusmaninSayaci].can = true;
		dusmaninSayaci++;
		saniyeGectiMi = false;
	}
	
}

void dusmaniCiz() {
	for (int i = 0; i < 8; i++)	// dusman dizisinin t�m elemanlar� taran�r.
	{
		if (dusman[i].can)	// Canl� olanlar �izilir.
		{
			int x = dusman[i].x;
			int y = dusman[i].y;
			oyunTahtasi[y][x] = 178;
			oyunTahtasi[y][x + 1] = 178;
			oyunTahtasi[y][x + 2] = 178;
			oyunTahtasi[y + 1][x] = 178;
			oyunTahtasi[y + 1][x + 2] = 178;
			oyunTahtasi[y + 2][x] = 178;
			oyunTahtasi[y + 2][x + 1] = 178;
			oyunTahtasi[y + 2][x + 2] = 178;
		}
		else // Canl� olmayanlar �izilmez.
		{
			int x = dusman[i].x;
			int y = dusman[i].y;
			oyunTahtasi[y][x] = ' ';
			oyunTahtasi[y][x + 1] = ' ';
			oyunTahtasi[y][x + 2] = ' ';
			oyunTahtasi[y + 1][x] = ' ';
			oyunTahtasi[y + 1][x + 2] = ' ';
			oyunTahtasi[y + 2][x] = ' ';
			oyunTahtasi[y + 2][x + 1] = ' ';
			oyunTahtasi[y + 2][x + 2] = ' ';
		}
	}
}

void dusmanHareketEttir() {
	for (int i = 0; i < 8; i++)	// dusman dizisinin t�m elemanlar� taran�r.
	{
		if (dusman[i].can)	// Canl� olanlar hareket edebilir.
		{
			dusman[i].x -= 1;
		}

		if (dusman[i].x < 0)	// Oyun tahtas�n�n s�n�r�n� a�anlar �ld�r�l�r ve oyun tahtas�n�n sa� alt k��eye g�nderilir(Sa� alt k��ede �izilmezler).
		{
			dusman[i].x = genislik-3;
			dusman[i].y = yukseklik - 3;
			dusman[i].can = false;
		}

	}
}

bool dusmanKursunCarpismaVarMi(int i, int j) {	// D��man ile mermi aras�nda bir �arp��ma olup olmad���n� kontrol eder.
	return dusman[i].x - 1 <= kursun[j].x && dusman[i].y == kursun[j].y ||
		dusman[i].x - 1 <= kursun[j].x && dusman[i].y + 1 == kursun[j].y ||
		dusman[i].x - 1 <= kursun[j].x && dusman[i].y + 2 == kursun[j].y;
}

bool ucakDusmanCarpismaVarMi(int i) {	// U�ak ile d��man aras�nda bir �arp��ma olup olmad���n� kontrol eder.
	return dusman[i].x <= ucak.x + 1 && dusman[i].y == ucak.y ||
		dusman[i].x <= ucak.x + 2 && dusman[i].y == ucak.y + 1 ||
		dusman[i].x <= ucak.x + 3 && dusman[i].y == ucak.y + 2 ||
		dusman[i].x <= ucak.x + 2 && dusman[i].y == ucak.y + 3 ||
		dusman[i].x <= ucak.x + 1 && dusman[i].y == ucak.y + 4 ||

		dusman[i].x <= ucak.x + 1 && dusman[i].y + 1 == ucak.y ||
		dusman[i].x <= ucak.x + 2 && dusman[i].y + 1 == ucak.y + 1 ||
		dusman[i].x <= ucak.x + 3 && dusman[i].y + 1 == ucak.y + 2 ||
		dusman[i].x <= ucak.x + 2 && dusman[i].y + 1 == ucak.y + 3 ||
		dusman[i].x <= ucak.x + 1 && dusman[i].y + 1== ucak.y + 4 ||

		dusman[i].x <= ucak.x + 1 && dusman[i].y + 2 == ucak.y ||
		dusman[i].x <= ucak.x + 2 && dusman[i].y + 2 == ucak.y + 1 ||
		dusman[i].x <= ucak.x + 3 && dusman[i].y + 2 == ucak.y + 2 ||
		dusman[i].x <= ucak.x + 2 && dusman[i].y + 2 == ucak.y + 3 ||
		dusman[i].x <= ucak.x + 1 && dusman[i].y + 2 == ucak.y + 4;
}

void carpisma() {
	for (int i = 0; i < 8; i++)	// T�m d��manlar taran�r.
	{
		for (int j = 0; j < 50; j++)	// T�m mermiler taran�r.
		{
			if (dusmanKursunCarpismaVarMi(i,j))//D��man ile kur�un aras�nda �arp��ma olup olmad��� kontrol edilir. E�er �arp��ma varsa d��man �ld�r�l�r sa� alt k��eye g�nderilir. �izilmez.
			{
				
				dusman[i].can = false;
				dusman[i].x = genislik - 3;
				dusman[i].y = yukseklik - 3;
			}
		}
		
	}
	
	for (int i = 0; i < 8; i++)	// T�m d��manlar taran�r.
	{
		if (ucakDusmanCarpismaVarMi(i))	// U�ak ile d��man aras�nda �arp��ma olup olmad��� kontrol edilir. E�er �arp��ma varsa oyun sonland�r�l�r.
		{
			oyun = false;
		}
	}

	
	
}

void skorHesapla() {
	int zaman = time(&timer);
	if (skorr <= 0)	//Skor de�i�kenine 0 de�eri atan�r.
	{
		skorr = 0;
	}
	
	
	if (zaman % 2 == 0)	// zaman de�i�keni �ift say� ise ko�ul sa�lan�r.
	{
		saniyeGectiMi2 = true;
	}

	if (zaman % 2 == 1 && saniyeGectiMi2)	// zaman de�i�keni tek say� ise ve saniyeGectiMi de�i�keni true d�nerse skor de�i�keni 1 artt�r�l�r. saniyeGectiMi false d�ner.
	{										// Bu sayede her saniye ge�ti�inde kullan�c� bir puan kazanm�� olur. Hayatta kald��� s�rece kullan�c� �d�llendirilir.
		skorr++;
		saniyeGectiMi2 = false;
	}
}








