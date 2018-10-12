#ifndef __Shapes_Shapes__
#define __Shapes_Shapes__

namespace Shapes {

    enum Type {
        SQUARE,
        TRIANGLE,
        DIAMOND
    };

    class Shape {
    public:
        char** get(Type shape, int SIZE, int width);
    };

}

#endif // __Shapes_Shapes__
