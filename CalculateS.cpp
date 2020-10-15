#include "CalculateS.h"

CalculateS::CalculateS(void) : index(0)
{
	Vertexes = new double* [3];
	Vertexes[0] = new double[3];
	Vertexes[1] = new double[3];
	Vertexes[2] = new double[3];
}

CalculateS::CalculateS(CalculateS const& src)
{
	*this = src;
}

void	CalculateS::setVertex(double vx, double vy, double vz, int index)
{
	this->Vertexes[index][0] = vx;
	this->Vertexes[index][1] = vy;
	this->Vertexes[index][2] = vz;
}

double	CalculateS::getSpace()
{
	double	space;
	double	VectorAB[3];
	double	VectorAC[3];
	double	ABxAC[3];

	double	mod;

	VectorAB[0] = this->Vertexes[1][0] - this->Vertexes[0][0];
	VectorAB[1] = this->Vertexes[1][1] - this->Vertexes[0][1];
	VectorAB[2] = this->Vertexes[1][2] - this->Vertexes[0][2];

	VectorAC[0] = this->Vertexes[2][0] - this->Vertexes[0][0];
	VectorAC[1] = this->Vertexes[2][1] - this->Vertexes[0][1];
	VectorAC[2] = this->Vertexes[2][2] - this->Vertexes[0][2];

	ABxAC[0] = VectorAB[1] * VectorAC[2] - VectorAB[2] * VectorAC[1];
	ABxAC[1] = VectorAB[2] * VectorAC[0] - VectorAB[0] * VectorAC[2];
	ABxAC[2] = VectorAB[0] * VectorAC[1] - VectorAB[1] * VectorAC[0];

	mod = sqrt(pow(ABxAC[0], 2) + pow(ABxAC[1], 2) + pow(ABxAC[2], 2));

	return mod / 2;
}

CalculateS::~CalculateS()
{
	delete[]Vertexes;
}