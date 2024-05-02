#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

void drawTransparency(Mat frame, Mat transp, int xPos, int yPos){ //função para desenhar algo com transparência, como parametros temos a matriz(frame) na qual iremos desenhar a imagem(transp) na posição xPos, yPos de acordo com a orientação da matriz, na qual se aumenta da esquerda para direita e de cima para baixo
    Mat mask;
    vector<Mat> layers;

    split(transp, layers); // seperate channels
    Mat rgb[3] = { layers[0],layers[1],layers[2] };
    mask = layers[3]; // png's alpha channel used as mask
    merge(rgb, 3, transp);  // put together the RGB channels, now transp insn't transparent 
    transp.copyTo(frame.rowRange(yPos, yPos + transp.rows).colRange(xPos, xPos + transp.cols), mask);
}

int main(){
    //usando como base o inicio vamos ver como se coloca uma imagem com transparencia no background
    //definindo a imagem que iremos desenhar
    Mat orange = imread("imagens/orange.png", IMREAD_UNCHANGED);

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
    
        //desenhando uma imagem com transparencia no background
        drawTransparency(background, orange, 10, 150); //desenhando a laranja numa posição qualquer

        char c = (char)waitKey(100);
        if(c == 27 || c == 'q'){ //apertar q para sair do programa (quit)
            break;
        }

        cout << background.cols << " x " << background.rows << endl; //diz o tamanho da matriz do background

        imshow("result", background); //abre uma aba exibindo uma matriz, o primeiro parametro é o nome da aba
    }


    return 0;
}