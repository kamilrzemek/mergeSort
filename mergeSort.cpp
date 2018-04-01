/*

	autor Kamil Rzemek

*/

#include <iostream>
#include <time.h>
#include <stdlib.h>
#define N 100000
using namespace std;

void wypisz(int * tabScalana, int n) {
	for (int i = 0; i < n; i++) {
		cout << tabScalana[i] << " ";
	}
	cout << endl;
}

void scal(int * tablicaZrodlowa, int pierwszyLewa, int ostatniLewa, int pierwszyPrawa, int ostatniPrawa) {
	//Zmienne do zapamietania indeksow tablicy zrodlowej
	int pierwszyLewaTemp = pierwszyLewa;
	int ostatniPrawaTemp = ostatniPrawa;
	//Informacja do tego, ile razy petla ma iterowac
	int iloscElementow = ostatniPrawa - pierwszyLewa + 1;
	//Pomocnicza tablica, zapisywane beda juz posortowane liczby
	int * tempTablica = new int[iloscElementow];
	for (int i = 0; i < iloscElementow; i++) {
		//Jesli skonczyly sie elementy lewej tablicy, przepisujemy elementy tablicy prawej
		if (pierwszyLewa > ostatniLewa) tempTablica[i] = tablicaZrodlowa[pierwszyPrawa++];
		//Jesli skonczyly sie elementy prawej tablicy, przepisujemy elementy tablicy lewej
		else if (pierwszyPrawa > ostatniPrawa) tempTablica[i] = tablicaZrodlowa[pierwszyLewa++];
		//Jesli pierwszy w kolejnosci element tablicy lewej jest <= pierwszemu elementowi tablicy prawej, trafia on do pomocniczej tablicy jako posortowany
		else if (tablicaZrodlowa[pierwszyLewa] <= tablicaZrodlowa[pierwszyPrawa]) tempTablica[i] = tablicaZrodlowa[pierwszyLewa++];
		//Jesli pierwszy w kolejnosci element tablicy prawej jest <= pierwszemu elementowi tablicy lewej, trafia on do pomoczniej tablicy jako posortowany
		else if (tablicaZrodlowa[pierwszyPrawa] <= tablicaZrodlowa[pierwszyLewa]) tempTablica[i] = tablicaZrodlowa[pierwszyPrawa++];
	}
	int index = 0;
	//Przepisuje scalone tablice do tablicy zrodlowej
	for (int i = pierwszyLewaTemp; i <= ostatniPrawaTemp; i++) {
		tablicaZrodlowa[i] = tempTablica[index++];
	}
}

void wylosuj(int * tabScalana, int n) {
	for (int i = 0; i < n; i++) tabScalana[i] = rand() % 200;
}

void mergeSort(int *tabZrodlowa, int pierwszy, int ostatni) {
	//Jesli tablica ma 2 lub mniej elementow, to od razu ja scalamy jako dwie jednoelementowe tablice
	if ((ostatni - pierwszy + 1) <= 2) scal(tabZrodlowa, pierwszy, pierwszy, ostatni, ostatni);
	else {
		//Jesli tablica ma wiecej niz 2 elementy, to wyznaczamy srodek
		int srodek = (pierwszy + ostatni) / 2;
		//Sortujemy rekurencyjnie lewa strone glownej tablicy
		mergeSort(tabZrodlowa, pierwszy, srodek);
		//Sortujemy rekurencyjnie prawa strone glownej tablicy
		mergeSort(tabZrodlowa, srodek + 1, ostatni);
		//Scalamy lewa i prawa strone tablicy
		scal(tabZrodlowa, pierwszy, srodek, srodek + 1, ostatni);
	}
	/*
		Argumenty funkcji int pierwszy i int ostatni to indexy tablicy np. 0,9 (10 elementowa tablica)
		Wyznaczajac srodek, index srodkowy nalezy do lewej tablicy
		Dlatego dla sortowania prawej tablicy wywolujemy (srodek+1, ostatni)
	*/
}

int main() {
	clock_t start, stop;
	srand(time(NULL));
	int *tab = new int[N];
	wylosuj(tab, N);
	start = clock();
	mergeSort(tab, 0, N-1);
	stop = clock();
	cout << "Sortowanie " << N <<" liczb merge sortem trwalo: " << (double)(stop - start) / CLOCKS_PER_SEC << " sekund(y)." << endl;
	return 0;

}
