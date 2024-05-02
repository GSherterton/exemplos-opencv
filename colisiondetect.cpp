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
//Mat mat1 = orange.clone();


int main(){
    //usando como base o inicio.cpp com o video.mp4 como um background
    Mat background; //criando uma matriz para representar o background

    VideoCapture capture; //objeto responsável pela captura do video

    //if(!capture.open(0)){ //se for utilizar a camera
    if(!capture.open("video.mp4")){ //se for utilizar um video
        cout << "Capture from camera #0 didn't work" << endl;
        return 1;
    }

    cout << "Ativei a camera\n"; //debug  

    Rect fixo(Point(50, 40), Size(20, 100));
    Rect rect1(Point(0, 0), Size(20, 100));

    while(1){
        capture.read(background); //passando o que for lido na camera para o background 

        resize(background, background, Size(), 1/2.0, 1/2.0, INTER_LINEAR_EXACT); //divindo a imagem da camera por 2 em cada dimensão

        rectangle(background, fixo, Scalar(0, 255, 255), 3);    //blue green red
        rectangle(background, rect1, Scalar(255, 0, 255), 3);   //blue green red

        char c = (char)waitKey(100);
        if(c == 27 || c == 'q'){ //apertar q para sair do programa (quit)
            break;
        }

        cout << background.cols << " x " << background.rows << endl; //diz o tamanho da matriz do background

        imshow("result", background); //abre uma aba exibindo uma matriz, o primeiro parametro é o nome da aba
    }

    return 0;
}