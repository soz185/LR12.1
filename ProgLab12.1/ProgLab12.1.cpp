// Работа с векторами и радиусами цилиндров.

#include <iostream>
#include <string>
#include <corecrt_math_defines.h>
using namespace std;

class Radius {
private:
	double radius;
public:
	Radius()
	{
		this->radius = 0;
	}
	Radius(double rad)
	{
		this->radius = rad;
	}
	void readRadius()
	{
		std::cin >> radius;
	}
	void displayRadius()
	{
		std::cout << radius;
	}
	Radius addRadius(Radius rad1, Radius rad2)
	{
		radius = rad1.radius + rad2.radius;
		return *this;
	}
	double returnRadius()
	{
		return radius;
	}
	Radius& operator ++()
	{
		this->radius++;
		return *this;
	}
	Radius operator ++(int unused)
	{
		Radius c = *this;
		++* this;
		return c;
	}

};

class Vector {
protected: double X;
protected: double Y;
protected: double Z;
//private: Radius cylinderRadius;
public:
	static int countOfVectors;
	friend void operator <<(ostream& o, Vector sp);
	friend Vector operator >>(istream& i, Vector& r);

	Vector()
	{
		Radius rad(0);
		X = 0;
		Y = 0;
		Z = 0;
		//cylinderRadius = rad;
		Vector::countOfVectors++;
	}
	Vector(double X, double y, double z)
	{
		this->X = X;
		this->Y = y;
		this->Z = z;
		//this->cylinderRadius = rad;
		Vector::countOfVectors++;
	}

	Vector(int n)
	{
		Radius rad(n);
		this->X = n;
		this->Y = n;
		this->Z = n;
		//this->cylinderRadius = rad;
		Vector::countOfVectors++;
	}

	Vector(const Vector& vector)
	{
		this->X = vector.X * 2;
		this->Y = vector.Y * 2;
		this->Z = vector.Z * 2;
		//this->cylinderRadius = vector.cylinderRadius;
	}

	~Vector() { if (Vector::countOfVectors > 0) Vector::countOfVectors--; }

	static int getCountOfVectors()
	{
		return Vector::countOfVectors;
	}

	double getX() { return this->X; }
	double getY() { return this->Y; }
	double getZ() { return this->Z; }

	void read()
	{
		std::cin >> this->X >> this->Y >> this->Z;
		//this->cylinderRadius.readRadius();
		if (X < -100 || X > 100 || Y < -100 || Y > 100 || Z < -100 || Z > 100)
			throw 0;
	}

	void display()
	{
		std::cout << this->X << "; " << this->Y << "; " << this->Z;
		std::cout << ", радиус = ";
		//cylinderRadius.displayRadius();
	}

	Vector add(Vector vector)
	{
		Vector c;
		c.X = this->X + vector.X;
		c.Y = this->Y + vector.Y;
		c.Z = this->Z + vector.Z;
		//c.cylinderRadius.addRadius(this->cylinderRadius, vector.cylinderRadius);
		return c;
	}

	double length()
	{
		double length = sqrt(this->X * this->X + this->Y * this->Y + this->Z * this->Z);
		return length;
	}

	void length(double* length)
	{
		*length = sqrt(this->X * this->X + this->Y * this->Y + this->Z * this->Z);
	}

	void length(double& length)
	{
		length = sqrt(this->X * this->X + this->Y * this->Y + this->Z * this->Z);
	}


	double scalar(Vector vector)
	{
		double scalar = this->X * vector.X + this->Y * vector.Y + this->Z * vector.Z;
		return scalar;
	}

	virtual double Volume()
	{
		return 0;
	}

	Vector operator+(Vector vector)
	{
		Vector c;
		c.X = this->X + vector.X;
		c.Y = this->Y + vector.Y;
		c.Z = this->Z + vector.Z;
		//c.cylinderRadius.addRadius(this->cylinderRadius, vector.cylinderRadius);
		return c;
	}

	Vector& operator=(Vector& vector)
	{
		this->X = vector.X;
		this->Y = vector.Y;
		this->Z = vector.Z;
		//this->cylinderRadius = vector.cylinderRadius;
		return *this;
	}

	Vector& operator ++()
	{
		this->X++;
		this->Y++;
		this->Z++;
		//this->cylinderRadius++;
		return *this;
	}

	Vector operator ++(int unused)
	{
		Vector c = *this;
		++* this;
		return c;
	}
};

class Cylinder: public Vector
{
private: double height;
public: static int countOfCylinder;
	  Cylinder() : Vector(0, 0, 0) { height = 0; }
	  Cylinder(double X, double Y, double Z, double h) : Vector(X, Y, Z) { height = h; }
	friend void operator <<(ostream& o, Cylinder sp);
	friend Cylinder operator >>(istream& i, Cylinder& r);


	double Volume()
	{
		double volume = height * length() * length() * M_PI;
		return volume;
	}
	static int getCountOfSphere()
	{
		return Cylinder::countOfCylinder++;
	}

	void operator =(Vector vector)
	{
		this->X = vector.getX();
		this->Y = vector.getY();
		this->Z = vector.getZ();
	}
};

int Vector::countOfVectors = 0;
int Cylinder::countOfCylinder = 0;

class Figure
{
protected: virtual void ReturnName() = 0;
};

class Circle :public Figure
{
public: void ReturnName() { cout << "Круг"; }
};

