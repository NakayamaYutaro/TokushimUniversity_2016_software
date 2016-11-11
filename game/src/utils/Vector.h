#ifndef VECTOR_H

#define VECTOR_H

template<typename T>
class Vector{
	private:
		T x, y;
	public:
		Vector(x_val, y_val) : x(x_val), y(y_val) {}
		Vector<T> operator *(T coefficient) { return Vector<T>(x * coefficient, y * coefficient); }
		Vector<T> operator +(Vector<T> vec2) { return Vector<T>(x + vec2.getX, y + vec2.y); }
		Vector getX() { return x; }
		Vector getY() { return y; }
		T getMagnitude{ return 
}

#endif
