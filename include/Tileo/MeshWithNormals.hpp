#pragma once


#include <vector>


namespace Tileo
{
   class MeshWithNormals
   {
   private:
      int num_columns;
      int num_rows;
      float tile_width;
      float tile_height;
      std::vector<int> tile_ids;
      std::vector<int> normal_tile_ids;
      bool initialized;

   public:
      MeshWithNormals(int num_columns=0, int num_rows=0, float tile_width=1.0f, float tile_height=1.0f);
      ~MeshWithNormals();

      void initialize();
      void resize(int num_columns=1, int num_rows=1);
   };
}



