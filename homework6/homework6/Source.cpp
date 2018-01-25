#include<iostream>
#include<vector>
#include<math.h>
using namespace std;

class Point {
public:
	float x, y;
	void point_display(){
		cout << "x coordinate:" << x << " " << "y coordinate:" << y;
	}
	Point(float a, float b)
	{
		x = a;
		y = b;
	}
	Point(const Point &P) {
		x = P.x;
		y = P.y;
	}
};
class shape
{
protected:
	vector<Point> corners;
public:
	shape() {
		cout << "\nShape :: default constructor\n";
	}
	shape(const shape &S) {
		for (int i = 0; i < corners.size(); i++)
			corners[i] = S.corners[i];
	}
	~shape() {
		cout << "Shape Destructor";
	}

	void display_shape(){
		for (int i = 0; i < corners.size(); i++)
			cout << "\nPoint " << i << ": (" << corners[i].x << ", " << corners[i].y << ")";
	}
	
	virtual void area()=0;
	virtual void perimeter()=0;
};

class triangle : public shape {
public:
	float areaOfTraingle;
	float perimeterOfTriangle;
	triangle(Point p1, Point p2, Point p3)
	{
		corners.push_back(p1);
		corners.push_back(p2);
		corners.push_back(p3);
		areaOfTraingle = 0.0f;
		perimeterOfTriangle = 0.0f;
	}

	triangle(const triangle &t)
	{
		for (int i = 0; i < corners.size(); i++)
			corners[i] = t.corners[i];
		areaOfTraingle = t.areaOfTraingle;
		perimeterOfTriangle = t.perimeterOfTriangle;
	}

	void display()
	{
		display_shape();
		cout << "\nArea of Triangle = " << areaOfTraingle;
		cout << "\nPerimeter of Triangle = " << perimeterOfTriangle;
	}
	void area()
	{

		areaOfTraingle = ((corners[0].x*(corners[1].y - corners[2].y)) + (corners[1].x*(corners[2].y - corners[0].y)) + (corners[2].x*(corners[0].y - corners[1].y))) / 2;
		areaOfTraingle = (areaOfTraingle < 0) ? -(areaOfTraingle) : areaOfTraingle;
	}

	float lengthOfSide(float x1, float y1, float x2, float y2)
	{
		return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
	}

	void perimeter()
	{
		float side1, side2, side3;	
		side1 = lengthOfSide(corners[0].x, corners[0].y, corners[1].x, corners[1].y);
		side2 = lengthOfSide(corners[1].x, corners[1].y, corners[2].x, corners[2].y);
		side3 = lengthOfSide(corners[2].x, corners[2].y, corners[0].x, corners[0].y);
		perimeterOfTriangle = side1 + side2 + side3;
	}
};

class rectangle : public shape {
public:
	float length, width, diagonal;
	float areaOfRectangle;
	float perimeterOfRectangle;
	bool isRectangle;
	rectangle() {
		cout << "Rectangle default constructor";
	}

	rectangle(const rectangle &t)
	{
		for (int i = 0; i < corners.size(); i++)
			corners[i] = t.corners[i];
		length = t.length;
		width = t.width;
		diagonal = t.diagonal;
		isRectangle = t.isRectangle;
		areaOfRectangle = t.areaOfRectangle;
		perimeterOfRectangle = t.perimeterOfRectangle;
	}
	rectangle(Point p1, Point p2, Point p3, Point p4)
	{
		corners.push_back(p1);
		corners.push_back(p2);
		corners.push_back(p3);
		corners.push_back(p4);
		length = 0.0f;
		width = 0.0f;
		diagonal = 0.0f;
		isRectangle = false;
		areaOfRectangle = 0.0f;
		perimeterOfRectangle = 0.0f;
	}

	rectangle(Point p1, Point p2)
	{
		corners.push_back(p1);
		corners.push_back(p2);
		corners.push_back(p1);
		corners.push_back(p2);
		length = 0.0f;
		width = 0.0f;
		diagonal = 0.0f;
		isRectangle = false;
		areaOfRectangle = 0.0f;
		perimeterOfRectangle = 0.0f;
	}

	void display()
	{
		display_shape();
		if (isRectangle)
		{
			cout << "\nArea of Rectangle = " << areaOfRectangle;
			cout << "\nPerimeter of Rectangle = " << perimeterOfRectangle;
		}
	}
	