class Square :public Figure
{
public: void ReturnName() { cout << "Квадрат"; }
};
void operator << (ostream& o, Vector v)
{
	cout << v.X << " " << v.Y << " " << v.Z;
}

Vector operator >> (istream& o, Vector& v)
{
	cin >> v.X >> v.Y >> v.Z;
	return v;
}

void operator << (ostream& o, Cylinder sp)
{
	cout << sp.X << " " << sp.Y << " " << sp.Z << " " << sp.height;
}

Cylinder operator >> (istream& o, Cylinder& sp)
{
	cin >> sp.X >> sp.Y >> sp.Z >> sp.height;
	return sp;
}

int main()
{
	setlocale(LC_ALL, "Russian");
	std::string str("Работа с векторами и радиусами цилиндров.\n");
	int length_str = str.length();
	std::cout << str << "Длина строки " << length_str << "\n";
	Vector a, c;
	//Radius rad(1.5);
	Vector b(1, 0, -2);
	printf("Количество созданных векторов: %d\n", Vector::getCountOfVectors());

	bool p = false;
	while (!p)
	{
		p = true;
		try
		{
			printf("Введите координаты и радиус a [-100;100]: ");
			cin >> a;
		}
		catch (...)
		{
			printf("Повторите ввод.\n");
			p = false;
		}
	}

	printf("Цилиндры:\n");
	printf("a ");
	cout << a;
	puts("");
	printf("b ");
	cout << b;
	puts("");

	b++;
	cout << b;
	puts("");

	++b;
	cout << b;
	puts("");
	/*double length1 = 0;
	double length2 = 0;
	a.length(&length1);
	a.length(&length2);
	printf("\nДлина вектора a равна %g\n", a.length());
	printf("Длина вектора a равна %g (через указатель)\n", length1);
	printf("Длина вектора a равна %g (через ссылку)\n", length2);

	printf("Объем цилиндра a равен %g\n", cylinderVolume(a));
	printf("Скалярное произведение векторов a и b равно %g\n", a.scalar(b));

	Vector arr[3] = { 1, 2, 3 };
	printf("arr[0] ");
	cin >> arr[0];
	puts("");
	Vector arrCopy = arr[0];
	printf("arrCopy ");
	cout << arrCopy;
	puts("");

	Vector arrayVector[][2] = { { 1, 2}, { 3, 4 } };
	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 2; j++)
		{
			arrayVector[i][j]++;
			cout << arrayVector[i][j];
			puts("");
		}
	printf("Динамические переменные.\n");
	Vector* din_a = new Vector();
	Vector* din_b = new Vector(1, 0, -2.1, rad);
	Vector* din_c = new Vector();
	printf("Количество созданных векторов: %d\n", Vector::getCountOfVectors());

	Vector* d;
	d = (Vector*)malloc(sizeof(Vector));
	free(d);
	d = (Vector*)calloc(2, sizeof(Vector));
	d = (Vector*)realloc(d, 3 * sizeof(Vector));
	free(d);

	p = false;
	while (!p)
	{
		p = true;
		try
		{
			printf("Введите координаты и радиус a [-100;100]: ");
			(*din_a).read();
		}
		catch (...)
		{
			printf("Повторите ввод.\n");
			p = false;
		}
	}

	printf("Цилиндры:\n");
	printf("a ");
	(*din_a).display();
	puts("");
	printf("b ");
	(*din_b).display();
	puts("");

	printf("Мелкое копирование.\n");
	din_a = din_b;
	printf("a = b =  ");
	(*din_a).display();
	puts("");
	(*din_b)++;
	printf("b + 1, a =  ");
	(*din_a).display();
	puts("");

	printf("Глубокое копирование.\n");
	*din_b = *din_c;
	printf("b = c =  ");
	(*din_b).display();
	puts("");
	(*din_c)++;
	printf("c + 1, b =  ");
	(*din_b).display();
	puts("");

	printf("\nДлина вектора a равна %g\n", (*din_a).length());
	printf("Скалярное произведение векторов a и b равно %g\n", (*din_a).scalar(*din_b));
	delete din_a;
	delete din_c;

	printf("Динамический массив объектов.\n");
	Vector* din_mas_obj;
	din_mas_obj = new Vector[3]{ 1, 2, 0 };
	printf("Количество созданных векторов: %d\n", Vector::getCountOfVectors());

	printf("Введите координаты и радиус a: ");
	din_mas_obj[0].read();
	printf("Цилиндры:\n");
	printf("a ");
	din_mas_obj[0].display();
	puts("");
	printf("b ");
	din_mas_obj[1].display();
	puts("");

	printf("\nДлина вектора a равна %g\n", din_mas_obj[0].length());
	printf("Скалярное произведение векторов a и b равно %g\n", din_mas_obj[0].scalar(din_mas_obj[1]));
	delete[] din_mas_obj;*/
	Cylinder sp(1, 3, 2, 2);
	sp = b;
	cout << b.Volume() << "\n";
	cout << sp.Volume() << "\n";

	Vector* vector = new Vector(0, 2, 3);
	Cylinder* cylinder = new Cylinder(1, 2, 3, 4);
	vector = cylinder;
	cout << vector->Volume() << "\n";
	cout << cylinder->Volume() << "\n";

	Circle circle;
	Square square;
	circle.ReturnName();
	puts("");
	square.ReturnName();
	puts("");
	return 0;
}
