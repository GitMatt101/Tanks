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