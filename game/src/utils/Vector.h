#ifndef VECTOR_H

#include<math.h>
#include<iostream>

#define VECTOR_H

template<typename T>
class Vector{
	private:
		T x, y;
	public:
		Vector(T x_val = 0, T y_val = 0) : x(x_val), y(y_val) {}
		T getX() { return x; }
		T getY() { return y; }
		operator const Vector<int>() const { return Vector<int>( (int)x, (int)y ); }
		operator const Vector<float>() const { return Vector<float>( (float)x, (float)y ); }
		operator const Vector<double>() const { return Vector<double>( (double)x, (double)y ); }
		Vector<T> operator *(double coefficient) { return Vector<T>( (T)(x * coefficient), (T)(y * coefficient) ); }
		Vector<T> operator +(Vector<T> vec2) { return Vector<T>(x + vec2.getX(), y + vec2.getY()); }
		Vector<T> operator -(Vector<T> vec2) { return Vector<T>(x - vec2.getX(), y - vec2.getY()); }
		Vector<T> operator -(double num) { return Vector<T>(x - num, y - num); }
		Vector<T> operator /(double divide_by) { return Vector<T>((T)(x/divide_by), (T)(y/divide_by)); }
		Vector<T> operator +=(Vector<T> vec2) {  x += vec2.getX(); y += vec2.getY(); }
		Vector<T> operator -=(Vector<T> vec2) {  x -= vec2.getX(); y -= vec2.getY(); }
		Vector<T> operator *=(double scale) {  x = (T)(scale * x); x = (T)(scale * y); }
		Vector<T> operator /=(double divided_by) {  x = (T)(x/divided_by); y = (T)(y/divided_by); }
		double getMagnitude(){ return sqrt((double)x*x + y*y); }
		double getInnerProduct(Vector<T> vec2){ return (double)(x*vec2.getX() + y*vec2.getY()); }
		void display() { std::cout << "(" << x << ", " << y << ")" << std::endl; }
};

#endif
