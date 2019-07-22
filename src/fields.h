#ifndef FIELDS_H
#define FIELDS_H

#include <vector>

class Fields {
  
  public:
    enum class FieldType { Wall, PathEmpty , PathFood };


    Fields(int grid_width, int grid_height){

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
      std::vector<int> xVertLines{3,6,11,18};
      for(int x : xVertLines){
        for(int y = 0; y < grid_height ;y++){
          xCoordinates.push_back(x);
          yCoordinates.push_back(y);
        }
      }
      //horizontal line paths
      std::vector<int> yHorLines{1,4,8,12,14,19};
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
    
    std::vector<std::vector<FieldType>> getTypes(){
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

    void eatFood(int x, int y){
      ftypes[x][y]=FieldType::PathEmpty;
      foodLeft--;
    }


  private:
    std::vector<std::vector<FieldType>> ftypes; 
    int foodLeft;
};



#endif


