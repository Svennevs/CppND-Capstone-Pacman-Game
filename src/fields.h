#ifndef FIELDS_H
#define FIELDS_H

#include <vector>

class Fields {
  
  public:
    enum class FieldType { Wall, PathEmpty , PathFood };


    Fields(std::string filename_map){
      
      grid_width = 20;
      grid_height = 20;

      foodLeft=0;
      std::vector<std::vector<FieldType>> temp(grid_width, std::vector<FieldType>(grid_height));
      ftypes = temp;
      //everything is wall
      for (int x = 0; x < grid_width; x++)
      {
         for (int y = 0; y < grid_height; y++)
         {
            ftypes[x][y] = FieldType::Wall;
         }
      }

      
      //draw paths (read from file in future) 
      std::vector<int> xCoordinates;//{0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19};
      std::vector<int> yCoordinates;//{10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10};
      
      //vertical line paths
      std::vector<int> xVertLines{ 10};
      for(int x : xVertLines){
        for(int y = 4; y < grid_height ;y++){
          xCoordinates.push_back(x);
          yCoordinates.push_back(y);
        }
      }
      //horizontal line paths
      std::vector<int> yHorLines{ 4, 8};
      for(int y : yHorLines){
        for(int x = 0; x < grid_width ;x++){
          xCoordinates.push_back(x);
          yCoordinates.push_back(y);
        }
      }


      for(int i=0;i<xCoordinates.size();i++){
        if(ftypes[xCoordinates[i]][yCoordinates[i]]==FieldType::Wall){ //avoid double assignments (foodLeft gets too high)
          ftypes[xCoordinates[i]][yCoordinates[i]]=FieldType::PathFood;
          foodLeft++;
        }
      }
      
      //SDL_Point wallpoint;

      //for(int i=0;i<xCoordinates.size();i++){ 
      //  wallpoint.x = xCoordinates[i];
      //  wallpoint.y = yCoordinates[i];
      //  walls.push_back(wallpoint);
      //}
      
    }
    //std::vector<SDL_Point> GetWalls(){
      //return walls;
      //}
    
    int getGrid_width() const {return grid_width;}
    int getGrid_height() const {return grid_height;}
    std::vector<std::vector<FieldType>> getTypes() const{
      return ftypes;
    }
    /*
    FieldType getType(int x, i nt y){
      return ftypes[x][y];
    } */
    bool isWall(int x, int y) const {
      return ftypes[x][y]==FieldType::Wall;
    }
    bool hasFood(int x, int y) const {
      return ftypes[x][y]==FieldType::PathFood;
    }

    int getFoodLeft() const {return foodLeft;}

    bool eatFood(int x, int y){
      if (hasFood(x,y)){
        ftypes[x][y]=FieldType::PathEmpty;
        foodLeft--;
        return true;
      }
      return false;
    }

      
  private:
    std::vector<std::vector<FieldType>> ftypes; 
    int foodLeft;
    int grid_width;
    int grid_height; 
};



#endif


