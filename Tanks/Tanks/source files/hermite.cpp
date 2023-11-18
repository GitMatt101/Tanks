#include "../header files/hermite.h"
#include "../header files/lib.h"

float dx(int i, float* t, float tens, float bias, float cont, Shape* shape)
{
	if (i == 0)
		return  0.5 * (1.0 - tens) * (1.0 - bias) * (1.0 - cont) * (shape->cpCoordinates[i + 1].x - shape->cpCoordinates[i].x) / (t[i + 1] - t[i]);
	if (i == shape->cpCoordinates.size() - 1)
		return  0.5 * (1.0 - tens) * (1.0 - bias) * (1.0 - cont) * (shape->cpCoordinates[i].x - shape->cpCoordinates[i - 1].x) / (t[i] - t[i - 1]);

	if (i % 2 == 0)
		return 0.5 * (1.0 - tens) * (1.0 + bias) * (1.0 + cont) * (shape->cpCoordinates.at(i).x - shape->cpCoordinates.at(i - 1.0).x) / (t[i] - t[i - 1]) + 0.5 * (1.0 - tens) * (1.0 - bias) * (1.0 - cont) * (shape->cpCoordinates.at(i + 1).x - shape->cpCoordinates.at(i).x) / (t[i + 1] - t[i]);
	else
		return 0.5 * (1.0 - tens) * (1.0 + bias) * (1.0 - cont) * (shape->cpCoordinates.at(i).x - shape->cpCoordinates.at(i - 1.0).x) / (t[i] - t[i - 1]) + 0.5 * (1.0 - tens) * (1.0 - bias) * (1.0 + cont) * (shape->cpCoordinates.at(i + 1).x - shape->cpCoordinates.at(i).x) / (t[i + 1] - t[i]);
}

float dy(int i, float* t, float tens, float bias, float cont, Shape* shape)
{
	if (i == 0)
		return 0.5 * (1.0 - tens) * (1.0 - bias) * (1.0 - cont) * (shape->cpCoordinates.at(i + 1).y - shape->cpCoordinates.at(i).y) / (t[i + 1] - t[i]);
	if (i == shape->cpCoordinates.size() - 1)
		return  0.5 * (1.0 - tens) * (1.0 - bias) * (1.0 - cont) * (shape->cpCoordinates.at(i).y - shape->cpCoordinates.at(i - 1.0).y) / (t[i] - t[i - 1]);

	if (i % 2 == 0)
		return 0.5 * (1.0 - tens) * (1.0 + bias) * (1.0 + cont) * (shape->cpCoordinates.at(i).y - shape->cpCoordinates.at(i - 1.0).y) / (t[i] - t[i - 1]) + 0.5 * (1.0 - tens) * (1.0 - bias) * (1.0 - cont) * (shape->cpCoordinates.at(i + 1).y - shape->cpCoordinates.at(i).y) / (t[i + 1] - t[i]);
	else
		return 0.5 * (1.0 - tens) * (1.0 + bias) * (1.0 - cont) * (shape->cpCoordinates.at(i).y - shape->cpCoordinates.at(i - 1.0).y) / (t[i] - t[i - 1]) + 0.5 * (1.0 - tens) * (1.0 - bias) * (1.0 + cont) * (shape->cpCoordinates.at(i + 1).y - shape->cpCoordinates.at(i).y) / (t[i + 1] - t[i]);
}

float DX(int i, float* t, Shape* d, Shape *p)
{
	if (d->cpCoordinates.at(i).x == 0)
		return dx(i, t, 0.0f, 0.0f, 0.0f, p);
	if (d->cpCoordinates.at(i).x != 0)
		return d->cpCoordinates.at(i).x;
}

float DY(int i, float* t, Shape* d, Shape* p)
{
	if (d->cpCoordinates.at(i).y == 0)
		return dy(i, t, 0.0f, 0.0f, 0.0f, p);
	if (d->cpCoordinates.at(i).y != 0)
		return d->cpCoordinates.at(i).y;
}

