#ifndef __Shapes_Shapes__
#define __Shapes_Shapes__

namespace Shapes {

    enum Type {
        SQUARE,
        TRIANGLE,
        DIAMOND,
        ROUND,
        LARGE_OPAQUE,
        SMALL_OPAQUE
    };

    class Shape {
    public:
        char** get(Type shape, int n, int width);
    };

}

#endif // __Shapes_Shapes__
