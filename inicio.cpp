#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

//so uma informação extra
//quando se usa uma matriz igual a outra
//exemplo:
//Mat orange = imread("imagens/orange.png", IMREAD_UNCHANGED);
//Mat mat1 = orange;

//se eu mexer em mat1 eu irei estar alterando orange

//para se fazer uma atribuição do jeito que esperariamos é necessário fazer 
//Mat orange = imread("imagens/orange.png", IMREAD_UNCHANGED);
//Mat mat1 = orange.clone()


int main(){
    //exemplo usando o video.mp4 como um background
    Mat background; //criando uma matriz para representar o background

    VideoCapture capture; //objeto responsável pela captura do video

    bool isToResize = 0;
    bool isToFlip = 0;

    //if(!capture.open(0)){ //se for utilizar a camera
    if(!capture.open("video.mp4")){ //se for utilizar um video
        cout << "Capture from camera #0 didn't work" << endl;
        return 1;
    }

    cout << "Ativei a camera\n"; //debug  

    while(1){
        capture.read(background); //passando o que for lido na camera para o background 

        if(isToResize)
            resize(background, background, Size(), 0.5, 0.5, INTER_LINEAR_EXACT);
        
        if(isToFlip)
            flip(background, background, 1);


        char c = (char)waitKey(100);
        if(c == 27 || c == 'q'){ //apertar q para sair do programa (quit)
            break;
        }else if(c == 'r'){ //apertar r para ativar/desativar o resize
            isToResize = !isToResize;
        }else if(c == 'f'){ //apertar f para ativar/desativar o flip
            isToFlip = !isToFlip;
        }

        cout << background.cols << " x " << background.rows << endl; //diz o tamanho da matriz do background

        imshow("result", background); //abre uma aba exibindo uma matriz, o primeiro parametro é o nome da aba
    }

    return 0;
}