#pragma once
#include <functional>
#include <string>

using namespace std;

template <class G, class C = G>
class ABB
{
private:
	long cantidad;
	template <class G, class C = G>
	class Nodo
	{
	public:
		G valor;
		Nodo<G>* izquierdo;
		Nodo<G>* derecho;
		int altura;
		Nodo(G value)
		{
			izquierdo = derecho = nullptr;
			valor = value;
			altura = 0;
		}
	};

	Nodo<G>* raiz;
	//function<bool(G, G)> criterioOrden;

	//ROTACIONES

	void _rotarIzquierda(Nodo<G>* x, Nodo<G>* y, Nodo<G>*& p) {
		p = y;
		x->derecho = y->izquierdo;
		x->altura = _altura(x);
		y->izquierdo = x;
		y->altura = _altura(p);
	}

	void _rotarDerecha(Nodo<G>* x, Nodo<G>* y, Nodo<G>*& p) {
		p = x;
		y->izquierdo = x->derecho;
		y->altura = _altura(y);
		x->derecho = y;
		x->altura = _altura(p);
	}

	int _altura(Nodo<G>* nodo) {
		if (nodo == nullptr) return 0;
		int hi = _altura(nodo->izquierdo);
		int hd = _altura(nodo->derecho);
		return 1 + (hi > hd ? hi : hd);
	}

	void balancear(Nodo<G>*& nodo) {
		//BALANCEAR

		int hi = _altura(nodo->izquierdo); 
		int hd = _altura(nodo->derecho);
		int dif = hd - hi;
		if (dif > 1) { //pesado a la derecha
			//verificar si es un intercambio em zig zag
			int hdi = _altura(nodo->derecho->izquierdo);
			int hdd = _altura(nodo->derecho->derecho);
			if (hdi > hdd) 
				_rotarDerecha(nodo->derecho->izquierdo, nodo->derecho, nodo->derecho); //Esto solo aplica a zig zag
			_rotarIzquierda(nodo, nodo->derecho, nodo); // Esto aplica para ambos
		}
		else if (dif < -1) { //Pesado por la izquierda
			int hdi = _altura(nodo->izquierdo->izquierdo);
			int hii = _altura(nodo->izquierdo->derecho);
			if (hdi > hii)
				_rotarIzquierda(nodo->izquierdo, nodo->izquierdo->derecho, nodo->izquierdo); //Aplica para zig zag
			_rotarDerecha(nodo->izquierdo, nodo, nodo); // Aplica para los dos
		}
	}

	void _AgregarNodo(Nodo<G>*& nodo, G value, function<bool(G, G)> criterio)
	{
		if (nodo == nullptr)
		{
			nodo = new Nodo<G>(value);
			++cantidad;
		}
		else if (criterio(value, nodo->valor))
			_AgregarNodo(nodo->izquierdo, value, criterio);
		else
			_AgregarNodo(nodo->derecho, value, criterio);

		//balancear(nodo);

		//Volver a calcular las alturas
		//int hi = _altura(nodo->izquierdo);
		//int hd = _altura(nodo->derecho);
		//nodo->altura = _altura(nodo);

	}
	void _Buscar(Nodo<G>* nodo, G value, bool& encontrar)
	{
		if (nodo == nullptr)
			encontrar = false;
		else
		{
			if (value == nodo->valor)
			{
				encontrar = true;
				return;
			}
			else if (value < nodo->valor)
				_Buscar(nodo->izquierdo, value, encontrar);
			else
				_Buscar(nodo->derecho, value, encontrar);
		}
	}
	void _eliminarTodo(Nodo<G>* nodo)
	{
		if (nodo != nullptr)
		{
			_eliminarTodo(nodo->izquierdo);
			_eliminarTodo(nodo->derecho);
			delete nodo;
		}
	}
	void _EnOrden(Nodo<G>* nodo, function<void(G)> criterioImpresion)
	{
		if (nodo == nullptr) {
			return;
		}
		else {
			_EnOrden(nodo->izquierdo, criterioImpresion);
			criterioImpresion(nodo->valor);
			_EnOrden(nodo->derecho, criterioImpresion);
		}
	}

	void _EnOrdenDescendente(Nodo<G>* nodo, function<void(G)> criterioImpresion)
	{
		if (nodo == nullptr) {
			return;
		}
		else {
			_EnOrdenDescendente(nodo->derecho, criterioImpresion);
			criterioImpresion(nodo->valor);
			_EnOrdenDescendente(nodo->izquierdo, criterioImpresion);
		}
	}

	void _PreOrden(Nodo<G>* nodo, function<void(G)> criterioImpresion)
	{
		if (nodo == nullptr) {
			return;
		}
		else {
			criterioImpresion(nodo->valor);
			_EnOrden(nodo->izquierdo, criterioImpresion);
			_EnOrden(nodo->derecho, criterioImpresion);
		}
	}
	void _PostOrden(Nodo<G>* nodo, function<void(G)> criterioImpresion)
	{
		if (nodo == nullptr) {
			return;
		}
		else {
			_EnOrden(nodo->izquierdo, criterioImpresion);
			_EnOrden(nodo->derecho, criterioImpresion);
			criterioImpresion(nodo->valor);
		}
	}

public:
	ABB()
	{
		raiz = nullptr;
		cantidad = 0;
	}
	/*ABB(function<bool(G, G)> cr) {
		criterioOrden = cr;
		raiz = nullptr;
		cantidad = 0;
	}*/
	~ABB()
	{
		_eliminarTodo(raiz);
	}

	void AgregarNodo(G value, function<bool(G, G)> criterio)
	{
		_AgregarNodo(raiz, value, criterio);
	}
	bool Buscar(G value)
	{
		bool encontrar = false;
		_Buscar(raiz, value, encontrar);
		return encontrar;
	}
	void Orden(function<void(G)> criterio)
	{
		_EnOrden(raiz, criterio);
		//_PreOrden(raiz, criterio);
		//_PostOrden(raiz, criterio);
	}
	void OrdenDes(function<void(G)> criterio)
	{
		_EnOrdenDescendente(raiz, criterio);
	}
};