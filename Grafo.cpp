#include "Grafo.h"

Grafo::Grafo()
{
	primero = NULL;
	tamano = 0;
}

bool Grafo::EstaVacio()
{
	return tamano == 0;
}

int Grafo::ObtenerTamano()
{
	return tamano;
}

Vertice* Grafo::ObtenerVertice(string nombre)
{
	Vertice* i = primero;

	while (i != NULL)
	{
		if (i->nombre == nombre)
			return i;

		i = i->sig;
	}

	return NULL;
}

void Grafo::InsertaVertice(string nombre)
{
	if (ObtenerVertice(nombre) == NULL)
	{
		Vertice* nuevo = new Vertice(nombre);

		if (EstaVacio())
			primero = nuevo;
		else
		{
			Vertice* i = primero;

			while (i->sig != NULL)
				i = i->sig;

			i->sig = nuevo;
		}

		tamano++;
	}
	else
		cout << "Ese vertice ya existe" << endl;
}

void Grafo::InsertaArista(string ori, string dest, int precio)
{
	Vertice* vori = ObtenerVertice(ori);
	Vertice* vdest = ObtenerVertice(dest);

	if (vori == NULL)
		cout << "El vertice origen no se encuentra o existe en el grafo" << endl;

	if (vdest == NULL)
		cout << "El vertice destino no se encuentra o existe en el grafo" << endl;

	if (vori != NULL && vdest != NULL)
	{
		Arista* nueva = new Arista(vdest, precio);

		if (vori->ari == NULL)
			vori->ari = nueva;
		else
		{
			Arista* j = vori->ari;

			while (j->sig != NULL)
				j = j->sig;

			j->sig = nueva;
		}
	}
}

void Grafo::MostrarListaAdyacencia()
{
	Vertice* i = primero;

	while (i != NULL)
	{
		Arista* j = i->ari;
		cout << i->nombre << " = ";

		while (j != NULL)
		{
			cout << i->nombre << " -> " << j->precio << " -> " << j->dest->nombre << ",";
			j = j->sig;
		}

		cout << endl;
		i = i->sig;
	}
}

void Grafo::EliminarAristas(Vertice* vertice)
{
	if (vertice == NULL)
		return;

	Arista* i = vertice->ari;

	while (vertice->ari != NULL)
	{
		i = vertice->ari;
		vertice->ari = vertice->ari->sig;
		cout << "Arista " << vertice->nombre << " -> " << i->dest->nombre << " eliminada" << endl;
		delete(i);
	}
}

void Grafo::EliminarAristasDestino(string dest)
{
	Vertice* i = primero;

	while (i != NULL)
	{
		if (i->nombre == dest || i->ari == NULL)
		{
			i = i->sig;
			continue;
		}

		if (i->ari->dest->nombre == dest)
		{
			Arista* j = i->ari;
			i->ari = i->ari->sig;
			cout << "Arista " << i->nombre << " -> " << dest << " eliminada" << endl;
			delete(j);
		}
		else
		{
			Arista* x = i->ari;
			Arista* y = x->sig;

			while (y != NULL)
			{
				if (y->dest->nombre == dest)
				{
					x->sig = y->sig;
					cout << "Arista " << i->nombre << " -> " << dest << " eliminada" << endl;
					delete(y);
				}

				x = y;
				y = y->sig;
			}
		}

		i = i->sig;
	}
}

void Grafo::EliminarVertice(string nombre)
{
	if (primero->nombre == nombre)
	{
		Vertice* i = primero;
		primero = primero->sig;
		EliminarAristas(i);
		EliminarAristasDestino(i->nombre);
		cout << "Vertice " << nombre << " fue eliminado" << endl;
		delete(i);
		tamano--;
	}
	else
	{
		Vertice* i = primero;
		Vertice* j = i->sig;
		bool existe = false;

		while (j != NULL)
		{
			if (j->nombre == nombre)
			{
				i->sig = j->sig;
				EliminarAristas(j);
				EliminarAristasDestino(j->nombre);
				cout << "Vertice " << nombre << " fue eliminado" << endl;
				delete(j);
				tamano--;
				existe = true;
				break;
			}

			i = j;
			j = j->sig;
		}

		if (!existe)
			cout << "El vertice especificado no existe" << endl;
	}
}

