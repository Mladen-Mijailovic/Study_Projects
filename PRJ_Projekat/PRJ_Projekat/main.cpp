//Mladen Mijailovic NRT 14/22
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>

#define MAX_IGRACA 20

using namespace std;

class Igrac {
private:
	static int brojIgracaUFajlu;
	string ime;
	string prezime;
	string godiste;
	string pozicija;
	string status;

public:
	// Konstruktor
	Igrac() {}

	void unosPodataka();

	static void ispisiIgrace(const Igrac igraci[], int brojIgraca);
	static void sacuvajIgrace(const Igrac* igraci, int brojIgraca);
	static void ucitajIgrace(Igrac* igraci, int& brojIgraca);
	static void obrisiIgraca(int index);

};

class Raspored {
private:
	string naziviKlubova[18];
	char domacinGost[1]; // 'D' ili 'G'

public:
	void unosRasporeda();
	void ispisiRaspored();
};

class Trener {
private:
	string ime;
	string prezime;
	string strategija;
	string formacija;

public:
	void unosTrenera();
	void upisivanjeTrenera();
	void prikazTrenera();
};

//Funkcije
void brisanjePodatakaUFajlu(const string nazivFajla);
void greskaIzbora(int izbor);
bool prazanFile(const string& file);
bool brojString(const string& s);
bool duzinaBroja(string s);
string velikoMaloSlovo(string podatak);


//Igrac
void Igrac::unosPodataka() {
	//Unosi se ime igraca, proverava se da li je unet broj u imenu
	do {
		cout << "\nUnesite ime igraca: ";
		cin >> ime;

		if (brojString(ime)) {
			cout << "\nUneli ste broj u imenu!";
		}
		else {
			ime = velikoMaloSlovo(ime);		//Pretvara prvo slovo u veliko, a ostala slova u mala
			break;
		}

	} while (true);
	//Unosi se prezime igraca, proverava se da li je unet broj u prezimenu
	do {
		cout << "\nUnesite prezime igraca: ";
		cin >> prezime;

		if (brojString(prezime)) {
			cout << "\nUneli ste broj u prezimenu!";
		}
		else {
			prezime = velikoMaloSlovo(prezime);	//Pretvara prvo slovo u veliko, a ostala slova u mala
			break;
		}

	} while (true);

	//Godiste mora da se unese da se unese kao broj od 4 cifre
	do {
		cout << "\nUnesite godiste igraca: ";
		cin >> godiste;

		if (brojString(godiste) == false) {			//Proverava da li je string broj
			cout << "\nNiste uneli pravilno godiste! Unesite 4 cifre.";
		}
		if (duzinaBroja(godiste) == false) {		//Proverava duzinu stringa
			cout << "\nNiste uneli pravilno godiste! Unesite 4 cifre.";
		}
		if (brojString(godiste) == true && duzinaBroja(godiste) == true)
		{
			break;
		}
	} while (true);

	//Pozicija se unosi sa 3 ili 2 karaktera
	do {
		cout << "\nUnesite poziciju igraca: ";
		cin >> pozicija;
		transform(pozicija.begin(), pozicija.end(), pozicija.begin(), ::toupper);	//Pretvara sve karaktere u velika slova
		if (brojString(pozicija) == true) {			//Proverava da li je unet broj u stringu
			cout << "\nUneli ste broj!";
		}
		if (!(pozicija.length() == 3 || pozicija.length() == 2)) {		//Proverava duzinu stringa
			cout << "\nNiste pravilno uneli poziciju. (RB,CM,CAM,RWF,CF)";
		}

	} while (!(pozicija.length() == 3 || pozicija.length() == 2) || brojString(pozicija) == true);

	//Status igraca
	do {
		cout << "\nUnesite status igraca: ";
		cin >> status;

		if (brojString(status)) {		//Proverava da li se nalazi broj u stringu
			cout << "\nUneli ste broj u statusu!";
		}
		else {
			status = velikoMaloSlovo(status);		//Pretvara prvo slovo u veliko, a ostala u mala
			break;
		}

	} while (true);
}

