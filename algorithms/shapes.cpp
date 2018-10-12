#include "shapes.hpp"
#include <math.h>

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
                            if (abs( mid - j ) < level + 1) {
                                mat[level][j] = 1;
                            }
                        } else {
                            if (abs( mid - j ) < SIZE - level + 1) {
                                mat[level][j] = 1;
                            }
                        }
                    }
                    level++;
                }

            break;
        }
        return mat;
    }
}
