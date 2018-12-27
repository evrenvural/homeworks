#include <iostream>
#include <Windows.h>
#include <stdlib.h>
#include <time.h>

/****************************************************************************
**								SAKARYA ÜNÝVERSÝTESÝ
**						 BÝLGÝSAYAR VE BÝLÝÞÝM BÝLÝMLERÝ FAKÜLTESÝ
**							BÝLGÝSAYAR MÜHENDÝSLÝÐÝ BÖLÜMÜ
**								PROGRAMLAMAYA GÝRÝÞÝ DERSÝ
**
**				ÖDEV NUMARASI…...: 1. Proje - Tasarým
**				ÖÐRENCÝ ADI......: Evren VURAL
**				ÖÐRENCÝ NUMARASI.: G181210373
**				DERS GRUBU.......: 2. Öðretim - A Grubu
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
	
	while (oyun)	// Oyun deðiþkeni true olduðu sürece devam eder.
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
	for (int i = 0; i < genislik; i++)	// Tahtanýn üst ve alt sýnýrlarýný çizer.
	{
		oyunTahtasi[0][i] = 219;
		oyunTahtasi[yukseklik - 1][i] = 219;
	}
	for (int i = 0; i < yukseklik; i++)	// Tahtanýn sað ve sol sýnýrlarýný çizer.
	{
		oyunTahtasi[i][0] = 219;
		oyunTahtasi[i][genislik - 1] = 219;
	}
}

void tahtayi_temizle() {
	for (int i = 0; i < yukseklik; i++)		//
	{										//	Tahtayý, yani oyunTahtasi matrisini ' ' ile doldurur.
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
	{										//	Tahtayý çizer, yani oyunTahtasi matrisini cout ile konsol ekranýna bastýrýr.
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
	for (int i = 0; i < 256; i++)	// tuslar dizisine klavyedeki tüm tuþlarý ekler.
	{
		tuslar[i] = (char)(GetAsyncKeyState(i) >> 8);
	}
}

void kursunKoordinatAta() {
	for (int i = 0; i < 50; i++)	// Baþlangýçta tüm mermileri oyun tahtasýnýn sol üst köþesine koyar.
	{
		kursun[i].x = 0;
		kursun[i].y = 0;
		
	}
}

void kursunCiz() {
	for (int i = 0; i < 50; i++)	// Tüm mermileri kursun objesinin koordinatlarýna göre çizer.
	{
		int x = kursun[i].x;
		int y = kursun[i].y;
		oyunTahtasi[y][x] = 219;
	}
}

void kursunOlustur() {
	if (kursununSayaci <= 0 || kursununSayaci >= 50)	// kursununSayaci'nda baþlangýçta 0 deðeri atadýðým halde bazen -601531 gibi bir sayý döndürüyodu.
		{												// O hatayý engellemek için eðer 0'ýn altýnda bir deðer atanýrsa bu fonksiyonun içinde tekrar 0 deðeri atanýr.	
			kursununSayaci = 0;							// Ayrýca kursununSayaci dizisinin boyutu olan 50'yi aþmasýn diye 50 ve 50'den yüksek olan deðerlerde tekrar 0 deðeri atanýr.
		}

		kursun[kursununSayaci].x = 4;
		kursun[kursununSayaci].y = ucak.y + 2;
		kursun[kursununSayaci].can = true;
		kursununSayaci++;
	
}

void kursunHareketEttir() {
	for (int i = 0; i < 50; i++)	// Aþaðýda yapýlan iþlemleri tüm kurþunlarda yapýlmasý için 50'ye kadar tüm kurþunlar taranýr.
	{
		if (kursun[i].can)	// Eðer kurþunun can deðeri true ise yani oyun tahtasýnda çiziliyor ise x koordinatý +2 arttýrýlýr.
		{
			kursun[i].x += 2;
		}

		if (kursun[i].x >=genislik)	// Eðer oyun tahtasýnýn boyutunu aþarsa kurþun ilk koordinatýna yani sol üst köþeye atanýr ve can deðeri false olur, kurþun öldürülür.
		{
			kursun[i].x = 0;
			kursun[i].can = false;
		}
	
	}
}

void ucak_kontrol() {
	klavyeOku(tuslar);

	if (tuslar['S'] != 0)	// S tuþuna basýldýðýnda uçak aþaðý gider.
	{
		ucak.y++;
	}
	else if (tuslar['W'] != 0)	//	W tuþuna basýldýðýnda uçak yukarý gider.
	{
		ucak.y--;
	}
	if (tuslar[32])	// Space'e basýldýðýnda kurþun oluþturulur.
	{
		kursunOlustur();
	}

	if (ucak.y > yukseklik-6)	// Uçak eðer oyun tahtasýnýn en altýna inerse daha fazla aþaðý inemez. Böylece dizi boyutu aþýlmaz.
	{
		ucak.y = yukseklik -6;
	}
	if (ucak.y < 1)	// Uçak eðer oyun tahtasýnýn en üstüne çýkarsa daha fazla yukarý çýkamaz. Böylece dizi boyutu aþýlmaz.	
	{
		ucak.y = 1;
	}
}

void tumDusmanlariOldur(){
	for (int i = 0; i < 8; i++)	// Tüm düþmanlar oyun baþlamadan önce öldürülür ki daha sonra tek tek süreye göre çizilebilsin.
	{
		dusman[i].can = false;
	}
}

void dusmaniOlustur() {
	int zaman = time(&timer);
	if (zaman % 2 == 0)	// zaman deðiþkeninin son iki rakamý saniyeyi veriyor. zaman her çift sayý olduðunda saniyeGectiMi deðiþkeni true olur.
	{
		saniyeGectiMi = true;
	}
	if (zaman % 2 == 1 && saniyeGectiMi)	// zaman deðiþkeni her tek sayý olduðunda ve saniyeGectiMi deðiþkeni true olduðunda bu koþulun içine girilir. Bunu bu þekilde yapmamýn sebebi 
	{										// while döngüsü çok hýzlý dönüyor ancak ben bu koþulun saniyede bir kere saðlanmasýný istiyorum.
		
		if (dusmaninSayaci <= 0 || dusmaninSayaci >= 8)	// dusmaninSayaci'nda baþlangýçta 0 deðeri atadýðým halde bazen -601531 gibi bir sayý döndürüyodu.
		{												// O hatayý engellemek için eðer 0'ýn altýnda bir deðer atanýrsa bu fonksiyonun içinde tekrar 0 deðeri atanýr.
			dusmaninSayaci = 0;							// Ayrýca dusmaninSayaci dizisinin boyutu olan 8'i aþmasýn diye 8 ve 8'den yüksek olan deðerlerde tekrar 0 deðeri atanýr.
		}

		dusman[dusmaninSayaci].x = genislik - 4;
		dusman[dusmaninSayaci].y = 1 + (rand() % (yukseklik - 4 ));
		dusman[dusmaninSayaci].can = true;
		dusmaninSayaci++;
		saniyeGectiMi = false;
	}
	
}

void dusmaniCiz() {
	for (int i = 0; i < 8; i++)	// dusman dizisinin tüm elemanlarý taranýr.
	{
		if (dusman[i].can)	// Canlý olanlar çizilir.
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
		else // Canlý olmayanlar çizilmez.
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
	for (int i = 0; i < 8; i++)	// dusman dizisinin tüm elemanlarý taranýr.
	{
		if (dusman[i].can)	// Canlý olanlar hareket edebilir.
		{
			dusman[i].x -= 1;
		}

		if (dusman[i].x < 0)	// Oyun tahtasýnýn sýnýrýný aþanlar öldürülür ve oyun tahtasýnýn sað alt köþeye gönderilir(Sað alt köþede çizilmezler).
		{
			dusman[i].x = genislik-3;
			dusman[i].y = yukseklik - 3;
			dusman[i].can = false;
		}

	}
}

bool dusmanKursunCarpismaVarMi(int i, int j) {	// Düþman ile mermi arasýnda bir çarpýþma olup olmadýðýný kontrol eder.
	return dusman[i].x - 1 <= kursun[j].x && dusman[i].y == kursun[j].y ||
		dusman[i].x - 1 <= kursun[j].x && dusman[i].y + 1 == kursun[j].y ||
		dusman[i].x - 1 <= kursun[j].x && dusman[i].y + 2 == kursun[j].y;
}

bool ucakDusmanCarpismaVarMi(int i) {	// Uçak ile düþman arasýnda bir çarpýþma olup olmadýðýný kontrol eder.
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
	for (int i = 0; i < 8; i++)	// Tüm düþmanlar taranýr.
	{
		for (int j = 0; j < 50; j++)	// Tüm mermiler taranýr.
		{
			if (dusmanKursunCarpismaVarMi(i,j))//Düþman ile kurþun arasýnda çarpýþma olup olmadýðý kontrol edilir. Eðer çarpýþma varsa düþman öldürülür sað alt köþeye gönderilir. Çizilmez.
			{
				
				dusman[i].can = false;
				dusman[i].x = genislik - 3;
				dusman[i].y = yukseklik - 3;
			}
		}
		
	}
	
	for (int i = 0; i < 8; i++)	// Tüm düþmanlar taranýr.
	{
		if (ucakDusmanCarpismaVarMi(i))	// Uçak ile düþman arasýnda çarpýþma olup olmadýðý kontrol edilir. Eðer çarpýþma varsa oyun sonlandýrýlýr.
		{
			oyun = false;
		}
	}

	
	
}

void skorHesapla() {
	int zaman = time(&timer);
	if (skorr <= 0)	//Skor deðiþkenine 0 deðeri atanýr.
	{
		skorr = 0;
	}
	
	
	if (zaman % 2 == 0)	// zaman deðiþkeni çift sayý ise koþul saðlanýr.
	{
		saniyeGectiMi2 = true;
	}

	if (zaman % 2 == 1 && saniyeGectiMi2)	// zaman deðiþkeni tek sayý ise ve saniyeGectiMi deðiþkeni true dönerse skor deðiþkeni 1 arttýrýlýr. saniyeGectiMi false döner.
	{										// Bu sayede her saniye geçtiðinde kullanýcý bir puan kazanmýþ olur. Hayatta kaldýðý sürece kullanýcý ödüllendirilir.
		skorr++;
		saniyeGectiMi2 = false;
	}
}








