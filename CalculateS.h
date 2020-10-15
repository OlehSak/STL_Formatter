#include <cmath>

class CalculateS
{
protected:
	double**	Vertexes;
	int			index;

public:
	CalculateS();
	~CalculateS();
	CalculateS(CalculateS const& src);

	void		setVertex(double vx, double vy, double vz, int index);
	double		getSpace();
};

