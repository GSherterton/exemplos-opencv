#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

void drawNoTransparency(Mat frame, Mat img, int xPos, int yPos){ //função para desenhar algo sem transparência, como parametros temos a matriz(frame) na qual iremos desenhar a imagem(img) na posição xPos, yPos de acordo com a orientação da matriz, na qual se aumenta da esquerda para direita e de cima para baixo
    img.copyTo(frame.rowRange(yPos, yPos + img.rows).colRange(xPos, xPos + img.cols));
}

void circularDraw(Mat background, Mat frame, int velocidade, int& posicao){ //tem que comentar essa funçao
    if(posicao > frame.cols)
        cout << "frame.cols: "<< frame.cols << "\n";
        posicao = 0;
    
    cout << "posicao: " << posicao << endl;

    Rect crop1(posicao, 0, background.cols - posicao, background.rows);
    Mat bg1 = background(crop1);
    //Rect crop2(0, 0, posicao, background.rows);
    //Mat bg2 = background(crop2);

    if (bg1.cols > 0)
        cout << bg1.rows << " x " << bg1.cols << endl;
        bg1.copyTo(frame.rowRange(0, bg1.rows).colRange(0, bg1.cols));
    //if (bg2.cols > 0)
	//    bg2.copyTo(frame(Rect(frame.cols - posicao, 0, bg2.cols, bg2.rows)));

}

int main(){
    //neste caso não usaremos a camera como background e sim uma imagem para ser o background, a qual irá ficar circulando (estilo flappy bird)
    //definindo a imagem que iremos usar como background
    Mat mustang = imread("imagens/mustang.jpg", IMREAD_UNCHANGED);

    //como essa imagem é muito grande iremos dar um rezise
    resize(mustang, mustang, Size(), 1/6.0, 1/6.0, INTER_LINEAR_EXACT);

    Mat background; //criando uma matriz para representar o background

    int velocidade = 1, posicao = 0;
    
    while(1){
        //background = mustang;
        circularDraw(mustang, background, velocidade, posicao);
        //posicao += 20;

        char c = (char)waitKey(100);
        if(c == 27 || c == 'q'){ //apertar q para sair do programa (quit)
            break;
        }

        cout << background.cols << " x " << background.rows << endl; //diz o tamanho da matriz do background

        imshow("result", background); //abre uma aba exibindo uma matriz, o primeiro parametro é o nome da aba
    }


    return 0;
}