#include "items.h"
#include <string>
#include <map>
using namespace std;

const ITEM trees {
  { 6381181, "Oak" }
};

const ITEM ores {
  { 6381181, "Copper" }
};

const ITEM fish {
  { 6381181, "Salmon" }
};



bool item_exists(int id, const ITEM& type) {
  auto search = type.find(id);
  
  if(search != type.end()) {
    return true;
  } else {
    return false;
  }
}


string get_item_name(int id, const ITEM& type) {
  if(item_exists(id, type)) {
    return type.at(id);
  } else {
    return "";
  }
}