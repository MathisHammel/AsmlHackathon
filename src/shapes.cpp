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

            case SMALL_OPAQUE:
            case LARGE_OPAQUE:
            case ROUND:
                float i;
                int r = 16;
                if (shape_type == SMALL_OPAQUE)
                    r = 5;

                int offsideX = (SIZE - 2*r) / 2;
                int offsideY = (SIZE - 2*r) / 2;
                for(i = 0.0; i<=6.29; i+=0.05) {
                        int x=r + r*cos(i);
                        int y=r + r*sin(i);
                        if(x>=0 && x<2*r && y>=0 && y<2*r){
                            mat[x + offsideX][y + offsideY] = 1;
                        }
                }

                if (shape_type == LARGE_OPAQUE || shape_type == SMALL_OPAQUE) {
                    for(int i=0;i<SIZE;i++) {
                        int last = SIZE - 1, start = 0;
                        while (start < SIZE && mat[i][start] != 1) start++;
                        while (last >=0 && mat[i][last] != 1) last--;

                        for(int j=0;j<SIZE;j++) {
                            if (start <= j && j <= last) 
                                mat[i][j] = 1;
                        }
                    }
                }
            break;
        }
        return mat;
    }
}
