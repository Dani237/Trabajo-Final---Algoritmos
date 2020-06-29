#include <iostream>
#include <conio.h>
#include <string>
#include <vector>

#include "fstream"
#include "sstream"

#include "Arbol.h"
#include "BaseDeDatos.h"
#include "ListDE.h"
#include "Menu.h"

using namespace std;
using namespace System;

void main()
{
	char tecla = 1;
	int colind, cantic, c, cantic1, c1, loc, locopcion, d;
	ListDE<int>* colmostrar = new ListDE<int>();
	ListDE<int>* colmostrar1 = new ListDE<int>();
	DataBase<string>* DB;
	ListDE<string>* nomcol = new ListDE<string>();
	ListDE<ListDE<string>*>* ListaRegistro = new ListDE<ListDE<string>*>();
	do
	{
		switch (Menu())
		{
		case 1:
			Console::ForegroundColor = ConsoleColor::Green;
			CrearTabla(nomcol);
			break;
		case 2:
			Console::ForegroundColor = ConsoleColor::Green;
			IngresaDatos(ListaRegistro, nomcol);
			DB = new DataBase<string>(ListaRegistro);
			break;
		case 3:
			Console::ForegroundColor = ConsoleColor::Green;
			cout << "Indexando columnas........." << endl;
			DB->IndexarTotal(nomcol);
			cout << endl;
			cout << "Columnas indexadas satisfactoriamente";
			break;
		case 4:
			Console::ForegroundColor = ConsoleColor::Yellow;
			cout << "Cuantas columnas desea seleccionar: "; cin >> cantic;
			for (int i = 0; i < cantic; ++i)
			{
				cout << "Columna " << i + 1 << ": "; cin >> c;
				colmostrar->push_back(c - 1);
				cout << endl;
			}
			DB->show(colmostrar);
			break;
		case 5:
			Console::ForegroundColor = ConsoleColor::Yellow;
			cout << "Cuantas columnas desea seleccionar: "; cin >> cantic1;
			for (int i = 0; i < cantic1; ++i)
			{
				cout << "Columna " << i + 1 << ": "; cin >> c1;
				colmostrar1->push_back(c1 - 1);
				cout << endl;
			}
			DB->AplicarFiltros(colmostrar1);
			break;
		case 6:
			Console::ForegroundColor = ConsoleColor::Yellow;
			cout << "Que columna desea ordenar?"; cin >> loc;
			cout << "1. Orden ascendente" << endl;
			cout << "2. Orden descendente" << endl;
			cout << "Mi opcion es: "; cin >> locopcion;
			DB->OrdenarMostrar(loc - 1, locopcion);
			break;
		case 7:
			Console::ForegroundColor = ConsoleColor::Green;
			DB->exportarDatos();
			break;
		case 8:
			Console::ForegroundColor = ConsoleColor::White;
			cout << "Que columna indexada desea mostrar?" << endl;
			cin >> d;
			DB->mostrarDatos(d - 1);
			_getch();
			break;
		case 9:
			Console::ForegroundColor = ConsoleColor::Cyan;
			DB = new DataBase<string>(ListaRegistro);
			DB->leerDataSet(nomcol);
			cout << "Los datos fueron cargados exitosamente" << endl;
			break;
		case 10:
			exit(0);
			break;
		}
		_getch();
		Console::Clear();
	} while (1);
}