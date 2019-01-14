/* buffer.h */
#ifndef BUFFER_H_INCLUDED
#define BUFFER_H_INCLUDED

#define BUFFER_SIZE 20

#include <string>

typedef int buffer_item;

int Initialize();
int Deinitialize();
int InsertItem(buffer_item item);
int RemoveItem(buffer_item *item);

#endif