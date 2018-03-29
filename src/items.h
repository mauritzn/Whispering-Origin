#ifndef ITEMS_H
#define ITEMS_H

#include <string>
#include <map>
using namespace std;


typedef map<int, string> ITEM;

extern const ITEM trees;
extern const ITEM ores;
extern const ITEM fish;

bool item_exists(int, const ITEM&); // check if an item ID exists
string get_item_name(int, const ITEM&); // get the items name, using it's item ID

#endif