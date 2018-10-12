
#include "Facilities_MeshNetwork.hpp"

class MeshControl {

public:
    MeshControl(Facilities::MeshNetwork& mesh);
    void transferImage(int nodeId, char pixels[8][32]);
private: 
    Facilities::MeshNetwork& _mesh;
};