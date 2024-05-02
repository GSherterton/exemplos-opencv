#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

//funcao que desenha um retangulo com transparencia, os parametros sao o local onde se deseja desenhar o retangulo,
//a cor do retangulo, o nivel de transparencia, sendo de 0 a 1, e quanto maior menos transparente, e o retangulo em si
void drawTransRect(Mat frame, Scalar color, double alpha, Rect region){
    Mat roi = frame(region);
    Mat rectImg(roi.size(), CV_8UC3, color); 
    addWeighted(rectImg, alpha, roi, 1.0 - alpha , 0, roi); 
}

int main(){
    //exemplo usando o video.mp4 como um background
    //colocando um retangulo com transparencia na tela
    Mat background; //criando uma matriz para representar o background

    VideoCapture capture; //objeto responsável pela captura do video

    //if(!capture.open(0)){ //se for utilizar a camera
    if(!capture.open("video.mp4")){ //se for utilizar um video
        cout << "Capture from camera #0 didn't work" << endl;
        return 1;
    }

    cout << "Ativei a camera\n"; //debug  

    while(1){
        capture.read(background); //passando o que for lido na camera para o background 

        resize(background, background, Size(), 1/2.0, 1/2.0, INTER_LINEAR_EXACT); //divindo a imagem da camera por 2 em cada dimensão

        double alpha = 0.3;
        drawTransRect(background, Scalar(255,0,0), alpha, Rect(Point(400, 200), Size(150, 150)));
        alpha = 0.8;
        drawTransRect(background, Scalar(0,255,0), alpha, Rect(Point(600, 200), Size(150, 150)));

        char c = (char)waitKey(100);
        if(c == 27 || c == 'q'){ //apertar q para sair do programa (quit)
            break;
        }

        cout << background.cols << " x " << background.rows << endl; //diz o tamanho da matriz do background

        imshow("result", background); //abre uma aba exibindo uma matriz, o primeiro parametro é o nome da aba
    }

    return 0;
}