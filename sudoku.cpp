#include <fstream>
#include <iostream>
using namespace std;
#define DIMPICCOLA 3
#define DIM (DIMPICCOLA*DIMPICCOLA)
struct cella {
	int valore = 0;
	bool sicuro = false;
};
//struttura dati matrice 9x9
struct cella m[DIM][DIM];
//inizializza vuoto
void sudokuVuoto() {
	for(int i=0; i<DIM; i++)
		for(int j=0; j<DIM; j++)
			m[i][j].valore=0;
}
//lettura da file
void leggiFile(string nome) {
	char c;
	int i=0, j=0, k=0;
	ifstream fin(nome); //si crea fin e si apre il file con nome specificato
	while(fin.get(c)) //si legge un carattere e se non si è alla fine del file
	{
		//cout << c; //comunico la lettura del carattere c
		if(c != '\n' && c != '.' && c != '?')
		{
			i = k / DIM; // la riga è il quoziente
			j = k % DIM; // la colonna è il resto
			m[i][j].valore = c - '0';
			//se non è inserito è insicuro per forza...
			if(m[i][j].valore == 0)
				m[i][j].sicuro = false;
			else
				m[i][j].sicuro = true;
			//cout << "' i = " << i << ", j = " << j << "' - ";
			k++;
		}
		/*se non leggo un numero è un indicazione di sicurezza
		o un a capo che non mi interessa*/
		else if( c == '.' && m[i][j].valore != 0) //se non è inserito non è sicuro
			m[i][j].sicuro = true;
		else if( c == '?')
			m[i][j].sicuro = false;
	}
	fin.close(); //si chiude fin
}
void salvaFile(string nome) {
	ofstream fout(nome); //si crea fout e si crea il file con il nome dato
	for(int i=0; i<DIM; i++) {
		for(int j=0; j<DIM; j++) {
			if(m[i][j].valore != -1)
				fout << m[i][j].valore; // si scrive su fout il contenuto della cella
			else	fout << 0; //se c'è stato un errore lo si ignora e si scrive 0
			if(m[i][j].sicuro)
				fout << '.'; //si aggiunge . se è sicuro
			else
				fout << '?'; //si aggiunge ? se non è sicuro
		}
		fout << '\n'; //si scrive 'a capo' alla fine di ogni riga
	}
	fout.close(); //si chiude fout
}
//stampa
void scriviLinea() {
	cout << "\n   -";
	for(int i=0; i<DIM; i++)
		cout << "----";
	cout << "\n";
}
void stampaSudoku() {
	system("clear");
	cout << "     A   B   C | D   E   F | G   H   I";
	scriviLinea();
	for(int i=0; i<DIM; i++) {
		cout << i+1 << "  |";
		for(int j=0; j<DIM; j++)
		{
			if(m[i][j].sicuro)
				cout << "(";
			else
				cout << " ";
			switch(m[i][j].valore)
			{
				case 0:
					cout << " ";
					break;
				case -1:
					cout << "X";
					break;
				default:
					cout << m[i][j].valore;
					break;
			}
			if(m[i][j].sicuro)
				cout << ")";
			else
				cout << " ";
			cout << "|";
		}
		scriviLinea();
	}
}
bool cond(int n) {
	return (0 <= n && n <= DIM);
}
bool okNum(int riga, int colonna, int n) {
	bool inserisci = true;
	//stessa riga e stessa colonna
	for(int i = 0; i < DIM; i++) {
		if(i != riga && m[i][colonna].valore == n)
			{inserisci = false; cout << "errore, stessa riga\n";}	
		if(i != colonna && m[riga][i].valore == n)
			{inserisci = false; cout << "errore, stessa colonna\n";}
	}
	if(inserisci) { //se non sto sprecando risorse...
		//quale cella deve essere controllata?
		int rigacella = riga / DIMPICCOLA, colonnacella = colonna / DIMPICCOLA;
		//controllo stessa casella
		for(int i = 0; i < DIMPICCOLA; i++)
			for(int j=0; j < DIMPICCOLA; j++)
				if(i != riga && j != colonna &&
				  m[rigacella*DIMPICCOLA+i]
				  [colonnacella*DIMPICCOLA+j].valore == n)
				{inserisci = false; cout << "errore, stessa casella\n";}
	}
	return inserisci;
}
bool inputNumero() {
	bool ok = true;
	int riga, colonna, numero;
	cout << "riga: ";
	cin >> riga;
	cout << "colonna: ";
	cin >> colonna;
	cout << "numero: ";
	cin >> numero;
	//se ho inserito dati validi da input (riga, colonna, numero tra 1 e 9)
	if(cond(riga--) && cond(colonna--) && (1 <= numero && numero <= DIM)) {
		//se non sto modificando un numero preesistente sicuro
		if(m[riga][colonna].sicuro == false)
			//se lo posso inserire senza errori
			if(okNum(riga, colonna, numero))
				m[riga][colonna].valore = numero;
			else
				m[riga][colonna].valore = -1;
	}			
	else
		ok = false;
	return ok;
}
int main() {	
	char risposta;
	string fileInput = "", fileOutput = "out";
	cout << "ATTENZIONE: questa versione del gioco\nNON controlla se il sudoku in input è risolvibile \no ci sono errori evidenti nella sua generazione!\n";
	cout << "vuoi leggere un file? (Y/N)";
	cin >> risposta;
	if(risposta == 'y' || risposta == 'Y') {
		cout << "inserisci nome file input (senza estensione): ";
		cin >> fileInput;
		fileInput = "./file/" + fileInput + ".txt";
		cout << "lo trovi in " << fileInput << endl;
		leggiFile(fileInput);
	}
	else
		sudokuVuoto();
	bool ok = true;
	do {
		stampaSudoku();
		ok = inputNumero();
	} while(ok);
	cout << "inserisci nome file di salvataggio (senza estensione): ";
	cin >> fileOutput;
	fileOutput = "./file/" + fileOutput + ".txt";
	cout << "lo trovi in " << fileOutput << endl;
	salvaFile(fileOutput);
	return 0;
}