//Funkcija za ispisivanje igraca
//Parametri:
//	igrac[]: niz igraca tipa Igrac
//	brojIgraca: broj igraca u nizu
void Igrac::ispisiIgrace(const Igrac igraci[], int brojIgraca) {
	cout << "\nSpisak igraca:" << endl;
	for (int i = 0; i < brojIgraca; ++i) {
		cout << "\nIgrac " << i + 1 << ":";
		cout << "\nIme: " << igraci[i].ime;
		cout << "\nPrezime: " << igraci[i].prezime;
		cout << "\nGodiste: " << igraci[i].godiste;
		cout << "\nPozicija: " << igraci[i].pozicija;
		cout << "\nStatus: " << igraci[i].status << "\n";
	}
}
//Funkcija za cuvajne podataka igraca
//Parametri:
//	igrac: pokazivac na niz objekata tipa Igrac
//	brojIgraca: broj igraca u objketu
void Igrac::sacuvajIgrace(const Igrac* igraci, int brojIgraca) {
	//Otvaranje txt fajla 
	ofstream fileIgraci("igraci.txt", ios::out);

	if (fileIgraci.is_open()) {
		fileIgraci << brojIgraca << endl; // Upisuje broj igraca u prvi red fajla

		for (int i = 0; i < brojIgraca; ++i) {
			// Upisuje podatke za svakog igraca
			fileIgraci << igraci[i].ime << " " << igraci[i].prezime << " " << igraci[i].godiste << " " << igraci[i].pozicija << " " << igraci[i].status << endl;
		}

		fileIgraci.close();
	}
	else {
		cout << "\nNije moguce sacuvati fajl.";
	}
}

//Funkcija za ucitavanje igraca
//Parametri:
//	igraci: pokazivac na niz objekata tipa Igrac
//	brojIgraca: referenca na broj igraca(menja se pri ucitavanju)
void Igrac::ucitajIgrace(Igrac* igraci, int& brojIgraca) {
	ifstream fileIgraci("igraci.txt", ios::in);

	if (fileIgraci.is_open()) {
		fileIgraci >> brojIgraca; // Ucitava broj igraca
		fileIgraci.ignore(); // Ignorise prelazak u novi red

		for (int i = 0; i < brojIgraca; ++i) {
			fileIgraci >> igraci[i].ime >> igraci[i].prezime >> igraci[i].godiste >> igraci[i].pozicija >> igraci[i].status;
		}
		fileIgraci.close();
	}
	else {
		cout << "\nNije moguce procitati fajl.";
	}
}

//Funkcija za brisanje igraca na osnovu njegovog indexa
//Parametri:
//	index: indeks igraca koji ce biti obrisan
void Igrac::obrisiIgraca(int index) {
	// Ucitavanje postojećih igraca iz fajla
	ifstream fileIgraci("igraci.txt");

	if (fileIgraci.is_open()) {
		int brojIgraca;
		fileIgraci >> brojIgraca;

		// Ucitavanje podataka u dinamicki niz
		Igrac* igraci = new Igrac[brojIgraca];

		//Ucitavanje podataka iz fajla
		for (int i = 0; i < brojIgraca; ++i) {
			fileIgraci >> igraci[i].ime >> igraci[i].prezime >> igraci[i].godiste >> igraci[i].pozicija >> igraci[i].status;
		}

		fileIgraci.close();

		// Provera ispravnosti indeksa
		if (index >= 0 && index - 1 < brojIgraca) {
			// Brisanje igraca iz niza
			for (int i = index - 1; i < brojIgraca; ++i) {
				igraci[i] = igraci[i];
			}

			// Azuriranje broja igraca u fajlu
			brojIgraca--;

			// Ponovno pisanje svih igraca u fajl
			ofstream fileIgraci("igraci.txt");
			if (fileIgraci.is_open()) {
				fileIgraci << brojIgraca << endl;

				for (int i = 0; i < brojIgraca; ++i) {
					fileIgraci << igraci[i].ime << " " << igraci[i].prezime << " "
						<< igraci[i].godiste << " " << igraci[i].pozicija << " "
						<< igraci[i].status << endl;
				}

				cout << "Igrac sa indeksom " << index << " uspesno obrisan." << endl;
				fileIgraci.close();
			}
			else {
				cout << "Nije moguce otvoriti fajl za pisanje." << endl;
			}
		}
		else {
			cout << "Neispravan indeks igraca!" << endl;
		}

		// Oslobadjanje memorije
		delete[] igraci;
	}
	else {
		cout << "Nije moguce otvoriti fajl za citanje." << endl;
	}
}


//Raspored
void Raspored::unosRasporeda() {
	ofstream fileRaspored("raspored.txt");
	cout << "\nZa izlaz iz unosa, upisite Stop\n";
	for (int i = 0; i < 18; ++i) {
		do {
			cout << "\nUnesite naziv protivnika za utakmicu " << i + 1 << ": ";
			cin >> naziviKlubova[i]; // Unos imena kluba
			if (brojString(naziviKlubova[i])) {
				cout << "\nUneli ste broj u nazivu!";
			}
			else {
				naziviKlubova[i] = velikoMaloSlovo(naziviKlubova[i]);
				break;
			}
		} while (true);

		if (naziviKlubova[i] == "Stop") {
			cout << "\nIzasli ste iz upisa.";
			break;
		}
		if (naziviKlubova[i] == "Slobodni") {
			domacinGost[i] = 'S';
			fileRaspored << naziviKlubova[i] << " " << domacinGost[i] << endl;
			continue;
		}

		char domacinGostChar;
		do {
			cout << "\nDa li je tim domacin ili gost? (D/G): ";
			cin >> domacinGostChar;

			if (domacinGostChar != 'D' && domacinGostChar != 'G') {
				cout << "\nNiste uneli ispravnu vrednost za domacina/gosta. Unesite D ili G.";
			}
		} while (domacinGostChar != 'D' && domacinGostChar != 'G');

		domacinGost[i] = domacinGostChar;
		fileRaspored << naziviKlubova[i] << " " << domacinGost[i] << endl;

	}
	fileRaspored.close();
}

