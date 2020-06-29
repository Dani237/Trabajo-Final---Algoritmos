#pragma once
#include <functional>
#include <string>

template<typename T>
struct Nodo {
	T valor;
	Nodo* anterior;
	Nodo* siguiente;
	Nodo(T v) {
		valor = v;
		anterior = nullptr;
		siguiente = nullptr;
	}
};

template<typename T>
class ListDE
{
private:
	Nodo<T>* inicio;
	Nodo<T>* final;
public:
	int tam;

	ListDE()
	{
		inicio = nullptr;
		final = nullptr;
		tam = 0;
	}

	~ListDE()
	{
		inicio = final = nullptr;
		delete inicio;
		delete final;
	}

	void push_back(T dato)
	{
		Nodo<T>* newNodo = new Nodo<T>(dato);
		if (tam == 0) {
			inicio = newNodo;
			final = newNodo;
		}
		else {
			newNodo->anterior = final;
			final->siguiente = newNodo;
			final = newNodo;
		}
		tam++;
		newNodo = nullptr;
		delete newNodo;
	}

	void InsertarPos(T dato, int pos)
	{
		Nodo<T>* newNodo = new Nodo<T>(dato);
		if (pos == 0) InsertarInicio(dato);
		else if (pos == tam) InsertarFinal(dato);
		else {
			Nodo<T>* previo = inicio, *posterior = nullptr;
			for (int i = 0; i < pos - 1; i++)
			{
				previo = previo->siguiente;
			}
			posterior = previo->siguiente;

			newNodo->anterior = previo;
			previo->siguiente = newNodo;

			newNodo->siguiente = posterior;
			posterior->anterior = newNodo;

			tam++;
			previo = posterior = nullptr;
			delete previo;
			delete posterior;
		}
	}

	T at(int pos) {
		Nodo<T>* index = inicio;
		if (pos == 0) return inicio->valor;
		if (pos == tam - 1) return final->valor;
		if (pos > 0 && pos < tam - 1) {
			for (int i = 0; i < pos; i++) {
				index = index->siguiente;
			}
		}
		T SuperDato = index->valor;
		index = nullptr;
		delete index;
		return SuperDato;
	}
	int size()
	{
		return tam;
	}
};