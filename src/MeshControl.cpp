#include "MeshControl.hpp"

#include "Debug.hpp"
#include "Constants.hpp"


MeshControl::MeshControl(Facilities::MeshNetwork& mesh): _mesh(mesh) {
    
}

void MeshControl::transferImage(int nodeId, char pixels[8][32])  {
    String pixelStr = "";

    //check if this is a master
    if(MASTER) {
        String str;
        DynamicJsonBuffer jsonBuffer;
        JsonObject& msg = jsonBuffer.createObject();
        msg["type"] = MSG_TYPE_IMG;
        msg["nodeId"] = nodeId; 

        for(int i=0; i< 7; i++) {
            for(int j=0; j < 31; j++) {
                if(0 == pixels[i][j]) {
                    pixelStr.concat('0');
                }
                else if(0xff == pixels[i][j]) {
                    pixelStr.concat('2');
                }
                else {
                    pixelStr.concat('1');
                }
            }
        }
        msg["pixels"] = pixelStr;
        msg.printTo(str);
        _mesh.sendBroadcast(str);
    }
}