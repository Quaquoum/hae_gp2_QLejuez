#include <cstdlib>
#include <cstring>

struct IntList
{
	int value = 0.0;
	IntList* next = nullptr;

};

static IntList* append(IntList* l, int value);
static IntList* remove(IntList* l, int value);
static IntList* appendFirst(IntList* l, int value);
static IntList* appendLast(IntList* l, int value);
static int length(IntList* l);