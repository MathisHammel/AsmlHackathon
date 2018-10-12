#include "shapes.hpp"
#include <cmath>
#include <stdio.h>

namespace Shapes {
    char** Shape::get(Shapes::Type shape_type, int n, int width = 1) { 
        int SIZE = 8 * n;
        char **mat = new char*[32];
        for(int i=0;i<32;i++) {
            mat[i] = new char[32];
            for(int j=0;j<32;j++)
                mat[i][j] = 0;
        }

        int level = SIZE - 1;
        int border = 0;
        int mid = SIZE / 2;

        switch (shape_type) {
            case SQUARE:
                for(int i=0;i<SIZE;i++) 
                    for(int j=0;j<SIZE;j++) {
                        mat[i][j] = 1;
                        mat[i][j] &= ((width <= i) && i < (SIZE - width));
                        mat[i][j] &= ((width <= j) && j < (SIZE - width));
                        mat[i][j] ^= 1;
                    }
            break;

            case TRIANGLE:  
                while (level > 0 && 2*border < SIZE) {
                    for(int j=0;j<SIZE;j++) {
                        mat[level][j] = mat[level - 1][j] = (border <= j && j < SIZE - border);
                    }
                    border++;
                    level -= 2;
                }

            break;

            case DIAMOND:
                level = 0;
                while (level < SIZE) {
                    for(int j=0;j<SIZE;j++) {
                        if (level < mid) {
                            if (std::abs( mid - j ) < level + 1) {
                                mat[level][j] = 1;
                            }
                        } else {
                            if (std::abs( mid - j ) < SIZE - level + 1) {
                                mat[level][j] = 1;
                            }
                        }
                    }
                    level++;
                }

            break;

            case ROUND:
                for ( int l = 0; l < width; l++) {
                    /*
                    for (i = mid - 1, j = l; i >= l; i--, j++) 
                        mat[i][j] = 1;
                    for (i++, j = mid; i < mid; i++, j++)
                        mat[i][j] = 1;
                    for (j = SIZE - 1 - l; i < SIZE - l; i++, j--)
                        mat[i][j] = 1;
                    for (i--, j = mid - 1; i >= mid; i--, j--)
                        mat[i][j] = 1;*/
                    
                }
                float i;
                for(i = 0.0; i<=6.29; i+=0.05) {
                        int x=16 + 16*cos(i);
                        int y=16 + 16*sin(i);
                        if(x>=0 && x<32 && y>=0 && y<32){
                            mat[x][y] = 1;
                        }
                }

            break;

        }
        return mat;
    }
}
