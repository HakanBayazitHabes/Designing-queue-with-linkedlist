#include <iostream>

#ifndef KUYRUK_H
#define KUYRUK_H

typedef int KuyrukVeriTipi;

struct Dugum
{
	KuyrukVeriTipi veri;
	Dugum* sonraki;
};

struct Kuyruk
{
	Dugum* bas;
	Dugum* son;
	void olustur();
	void kapat();
	void ekle(int);
	int cikar();
	bool bosMu();
	int size();
};

struct Yigin {
	Kuyruk k1, k2; //yığın için kullanılacak kuyruk değişkenleri
	Dugum* bas;
	void olustur(); //başlangıç için gereken tanımları içerir
	void kapat(); //program bitiminde bellek iadesi yapar
	void ekle(int); //kuyruğa yeni veri ekler
	int cikar(); //kuyruktan sıradaki elemanı çıkarır
	bool bosMu(); //kuyruk boş mu kontrol eder
	int tepe(); //yığının tepesindeki elemanı okur
	void yazdir(); //yığın elemanlarını sırayla ekrana yazar
};


int curr_size = 0;


#endif // !1

void yiginCikar(Yigin* s);
void siraliEkle(Yigin* s, int x);
int main()
{
	Yigin* y = new Yigin();
	y->ekle(3);
	y->ekle(1);
	y->ekle(7);
	y->ekle(4);
	y->ekle(8);

	std::cout << "Orijinal Yigin: " << std::endl;
	y->yazdir();

	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << "---yiginCikar fonksiyonu cagrisi--- " << std::endl;
	yiginCikar(y);
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << "Sirali Yigin: " << std::endl;
	y->yazdir();
	return 0;
}
void yiginCikar(Yigin* s) {
	if (!s->bosMu())
	{
		int x = s->cikar();
		yiginCikar(s);
		siraliEkle(s, x);
	}
}
void siraliEkle(Yigin* s, int x) {
	if (s->bosMu() or x > s->tepe())
	{
		s->ekle(x);
		return;
	}
	else
	{
		int temp = s->cikar();
		siraliEkle(s, x);
		s->ekle(temp);
	}

}
void Kuyruk::olustur()
{
	bas = NULL;
	son = NULL;
}
void Kuyruk::kapat()
{
	Dugum* p;
	while (bas) {
		p = bas;
		bas = bas->sonraki;
		delete p;
		curr_size = 0;
	}
}

void Kuyruk::ekle(int eklenenveri)
{
	Dugum* yenidugum = new Dugum;
	yenidugum->veri = eklenenveri;
	yenidugum->sonraki = NULL;
	if (bas == NULL)
	{
		bas = yenidugum;
		son = bas;
	}
	else {
		son->sonraki = yenidugum;
		son = yenidugum;
	}
}
int Kuyruk::cikar()
{
	Dugum* ustdugum;
	KuyrukVeriTipi gecici;
	ustdugum = bas;
	bas = bas->sonraki;
	gecici = ustdugum->veri;
	delete ustdugum;
	return gecici;
	curr_size--;
}

bool Kuyruk::bosMu()
{
	return bas == NULL;
}
int Kuyruk::size()
{
	return curr_size;
}

//---------------------------------
//Yığın

void Yigin::olustur()
{
	bas = NULL;
}
void Yigin::kapat()
{
	Dugum* p;
	while (bas)
	{
		p = bas;
		bas = bas->sonraki;
		delete p;
	}
}
void Yigin::ekle(int x)
{
	k2.ekle(x);

	while (!k1.bosMu())
	{
		k2.ekle(k1.bas->veri);
		k1.cikar();
	}
	Kuyruk q = k1;
	k1 = k2;
	k2 = q;
}

int Yigin::cikar()
{
	if (k1.bosMu())
		return 0;
	else
		k1.cikar();
}

bool Yigin::bosMu()
{
	return k1.bas == NULL;
}

int Yigin::tepe()
{
	if (k1.bosMu())
		return 0;
	return k1.bas->veri;
}

void Yigin::yazdir()
{
	Dugum* tara;
	tara = k1.bas;
	if (!tara)
	{
		std::cout << "Liste Bos!" << std::endl;
		return;
	}
	while (tara) {
		std::cout << tara->veri << " ";
		tara = tara->sonraki;
	}
	std::cout << std::endl;
}

