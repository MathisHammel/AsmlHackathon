#ifndef __MeshCtl__
#define __MeshCtl__

#include "Facilities_MeshNetwork.hpp"
#include <LEDMatrixDriver.hpp>

class MeshControl {

public:
    MeshControl(Facilities::MeshNetwork& mesh);
    void setPixel(char x, char y, char intensity);
    void clear();
    void recvScreen(Facilities::MeshNetwork::NodeId nodeId, String& msg);
    void morphImage(char image1[32][32], char image2[32][32]);
    void displayImage(char image[32][32]);
    void localSetPixel(char x, char y, char intensity);
    void localDisplayImage(char image[8][32]);
    void transferPixel(int nodeId, char x, char y, char intensity);
    void transferImage(int nodeId, char pixels[8][32]);
private: 
    Facilities::MeshNetwork& _mesh;
    LEDMatrixDriver m_lmd;
};

#endif // __MeshCtl__
