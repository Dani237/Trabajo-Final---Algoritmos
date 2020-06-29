#pragma once
#include "Arbol.h"
#include "fstream"
#include "sstream"
#include <algorithm>

#include "ListDE.h"

using namespace std;

template <typename T>
class DataBase
{
public:
	DataBase(ListDE<ListDE<string>*>* ListaRegistro)
	{
		mibd = ListaRegistro;
		VectorArboles = new ListDE<ABB<ListDE<T>*>*>();
		ArbolFila = new ABB<ListDE<T>*>();
	}
	DataBase() {
		numberCol = 0;
		mibd = new ListDE<ListDE<T>*>;
		VectorArboles = new ListDE<ABB<ListDE<T>*>*>();
		ArbolFila = new ABB<ListDE<T>*>();
	}
	~DataBase() {}

	void leerDataSet(ListDE<T>*& nomcol, bool cabecera = true) {
		ifstream data("DataSet.txt");
		string reg, cols;
		if (cabecera) {
			getline(data, reg);
			stringstream cc(reg);
			while (getline(cc, cols, ','))
				nomcol->push_back(cols);
		}

		while (getline(data, reg)) {
			stringstream ss(reg);
			dividircampos(ss);
		}
	}

	void dividircampos(istream& registro) {
		ListDE<string>* filas = new ListDE<string>;
		string temp;
		while (getline(registro, temp, ',')) {
			filas->push_back(temp);
		}
		mibd->push_back(filas);
	}

	void IndexarTotal(ListDE<string>* nomcol)
	{
		string cadenita;
		bool let = false;
		auto compSTR = [=](ListDE<string>* a, ListDE<string>* b)-> bool {
			string a1, b1;
			a1 = a->at(numberCol);
			b1 = b->at(numberCol);
			transform(a1.begin(), a1.end(), a1.begin(), ::tolower);
			transform(b1.begin(), b1.end(), b1.begin(), ::tolower);
			return a1.compare(b1) < 0; 
		};
		auto compNUM = [=](ListDE<string>* a, ListDE<string>* b)-> bool {return stof(a->at(numberCol)) < stof((b->at(numberCol))); };

		for (int i = 0; i < mibd->at(0)->size(); ++i)
		{
			let = false;
			numberCol = i;
			ABB<ListDE<T>*>* ArbolMolde = new ABB<ListDE<T>*>();
			cadenita = mibd->at(0)->at(i);
			for (int k = 0; k < cadenita.length(); k++) {
				if (cadenita[k] >= 65 && cadenita[k] <= 122) let = true;
			}

			for (int j = 0; j < mibd->size(); ++j)
			{
				if(let) ArbolMolde->AgregarNodo(mibd->at(j), compSTR);
				else ArbolMolde->AgregarNodo(mibd->at(j), compNUM);
				
			}
			VectorArboles->push_back(ArbolMolde);
		}
	}

	void mostrarDatos(int mo)
	{
		auto imprimir = [](ListDE<string>* a) {
			for (int i = 0; i < a->size(); ++i)
			{
				cout << a->at(i) << " ";
			}
			cout << endl; };

		VectorArboles->at(mo)->Orden(imprimir);
		cout << endl;

		/*Para mostrar todo indexado
		for (int i = 0; i < VectorArboles->size(); ++i)
		{
			VectorArboles->at(i)->Orden(imprimir);
			cout << endl;
		}*/

	}

	void OrdenarMostrar(int n, int opcion)
	{
		auto imprimir = [](ListDE<string>* a) {
			for (int i = 0; i < a->size(); ++i)
			{
				cout << a->at(i) << " ";
			}
			cout << endl; };
		cout << endl;
		switch (opcion)
		{
		case 1:
			VectorArboles->at(n)->Orden(imprimir);
			break;
		case 2:
			VectorArboles->at(n)->OrdenDes(imprimir);
			break;
		}
	}

	void show(ListDE<int>*& colmostrar)
	{
		if (mibd->size() > 0)
		{
			cout << endl;

			for (int i = 0; i < mibd->size(); ++i)//Filas
			{
				for (int l = 0; l < colmostrar->size(); ++l)
				{
					cout << mibd->at(i)->at(colmostrar->at(l)); // Fila * Columna
					if (l < colmostrar->size() - 1)
					{
						cout << "-";
					}
				}
				cout << endl;
			}
		}
		else
			cout << "No hay informacion almacenada";
	}

