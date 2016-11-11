#ifndef VECTOR_H

#include<math.h>
#include<iostream>

#define VECTOR_H

template<typename T>
class Vector{
	private:
		T x, y;
	public:
		Vector(T x_val, T y_val) : x(x_val), y(y_val) {}
		Vector<T> operator *(T coefficient) { return Vector<T>(x * coefficient, y * coefficient); }
		Vector<T> operator +(Vector<T> vec2) { return Vector<T>(x + vec2.getX, y + vec2.y); }
		Vector getX() { return x; }
		Vector getY() { return y; }
		T getMagnitude(){ return (T)sqrt(x*x + y*y); }
		void display() { std::cout << "(" << x << ", " << y << ")" << std::endl; }
};

#endif
