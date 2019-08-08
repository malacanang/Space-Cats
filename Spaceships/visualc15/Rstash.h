#ifndef RSTASH_H 
#define RSTASH_H

#include <cassert>
#include "Rectangle.h" 
#include "../visualc15/Vector.h"

using namespace std;
class Rstash
{
	int size;
	int quantity;
	int next;
	unsigned char* storage;

public:
	Rstash();
	void initalize(int sz);
	void cleanup();
	int add(const ucm::Rectangle* element);
	void* fetch(int index);
	int count();
	void inflate(int increase);
	~Rstash();


};
Rstash::Rstash()
{
	initalize(sizeof(ucm::Rectangle*) + sizeof(Vec) * 2);

}

void Rstash::initalize(int sz) {
	size = sz;
	quantity = 0;
	storage = 0;
	next = 0;
}

void Rstash::cleanup() {
	if (storage != 0)
	{
		delete[]storage;
	}
}

int Rstash::add(const ucm::Rectangle* element) {
	if (next >= quantity)
		inflate(100);


	int startBytes = next * size;
	unsigned char* e = (unsigned char*)element;

	for (int i = 0; i < size; i++)
		storage[startBytes + i] = e[i];
	next++;

	return(next - 1);
}

void* Rstash::fetch(int index) {

	assert(0 <= index);

	if (index >= next)
		return 0;

	return &(storage[index * size]);
}

int Rstash::count() {
	return next;
}

void Rstash::inflate(int increase) {
	assert(increase > 0);

	int newQuantity = quantity + increase;
	int newBytes = newQuantity * size;
	int oldBytes = quantity * size;
	unsigned char* b = new unsigned char[newBytes];

	for (int i = 0; i < oldBytes; i++)
		b[i] = storage[i];

	delete[]storage;
	storage = b;
	quantity = newQuantity;
}

Rstash::~Rstash()
{
	if (storage != 0)
	{
		delete[]storage;
	}
}

#endif