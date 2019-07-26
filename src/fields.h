#ifndef FIELDS_H
#define FIELDS_H

#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>


class Fields {
  
  public:
    enum class FieldType { Wall, PathEmpty , PathFood , PathPowerUp};

    Fields(std::string filename_map);

    int getGrid_width() const {return grid_width;}
    int getGrid_height() const {return grid_height;}
    int getFoodLeft() const {return foodLeft;}
    std::vector<std::vector<FieldType>> getTypes() const{return ftypes;}
   
    bool isWall(int y, int x) const {return ftypes[y][x]==FieldType::Wall;}

    bool hasFood(int y, int x) const {return ftypes[y][x]==FieldType::PathFood;}
    bool hasPowerUp(int y, int x) const {return ftypes[y][x]==FieldType::PathPowerUp;}
    bool eatFood(int y, int x);
    bool eatPowerUp(int y, int x);

  private:
    std::vector<std::vector<FieldType>> ftypes;  //this is a matrix with fieldtype elements and represents the map
    int foodLeft;
    int grid_width;
    int grid_height; 

    std::vector<std::vector<FieldType>> ReadMapFile(std::string path);
    std::vector<FieldType> ParseLine(std::string line); 

};

#endif