void Raspored::ispisiRaspored() {
	ifstream fileRaspored("raspored.txt");
	cout << "\nRaspored utakmica:\n";

	for (int i = 0; i < 18; ++i) {
		fileRaspored >> naziviKlubova[i];
		fileRaspored >> domacinGost[i];

		if (naziviKlubova[i] == "")
		{
			break;
		}

		cout << "Utakmica #" << i + 1 << ": " << naziviKlubova[i] << " " << domacinGost[i] << endl;
	}
	fileRaspored.close();
}



//Trener
void Trener::unosTrenera() {
	do {
		cout << "\nUnesite ime trenra: ";
		cin >> ime;

		if (brojString(ime)) {
			cout << "\nUneli ste broj u imenu!";
		}
		else {
			ime = velikoMaloSlovo(ime);
			break;
		}

	} while (true);

	do {
		cout << "\nUnesite prezime trenera: ";
		cin >> prezime;

		if (brojString(prezime)) {
			cout << "\nUneli ste broj u prezimenu!";
		}
		else {
			prezime = velikoMaloSlovo(prezime);
			break;
		}

	} while (true);

	do {
		cout << "Unesite strategiju: ";
		cin >> strategija;

		if (brojString(strategija)) {
			cout << "\nUneli ste broj u strategiji!";
		}
		else {
			strategija = velikoMaloSlovo(strategija);
			break;
		}

	} while (true);

	cout << "Unesite formaciju: ";
	cin >> formacija;
}

void Trener::upisivanjeTrenera() {
	ofstream trenerFile("trener.txt");
	trenerFile << ime << " " << prezime << " " << strategija << " " << formacija << endl;
	trenerFile.close();
}

void Trener::prikazTrenera() {
	ifstream trenerFile("trener.txt");
	cout << "\nPodaci trenera su:\n";
	if (trenerFile.is_open()) {
		string line;
		while (getline(trenerFile, line)) {
			cout << line << " ";
		}
		cout << endl;
	}
	trenerFile.close();
}