	void AplicarFiltros(ListDE<int>*& colmostrar1)
	{
		int valor;
		char caracter;
		string substr;

		int opcion;
		cout << endl;
		cout << "1. Mayor a" << endl;
		cout << "2. Menor a" << endl;
		cout << "3. Igual a" << endl;
		cout << "-----------------" << endl;
		cout << "4. Inicia con" << endl;
		cout << "5. Finaliza con " << endl;
		cout << "6. Esta contenido en" << endl;
		cout << "7. No esta contenido en" << endl;
		for (int j = 0; j < colmostrar1->size(); ++j)
		{

			cout << "Elegir Filtro para la columna " << colmostrar1->at(j) << endl;
			cout << "Mi opcion es: ";  cin >> opcion;
			if (opcion == 1 || opcion == 2 || opcion == 3)
			{
				cout << "Ingrese Valor: "; cin >> valor;

				auto compEnteros2 = [=](ListDE<string>* a) {
					if (opcion == 1) {
						if (stoi(a->at(colmostrar1->at(j))) > valor) {
							for (int i = 0; i < a->size(); i++)
								cout << a->at(i) << "\t";
							cout << endl;
						}
					}
					else if (opcion == 2) {
						if (stoi(a->at(colmostrar1->at(j))) < valor) {
							for (int i = 0; i < a->size(); i++)
								cout << a->at(i) << "\t";
							cout << endl;
						}
					}
					else {
						if (stoi(a->at(colmostrar1->at(j))) == valor) {
							for (int i = 0; i < a->size(); i++)
								cout << a->at(i) << "\t";
							cout << endl;
						}
					}
				};

				switch (opcion)
				{
				case 1:
					VectorArboles->at(colmostrar1->at(j))->Orden(compEnteros2);
					break;
				case 2:
					VectorArboles->at(colmostrar1->at(j))->Orden(compEnteros2);
					break;
				case 3:
					VectorArboles->at(colmostrar1->at(j))->Orden(compEnteros2);
					break;
				}
			}
			if (opcion == 4 || opcion == 5)
			{
				cout << "Ingrese Caracter: "; cin >> caracter;

				auto iniciaCon = [=](ListDE<string>* a) {
					if (tolower(a->at(colmostrar1->at(j))[0]) == tolower(caracter)) {
						for (int i = 0; i < a->size(); i++)
							cout << a->at(i) << "\t";
						cout << endl;
					}
				};
				auto finalizaCon = [=](ListDE<string>* a) {
					int nc = a->at(0).size() - 1;
					if (tolower((a->at(j))[nc]) == tolower(caracter)) {
						for (int i = 0; i < a->size(); i++)
							cout << a->at(i) << "\t";
						cout << endl;
					}
				};

				switch (opcion)
				{
				case 4:
					VectorArboles->at(colmostrar1->at(j))->Orden(iniciaCon);
					break;
				case 5:
					VectorArboles->at(colmostrar1->at(j))->Orden(finalizaCon);
					break;
				}
			}
			if (opcion == 6 || opcion == 7)
			{
				cout << "Ingrese string: "; cin >> substr;

				auto contenidoEn = [=](ListDE<string>* a) {
					string valor = a->at(colmostrar1->at(j));
					auto it = valor.find(substr);
					if (it != string::npos){
						for (int l = 0; l < a->size(); ++l)
							cout << a->at(l) << "\t";
						cout << endl;
					}
				};
				auto noContenidoEn = [=](ListDE<string>* a) {
					string valor = a->at(colmostrar1->at(j));
					auto it = valor.find(substr);
					if (it == string::npos) {
						for (int l = 0; l < a->size(); ++l)
							cout << a->at(l) << "\t";
						cout << endl;
					}
				};

				switch (opcion)
				{
				case 6:
					VectorArboles->at(colmostrar1->at(j))->Orden(contenidoEn);
					break;
				case 7:
					VectorArboles->at(colmostrar1->at(j))->Orden(noContenidoEn);
					break;
				}
			}
			colmostrar1->tam = 0;
		}
	}

	void exportarDatos()
	{
		string nombre; char separador;
		cout << "Digite el nombre con que quiere guardar el archivo: "; cin >> nombre;
		cout << "Elija el caracter separador: "; cin >> separador;
		
		ofstream archivoEscritura;
		archivoEscritura.open(nombre + ".txt", ios::trunc);
		for (int i = 0; i < mibd->size(); ++i)
		{
			for (int j = 0; j < mibd->at(0)->size(); ++j)
			{
				archivoEscritura << mibd->at(i)->at(j);
				if (j < mibd->at(0)->size() - 1)
				{
					archivoEscritura << separador;
				}
			}
			archivoEscritura << endl;
		}
		cout << endl << "Se guardo el archivo correctamente.";
	}

private:
	ListDE<ListDE<T>*>* mibd; //GESTIONA LAS FILAS
	ABB<ListDE<T>*>* ArbolFila;
	ListDE<ABB<ListDE<T>*>*>* VectorArboles;

	string cadena;
	int numberCol;
	ifstream archivo;
};