/*
	t -> rapporto tra l'indice del punto e il numero totale dei punti
	shape -> la figura dove inserire i vertici e dalla quale si estraggono i punti di controllo
	tan -> variabile dove si inseriscono i punti tangenti alla figura
	d -> derivata della figura
	p -> poligonale della figura
	tg -> indica se le tangenti devono essere calcolate
	pval -> punti di valenza
	center -> punto centrale da cui partono i triangoli per creare la figura
*/
void hermite_interpolation(float* t, Shape* shape, vec4 color_top, vec4 color_bot, Shape* tan, Shape* d, Shape* p, bool tg, int pval, vec3 center)
{
	float p_t = 0, p_b = 0, p_c = 0, x, y;
	float passotg = 1.0f / (float)(pval - 1.0f);

	float tgmapp, ampiezza;
	int is = 0; // indice dell'estremo sinistro dell'intervallo [t(i),t(i+1)] a cui il punto tg appartiene

	shape->vertices.clear();
	shape->colors.clear();
	if (tan != NULL)
		tan->cpCoordinates.clear();
	else
	{
		shape->vertices.push_back(center);	// Punto dal quale partono i triangoli per costruire la forma
		shape->colors.push_back(color_bot);
	}

	for (float tg = 0.0f; tg <= 1.0f; tg += passotg)
	{
		if (tg > t[is + 1])
			is++;
		ampiezza = (t[is + 1] - t[is]);
		tgmapp = (tg - t[is]) / ampiezza;

		x = shape->cpCoordinates[is].x * PHI0(tgmapp) + DX(is, t, d, p) * PHI1(tgmapp) * ampiezza + shape->cpCoordinates[is + 1].x * PSI0(tgmapp) + DX(is + 1, t, d, p) * PSI1(tgmapp) * ampiezza;
		y = shape->cpCoordinates[is].y * PHI0(tgmapp) + DY(is, t, d, p) * PHI1(tgmapp) * ampiezza + shape->cpCoordinates[is + 1].y * PSI0(tgmapp) + DY(is + 1, t, d, p) * PSI1(tgmapp) * ampiezza;
		shape->vertices.push_back(vec3(x, y, 0.0f));
		shape->colors.push_back(color_top);
	}

	if (tan != NULL && tg)
	{
		for (size_t i = 0; i < shape->cpCoordinates.size(); i++)
		{
			tan->cpCoordinates.push_back(vec3(shape->cpCoordinates[i].x + DX(i, t, d, p) / 50, shape->cpCoordinates[i].y + DY(i, t, d, p) / 50, 0.0f));
			tan->cpColors.push_back(vec4(0.0f, 0.0f, 1.0f, 1.0f));
			tan->cpCoordinates.push_back(vec3(shape->cpCoordinates[i].x - DX(i, t, d, p) / 50, shape->cpCoordinates[i].y - DY(i, t, d, p) / 50, 0.0f));
			tan->cpColors.push_back(vec4(0.0f, 0.0f, 1.0f, 1.0f));
		}
	}
}

/*
	color_top -> colore primario
	color_bot -> colore secondario
	shape -> variabile dove memorizzare i nuovi punti
	tan -> variabile dove si inseriscono i punti tangenti alla figura
	d -> derivata della figura
	p -> poligonale della figura
	tg -> indica se le tangenti devono essere calcolate
	pval -> punti di valenza
*/
void build_hermite_curve(vec4 color_top, vec4 color_bot, Shape* shape, Shape* tan, Shape* d, Shape* p, bool tg, int pval, vec3 center)
{
	p->cpCoordinates = shape->cpCoordinates;
	p->cpColors = shape->cpColors;
	/*if (tan != NULL)
		UPDATE_CP_VAO(p);*/

	if (p->cpCoordinates.size() > 1)
	{
		float* t = new float[p->cpCoordinates.size()];
		for (int i = 0; i < p->cpCoordinates.size(); i++)
			t[i] = (float)i / (float)(p->cpCoordinates.size() - 1);

		hermite_interpolation(t, shape, color_top, color_bot, tan, d, p, tg, pval, center);
		shape->nVertices = shape->vertices.size();
	}
}