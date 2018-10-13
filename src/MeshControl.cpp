#include "MeshControl.hpp"

#include "Debug.hpp"
#include "Constants.hpp"

#include <LEDMatrixDriver.hpp>


MeshControl::MeshControl(Facilities::MeshNetwork& mesh): _mesh(mesh), m_lmd(4, SEGMENT_PIN) {
    mesh.onReceive(std::bind(&MeshControl::recvScreen, this, std::placeholders::_1, std::placeholders::_2));
    m_lmd.clear();
    m_lmd.display();
    m_lmd.setEnabled(true);
    m_lmd.setIntensity(5);
}

void MeshControl::recvScreen(Facilities::MeshNetwork::NodeId nodeId, String& msg) {
    MY_DEBUG_PRINTLN("Node received new frame");
    char image[8][32] = {0};
    int x,y;
    for(x=8*NODE_ID-8; x<8*NODE_ID; x++) {
        for(y=0; y<32; y++)
        {
            image[x%8][y] = msg[x+y*32] - '0';
        }
    }
    localDisplayImage(image);
}

void MeshControl::setPixel(char x, char y, char intensity) {
    if (x < 8) {
        localSetPixel(x, y, intensity);
    } else if (x < 16) {
        transferPixel(2, x-8, y, intensity);
    } else if (x < 24) {
        transferPixel(3, x-16, y, intensity);
    } else if (x < 32) {
        transferPixel(4, x-24, y, intensity);
    }
}

void MeshControl::clear() {
    char blank[32][32] = {0};
    displayImage(blank);
}

void MeshControl::displayImage(char image[32][32]) {
    char image1[8][32] = {0};
    char image2[8][32] = {0};
    char image3[8][32] = {0};
    char image4[8][32] = {0};
    int x, y;
    for(x = 0 ; x < 8 ; x++) {
        for(y = 0; y < 32; y++) {
            image1[x][y] = image[x][y];
            image2[x][y] = image[x+8][y];
            image3[x][y] = image[x+16][y];
            image4[x][y] = image[x+24][y];
        }
    }
    localDisplayImage(image1);
    transferImage(2, image2);
    transferImage(3, image3);
    transferImage(4, image4);
}

void MeshControl::morphImage(char image1[32][32], char image2[32][32]){
    // TODO
}

void MeshControl::localSetPixel(char x, char y, char intensity) {
    MY_DEBUG_PRINTF("localSetPixel(%d, %d)\n", x, y);
    m_lmd.setPixel(y ^ 24, 7 - x, intensity > 0);
    m_lmd.display();
}

void MeshControl::localDisplayImage(char image[8][32]) {
    int x, y;

    for(x = 0 ; x < 8 ; x++) {
        for(y = 0; y < 32; y++) {
            m_lmd.setPixel(y ^ 24, 7 - x, image[x][y] > 0);
        }
    }
    m_lmd.display();
}

void MeshControl::transferPixel(int nodeId, char x, char y, char intensity) {
    m_lmd.setPixel(y ^ 24, 7 - x, intensity > 0);
    m_lmd.display();
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