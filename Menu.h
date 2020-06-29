#pragma once
#include <iostream>
#include <conio.h>
#include <string>
#include <vector>

#include "fstream"
#include "sstream"

using namespace std;
using namespace System;

int Menu()
{
	int dato;
	Console::ForegroundColor = ConsoleColor::Cyan;
	cout << "****************************MENU****************************" << endl;
	cout << "**	1. Creacion de tabla e insercion de columnas      **" << endl;
	cout << "**	2. Insertar Datos                                 **" << endl;
	cout << "**	3. Indexar por columnas                           **" << endl;
	cout << "**	4. Seleccion de datos por columnas                **" << endl;
	cout << "**	5. Filtrado de datos por columnas                 **" << endl;
	cout << "**	6. Ordenamiento de datos por columnas             **" << endl;
	cout << "**	7. Exportacion de datos a archivos planos         **" << endl;
	cout << "**	8. Mostrar datos indexados                        **" << endl;
	cout << "**	9. Leer datos de archivo                          **" << endl;
	cout << "**	10. Salir                                         **" << endl;
	cout << "************************************************************" << endl;
	cout << endl;
	cout << "Ingrese su opcion: "; cin >> dato;
	return dato;
}

void CrearTabla(ListDE<string>*& nomcol)
{
	int col;
	string v;

	cout << "Cantidad de columnas: "; cin >> col;
	for (int i = 0; i < col; ++i)
	{
		cout << "Nombre de columna " << i + 1 << ":"; cin >> v;
		nomcol->push_back(v);
	}
}

void cabecera(ListDE<string>*& nomcol)
{
	string data;
	cout << "Ingresar datos de la siguiente forma: dato ENTER, escribir abajo" << endl;
	cout << "Presionar escape para mostrar reporte (Debe estar en la columna 1)" << endl;
	for (int i = 0; i < nomcol->size(); ++i)
	{
		data += nomcol->at(i) + "---";
	}
	cout << data << "\n";
}

void MostrarInfo(ListDE<ListDE<string>*>* ListaRegistro, ListDE<string>* nomcol)
{

	if (ListaRegistro->size() > 0)
	{
		cout << endl;
		cout << "Cantidad de Columnas: " << nomcol->size() << endl;
		cout << "Cantidad de Filas: " << ListaRegistro->size() << endl;
		cout << endl;
	}
	else
		cout << "No hay informacion almacenada";

	for (int i = 0; i < nomcol->size(); i++)
		cout << nomcol->at(i) << "\t\t";

	cout << endl << endl;

	for (int i = 0; i < ListaRegistro->size(); ++i)
	{
		for (int j = 0; j < ListaRegistro->at(i)->size(); ++j)
		{
			cout << ListaRegistro->at(i)->at(j);
			if (j < ListaRegistro->at(i)->size() - 1)
			{
				cout << "\t\t";
			}
		}
		cout << endl;
	}
}

void IngresaDatos(ListDE<ListDE<string>*>* ListaRegistro, ListDE<string>*& nomcol)
{
	char tecla = 1;
	cabecera(nomcol);
	char dato[20];
	while (1)
	{
		if (_kbhit())
		{
			tecla = _getch();
			if (tecla == 27)//Escape
			{
				MostrarInfo(ListaRegistro, nomcol);
				_getch();
				break;
			}
			else
			{
				ListDE<string>* Fila = new ListDE<string>();
				for (int i = 0; i < nomcol->size(); ++i)
				{
					cout << "Ingrese " << nomcol->at(i) << ": "; cin >> dato;
					Fila->push_back(dato);
				}
				ListaRegistro->push_back(Fila);
			}
		}
	}
}