#ifndef COORDENADAS_HPP
#define COORDENADAS_HPP


//_________________________________________________________________________________________________________________________________

class Coordenadas
{
public:
	Coordenadas();
	Coordenadas(int, int);
	~Coordenadas();

	/* Funções get */
	int getX() const;
	int getY() const;
	void getXY(int*, int*) const;

	/* Funções set */
	void setX(int);
	void setY(int);
	void setXY(int, int);

private:
	int _x;
	int _y;
};
//_________________________________________________________________________________________________________________________________


#endif