void Grafo::EliminarArista(string ori, string dest)
{
	Vertice* vori = ObtenerVertice(ori);
	Vertice* vdest = ObtenerVertice(dest);

	if (vori == NULL)
		cout << "El vertice origen no existe" << endl;

	if (vdest == NULL)
		cout << "El vertice destino no existe" << endl;

	if (vori != NULL && vdest != NULL)
	{
		if (vori->ari->dest == vdest)
		{
			Arista* i = vori->ari;
			vori->ari = vori->ari->sig;
			cout << "Arista " << ori << " -> " << dest << " eliminada" << endl;
			delete(i);
		}
		else
		{
			Arista* i = vori->ari;
			Arista* j = i->sig;

			while (j != NULL)
			{
				if (j->dest == vdest)
				{
					i->sig = j->sig;
					cout << "Arista " << ori << " -> " << dest << " eliminada" << endl;
					delete(j);
					break;
				}

				i = j;
				j = j->sig;
			}
		}
	}
}

void Grafo::EliminarTodo()
{
	Vertice* i = primero;

	while (primero != NULL)
	{
		i = primero;
		primero = primero->sig;
		EliminarAristas(i);
		EliminarAristasDestino(i->nombre);
		cout << "Vertice " << i->nombre << " eliminado" << endl;
		delete(i);
		tamano--;
	}
}



bool OrderPorCosto(const pair<Vertice*, int>& a, const pair<Vertice*, int>& b)
{
	return a.second < b.second;
}


void Grafo::MostrarRutaEncontrada(stack<pair<Vertice*, Vertice*>> pilaPar, Vertice* vdest)
{
	Vertice* destinoActual = vdest;

	while (!pilaPar.empty())
	{
		cout << destinoActual->nombre << " <- ";

		while (!pilaPar.empty() && pilaPar.top().second != destinoActual)
			pilaPar.pop();

		if (!pilaPar.empty())
			destinoActual = pilaPar.top().first;
	}
}

bool CostoMinimo(const pair<Vertice*, int>& a, const pair<Vertice*, int>& b)
{
	return a.second < b.second;
}

//DESDE AQUI EMPIEZA EL ALGORITMO DIJKSTRA
void Grafo::Dijkstra(string origen)
{
	Vertice* vorigen = ObtenerVertice(origen);

	if (vorigen == NULL)
		cout << "El vertice origen no existe" << endl;
	else
	{
		map<Vertice*, map<Vertice*, int>> matriz;
		map<Vertice*, bool> visitados;
		map<Vertice*, Vertice*> rutas;
		map<Vertice*, int> cola;
		map<Vertice*, int> distancias;

		Vertice* vi = primero;

		// Inicializar colecciones de datos
		while (vi != NULL)
		{
			visitados[vi] = false;
			rutas[vi] = NULL;
			distancias[vi] = numeric_limits<int>::max();

			Vertice* vj = primero;

			while (vj != NULL)
			{
				matriz[vi][vj] = numeric_limits<int>::max();
				vj = vj->sig;
			}

			Arista* aj = vi->ari;

			while (aj != NULL)
			{
				matriz[vi][aj->dest] = aj->precio;
				aj = aj->sig;
			}

			vi = vi->sig;
		}

		distancias[vorigen] = 0;
		visitados[vorigen] = true;
		cola[vorigen] = distancias[vorigen];

		while (!cola.empty())
		{
			// Encuentra el vertice con el costo menor en la cola
			map<Vertice*, int>::iterator iter = min_element(cola.begin(), cola.end(), CostoMinimo);
			visitados[iter->first] = true;

			// Recorre todos los vertices que tiene como destino
			Arista* ai = iter->first->ari;

			while (ai != NULL)
			{
				if (!visitados[ai->dest])
				{
					if (distancias[ai->dest] > distancias[iter->first] + matriz[iter->first][ai->dest])
					{
						distancias[ai->dest] = distancias[iter->first] + matriz[iter->first][ai->dest];
						rutas[ai->dest] = iter->first;
						cola[ai->dest] = distancias[ai->dest];
					}
				}

				ai = ai->sig;
			}

			cola.erase(iter->first);
		}

		// Muestra los vertices destino con su respectivo peso total
		for (map<Vertice*, int>::iterator i = distancias.begin(); i != distancias.end(); i++)
			cout << i->first->nombre << ": " << i->second << endl;


		// Muestra las rutas completas
		for (map<Vertice*, Vertice*>::iterator i = rutas.begin(); i != rutas.end(); i++)
		{
			Vertice* vAct = i->first;

			while (vAct != NULL)
			{
				cout << vAct->nombre << " <- ";
				vAct = rutas[vAct];
			}

			cout << endl;
		}
	}
}
