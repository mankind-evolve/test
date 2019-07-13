//
// Created by Admin on 2019/7/13.
//

#ifndef OPENGLES_STU_MATRIXUTIL_H
#define OPENGLES_STU_MATRIXUTIL_H



//初始化单位矩阵
//1,0,0,0,
//0,1,0,0,
//0,0,1,0,
//0,0,0,1,
static void initMatrix(float* matrix){
   for(int i = 0 ; i < 16 ; i++){
       if(i % 5 == 0 ){
           matrix[i] = 1;
       }else{
           matrix[i] = 0;
       }
   }
}



#endif //OPENGLES_STU_MATRIXUTIL_H
