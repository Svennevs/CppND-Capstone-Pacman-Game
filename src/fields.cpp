#include "fields.h"
#include <iostream>

Fields::Fields(std::string filename_map){
  foodLeft = 0;
  ftypes = ReadMapFile(filename_map);
  grid_height = ftypes.size(); 
  grid_width = ftypes[0].size();
}

bool Fields::eatFood(int y, int x){
  //check if the field has food. if so, set it to empty and reduce foodLeft  
  if (hasFood(y,x)){
    ftypes[y][x]=FieldType::PathEmpty;
    foodLeft--;
    return true;
  }
  return false;
}

bool Fields::eatPowerUp(int y, int x){
  //check if the field has a powerUp and set it to empty.
  if (hasPowerUp(y,x)){
    ftypes[y][x]=FieldType::PathEmpty;
    return true;
  }
  return false;
}


std::vector<std::vector<Fields::FieldType>> Fields::ReadMapFile(std::string path) {
  // reads the map file. Code is copied from 2. Foundations, lesson 3 (A* search)
  std::ifstream myfile (path);
  
  std::vector<std::vector<FieldType>> ftypes{};
  if (myfile) {
    std::string line;
    while (getline(myfile, line)) {
      std::vector<FieldType> row = ParseLine(line);
      ftypes.push_back(row);
    }
  }
  return ftypes;
}

std::vector<Fields::FieldType> Fields::ParseLine(std::string line){
  std::istringstream sline(line);
  int n;
  char c;
  std::vector<FieldType> row;
  while (sline >> n >> c && c == ',') {
    if (n == 0) {
      row.push_back(FieldType::Wall);
    } else if (n == 1){
      row.push_back(FieldType::PathEmpty);
    } else if (n == 2){
      row.push_back(FieldType::PathFood);
      foodLeft++;
    } else {
      row.push_back(FieldType::PathPowerUp);
    }
  }
  return row;
}






