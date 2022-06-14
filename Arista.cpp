#include "Arista.h"

Arista::Arista(Vertice* _dest, int _precio)
{
	dest = _dest; //vertice al que se desea llegar
	precio = _precio; //valor
	sig = NULL;
}
