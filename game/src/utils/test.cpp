#include "Vector.h"
#include "LinkedList.h"

int main() {
	LinkedList<Vector<double>> list = LinkedList<Vector<double>>();
	list.add(Vector<double>(1, 2));
	list.add(Vector<double>(3, 4));
	list.add(Vector<double>(5, 6));
	list.add(Vector<double>(7, 8));
	list.get(3).display();
	return 0;
}
