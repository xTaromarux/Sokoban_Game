#pragma once
#include <iostream>

class Vector2D
{
public:
	
	
	
	
	
	
	//* zmienne okreslajace pozycje
	float x;
	float y;

	Vector2D();
	Vector2D(float x, float y);

	//*/ funkcja zerujaca wektor
	Vector2D& Zero();

	//*/ funkcja dodajaca 
	Vector2D& Add(const Vector2D& vec);
	
	//*/ funkcja odejmujaca
	Vector2D& Subtract(const Vector2D& vec);

	//*/ funkcja mnozaca
	Vector2D& Multiply(const Vector2D& vec);

	//*/ definicja przeciazenia operatora +
	friend Vector2D& operator+(Vector2D& v1, const Vector2D& v2);

	//*/ definicja przeciazenia operatora -
	friend Vector2D& operator-(Vector2D& v1, const Vector2D& v2);

	//*/ definicja przeciazenia operatora *
	Vector2D& operator*(const int& i);

	//*/ definicja przeciazenia operatora +=
	Vector2D& operator+=(const Vector2D& vec);

	//*/ definicja przeciazenia operatora -=
	Vector2D& operator-=(const Vector2D& vec);

	//*/ definicja przeciazenia operatora <<
	friend std::ostream& operator<<(std::ostream& stream, const Vector2D& vec);
};