	bool checkIfRectangle()
	{
		float pythagorasLHS = roundf(diagonal * 100) / 100;
		float pythagorasRHS = roundf((sqrt(pow(length, 2) + pow(width, 2))) * 100) / 100;
		// use pythagoras theorem to verify it is a rectangle or not

		if (ceil(pythagorasLHS) == ceil(pythagorasRHS))
		{
			return true;
		}
		return false;
	}

	int findDiagonal(float sides[2])
	{
		int position = 0;
		float max = 0.0f;
		max = (sides[0] > sides[1]) ? sides[0] : sides[1];
		position = (sides[0] > sides[1]) ? 0 : 1;
		diagonal = ((max > sides[2]) ? max: sides[2]);
		position = ((max > sides[2]) ? position : 2);
		return position;

	}
	void getSidesAndDiagonalLength()
	{
		float side[3];
		side[0] = lengthOfSide(corners[0].x, corners[0].y, corners[1].x, corners[1].y);
		side[1] = lengthOfSide(corners[0].x, corners[0].y, corners[2].x, corners[2].y);
		side[2] = lengthOfSide(corners[0].x, corners[0].y, corners[3].x, corners[3].y);

		int diagonalPosition = findDiagonal(side);
		bool setLengthFirst = false;
		for (int i = 0; i < 3; i++)
		{
			if (i == diagonalPosition)
			{
				diagonal = side[i];
			}
			else if (setLengthFirst)
			{
				width = side[i];
			}
			else
			{
				length = side[i];
				setLengthFirst = true;
			}
		}
		isRectangle = checkIfRectangle();
	}
	void area()
	{
		getSidesAndDiagonalLength();
		if (isRectangle)
		{
			areaOfRectangle = (length * width);
		}
		else
		{
			cout << "\nGiven coordinates doesn't form rectangle";
		}	
	}

	float lengthOfSide(float x1, float y1, float x2, float y2)
	{
		return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
	}

	void perimeter()
	{
		getSidesAndDiagonalLength();
		if (isRectangle)
		{
			perimeterOfRectangle = 2 * (length + width);
		}
		else
		{
			cout << "\nGiven coordinates doesn't form rectangle";
		}
	}
};
class square : public rectangle {
public:
	float areaOfSquare;
	float perimeterOfSqaure;
	square(Point p1, Point p2, Point p3, Point p4)
	{
		corners.push_back(p1);
		corners.push_back(p2);
		corners.push_back(p3);
		corners.push_back(p4);
		areaOfSquare = 0.0f;
		perimeterOfSqaure = 0.0f;
	}
	square(Point p1, Point p2)
	{
		corners.push_back(p1);
		corners.push_back(p2);
		corners.push_back(p1);
		corners.push_back(p2);
		areaOfSquare = 0.0f;
		perimeterOfSqaure = 0.0f;
	}

	square(const square &t)
	{
		for (int i = 0; i < corners.size(); i++)
			corners[i] = t.corners[i];
		length = t.length;
		width = t.width;
		diagonal = t.diagonal;
		isRectangle = t.isRectangle;
		areaOfSquare = t.areaOfSquare;
		perimeterOfSqaure = t.perimeterOfSqaure;
	}

	void display()
	{
		display_shape();
		if (isRectangle && length ==width)
		{
			cout << "\nArea of sqaure = " << areaOfSquare;
			cout << "\nPerimeter of square = " << perimeterOfSqaure;
		}
	}

	void area()
	{
		getSidesAndDiagonalLength();
		if (isRectangle && (length==width))
		{
			areaOfSquare = (length * width);
		}
		else
		{
			cout << "\nGiven coordinates doesn't form sqaure";
		}
	}

	void perimeter()
	{
		getSidesAndDiagonalLength();
		if (isRectangle && (length == width))
		{
			perimeterOfSqaure = 2 * (length + width);
		}
		else
		{
			cout << "\nGiven coordinates doesn't form square";
		}
	}
};
int main() {
	Point p1(10, 10), p2(20, 20), p3(10, 20), p4(20,10), p5(3,10), p6(5,10);

	Point pt1(16, 34), pt2(47, 16), pt3(33, -9), pt4(2, 8);
	
	triangle t1(pt1, pt2, pt3);
	t1.area();
	t1.perimeter();
	t1.display();
	
	rectangle r1(p1, p2, p3, p4);
	rectangle r2(pt1, pt2, pt3, pt4);
	r2.area();
	r2.perimeter();
	r2.display();
	square s1(pt1, pt2, pt3, pt4);
	s1.area();
	s1.perimeter();
	s1.display();
	getchar();
	return 0;
}

	