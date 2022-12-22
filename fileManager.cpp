#include "fileManager.h"

bool loadSrc(){
    bool success = true;
    std::ifstream dataIn;
    dataIn.open("img/PictureList.txt", std::ios::in);
    std::string path;
    int n;
    dataIn >> path;
    const char * mPath = path.c_str();
    loadMusic(mPath);
    for(int i = 0; i < 5; i++){
        dataIn >> path >> n;
        if(!loadMedia(path, (Picture)(n)))
            success = false;
    }
    while(dataIn >> path >> n){
        if(!loadMedia(path, (Picture)(n)))
            success = false;
    }
    char arr[5][7] = {};
    dataIn.close();

    dataIn.open("img/gameData.dat", std::ios::in);
    char c;
    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 7; j++){
            dataIn.get(c);
            arr[i][j] = c;
        }
        dataIn.ignore(20, '\n');
    }
    dataIn.close();

    bool sd;
    dataIn.open("img/Progress.dat", std::ios::in);
    for(int i = 0; i < 5; i++){
        dataIn >> n;
        SetProgress(i, n);
    }
    dataIn >> n;
    setSoundLoud(n);
    dataIn >> sd;
    setSoundOn(sd);

    dataIn.close();
    return success;

}

void saveProgress(int arr[]){
    bool success = true;
    std::ofstream dataOut;
    dataOut.open("img/Progress.dat", std::ios::out);
    for(int i = 0; i < 5; i++)
        dataOut << arr[i] << " ";
    dataOut << getSound() << " " << IsSound();

    dataOut.close();
}

bool loadFonts(){
    bool success = true;
    if(!loadFont("img/Teko-Regular.ttf", 54))
        success = false;
    return success;
}
