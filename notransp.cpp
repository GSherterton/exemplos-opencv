#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

void drawNoTransparency(Mat frame, Mat img, int xPos, int yPos){ //função para desenhar algo sem transparência, como parametros temos a matriz(frame) na qual iremos desenhar a imagem(img) na posição xPos, yPos de acordo com a orientação da matriz, na qual se aumenta da esquerda para direita e de cima para baixo
    img.copyTo(frame.rowRange(yPos, yPos + img.rows).colRange(xPos, xPos + img.cols));
}

int main(){
    //usando como base o inicio vamos ver como se coloca uma imagem sem transparencia no background
    //definindo a imagem que iremos desenhar
    Mat mustang = imread("imagens/mustang.jpg", IMREAD_UNCHANGED);

    //como essa imagem é muito grande iremos dar um rezise para caber no background
    resize(mustang, mustang, Size(), 1/8.0, 1/8.0, INTER_LINEAR_EXACT);

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
    
        //desenhando uma imagem sem transparencia no background
        drawNoTransparency(background, mustang, 10, 150);

        char c = (char)waitKey(100);
        if(c == 27 || c == 'q'){ //apertar q para sair do programa (quit)
            break;
        }

        cout << background.cols << " x " << background.rows << endl; //diz o tamanho da matriz do background

        imshow("result", background); //abre uma aba exibindo uma matriz, o primeiro parametro é o nome da aba
    }


    return 0;
}