int main() {
	Igrac* noviIgraci = new Igrac[MAX_IGRACA];
	int brojIgraca = 0;
	Igrac::ucitajIgrace(noviIgraci, brojIgraca);

	Raspored raspored;
	Trener trener;

	int izbor;
	do {
		cout << "\n1. Igraci";
		cout << "\n2. Raspored";
		cout << "\n3. Trener";
		cout << "\n0. Izlaz";
		cout << "\nIzaberite opciju: ";
		cin >> izbor;
		if (izbor == 0)
		{
			exit(0);
		}
		else {
			greskaIzbora(izbor);
		}

		switch (izbor) {
		case 1: {
			int opcijeIgraca;

			cout << "\n1. Nov igrac";
			cout << "\n2. Podaci igraca";
			cout << "\n3. Brisanje igraca";
			cout << "\n0. Nazad";
			cout << "\nIzaberite opciju: ";
			cin >> opcijeIgraca;
			if (opcijeIgraca == 0)
			{
				break;
			}
			else {
				greskaIzbora(opcijeIgraca);
			}


			switch (opcijeIgraca) {
			case 1: {
				if (brojIgraca < MAX_IGRACA) {
					noviIgraci[brojIgraca++].unosPodataka();

					Igrac::sacuvajIgrace(noviIgraci, brojIgraca);
					cout << "\nUspesno ste uneli podatke.";
				}
				else {
					cout << "\nDostignut je maksimalan broj igraca!" << endl;
				}
			}
				  break;
			case 2: {
				Igrac::ucitajIgrace(noviIgraci, brojIgraca);
				Igrac::ispisiIgrace(noviIgraci, brojIgraca);
			}
				  break;
			case 3: {
				int izborBrisanje;
				cout << "\n1. Obrisi jednog igraca";
				cout << "\n2. Obrisi sve igrace";
				cout << "\n0. Nazad";
				cout << "\nIzaberite opciju: ";
				cin >> izborBrisanje;
				if (izborBrisanje == 0)
				{
					break;
				}
				else {
					greskaIzbora(izborBrisanje);
				}

				switch (izborBrisanje)
				{
				case 1: {
					int indexBrisanje;
					int t = 0;
					do
					{
						cout << "Unesite indeks igraca za brisanje: ";
						cin >> indexBrisanje;
						if (indexBrisanje <= brojIgraca) {
							Igrac::obrisiIgraca(indexBrisanje);
							cout << "\nUspesno ste obrisali igraca sa indeksom[" << indexBrisanje << "]";
							t = 1;
						}
						else {
							cout << "\nUneli se indeks za nepostojeceg igraca.\n";
						}

					} while (t != 1);


				}
					  break;
				case 2: {
					brisanjePodatakaUFajlu("igraci.txt");
					brojIgraca = 0;
					cout << "\nUspesno ste obrisali sve igrace";
				}
					  break;
				}
			}
				  break;
			}
			break;
		}
		case 2: {
			int izborRaspored;
			string rasporedFile = "raspored.txt";
			cout << "\n1. Unesite raspored";
			cout << "\n2. Pregledajte raspored";
			cout << "\n3. Obrisite raspored";
			cout << "\n0. Nazad";
			cout << "\nIzaberite opciju: ";
			cin >> izborRaspored;
			if (izborRaspored == 0)
			{
				break;
			}
			else {
				greskaIzbora(izborRaspored);
			}

			switch (izborRaspored)
			{
			case 1: {
				raspored.unosRasporeda();
			}
				  break;
			case 2: {
				if (prazanFile(rasporedFile))
				{
					cout << "\nFajl " << rasporedFile << " je prazan.";
				}
				else {
					raspored.ispisiRaspored();
				}
				break;
			}
				  break;
			case 3: {
				brisanjePodatakaUFajlu("raspored.txt");
				cout << "\nUspesno ste obrisali podatke";
				break;
			}
			}
			break;
		}
		case 3: {
			int izborTrener;
			string trenerFile = "trener.txt";

			cout << "\n1. Unos informacija trenera";
			cout << "\n2. Informacije trenera";
			cout << "\n3. Brisanje informacija";
			cout << "\n0. Nazad";
			cout << "\nIzaberite opciju: ";
			cin >> izborTrener;
			if (izborTrener == 0)
			{
				break;
			}
			else {
				greskaIzbora(izborTrener);
			}

			switch (izborTrener)
			{
			case 1: {
				trener.unosTrenera();
				trener.upisivanjeTrenera();
				cout << "\nUspesno ste upisali podatke.";
				break;
			}
				  break;
			case 2: {
				if (prazanFile(trenerFile))
				{
					cout << "\nFajl " << trenerFile << " je prazan.";
				}
				else {
					trener.prikazTrenera();
				}
			}
				  break;
			case 3: {
				brisanjePodatakaUFajlu("trener.txt");
				cout << "\nUspesno ste obrisali podatke.";
			}
				  break;
			}
		}
		}
	} while (1);

	Igrac::sacuvajIgrace(noviIgraci, brojIgraca);

	delete[] noviIgraci;

	return 0;
}


//Funkcije
void brisanjePodatakaUFajlu(const string nazivFajla) {
	ofstream file(nazivFajla);
	file << "";
	file.close();
}

void greskaIzbora(int izbor) {
	if (!izbor) {
		cout << "\nNiste uneli broj!";
		exit(1);
	}
}
bool prazanFile(const string& file) {
	ifstream imeFile(file);

	// Provera da li je fajl otvoren
	if (!imeFile.is_open()) {
		cerr << "Nije moguce otvoriti fajl " << file << endl;
		return false;
	}

	// Pomeranje na kraj fajla
	imeFile.seekg(0, ios::end);

	// Provera da li je fajl prazan (EOF na pocetku)
	if (imeFile.tellg() == 0) {
		imeFile.close();
		return true;
	}

	imeFile.close();
	return false;
}

// Proverava da li u zadatom stringu postoji barem jedan karakter koji je cifra
// Vraca true ako postoji cifra, inace false
bool brojString(const string& s) {
	for (char c : s) {
		if (isdigit(c)) {
			return true;
		}
	}
	return false;
}

// Proverava da li zadati string predstavlja broj i ima tacno cetiri cifre
// Vraca true ako string predstavlja broj sa tacno cetiri cifre, inace false.
bool duzinaBroja(string s) {
	// Provera duzine stringa
	if (s.size() != 4) {
		return false;
	}

	// Provera da li su svi karakteri u stringu cifre
	for (char c : s) {
		if (!isdigit(c)) {
			return false;
		}
	}

	// Ako su sve cifre i duzina ispravne, vraca true
	return true;
}


string velikoMaloSlovo(string podatak) {
	transform(podatak.begin(), podatak.end(), podatak.begin(), ::tolower);
	podatak[0] = toupper(podatak[0]);
	return podatak;
}