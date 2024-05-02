#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

//função para desenhar algo sem transparência, como parametros temos a matriz(frame)
//na qual iremos desenhar a imagem(img) na posição xPos, yPos de acordo com a orientação
//da matriz, na qual se aumenta da esquerda para direita e de cima para baixo
void drawNoTransparency(Mat frame, Mat img, int xPos, int yPos){ 
    img.copyTo(frame.rowRange(yPos, yPos + img.rows).colRange(xPos, xPos + img.cols));
}

//função para fazer um background ficar "girando", a variável posicao é apenas para
//indicar onde está sendo o corte no background, que será uma imagem fixa. Frame será
//a exibição de forma alterada do background
void circularDraw(Mat background, Mat frame, int& posicao){
    if(posicao > background.cols){//verifica se o corte passou do tamanho do background
        posicao = 0;
    }
    
    //fazer dois cortes no background e colá-los em frame de forma a exibir algo que esteja circular
    Rect crop1(posicao, 0, background.cols - posicao, background.rows);
    Mat bg1 = background(crop1);
    Rect crop2(0, 0, posicao, background.rows);
    Mat bg2 = background(crop2);

    if (bg1.cols > 0){//verifica se o primeiro corte tem algum tamanho
        bg1.copyTo(frame.rowRange(0, bg1.rows).colRange(0, bg1.cols));
    }
    if (bg2.cols > 1){//verifica se o segundo corte tem algum tamanho
	    bg2.copyTo(frame(Rect(frame.cols - posicao, 0, bg2.cols, bg2.rows)));
    }
    
}

int main(){
    //neste caso não usaremos a camera como background e sim uma imagem
    //para ser o background, a qual irá ficar circulando (estilo flappy bird)

    //definindo a imagem que iremos usar como background
    Mat mustang = imread("imagens/mustang.jpg", IMREAD_UNCHANGED);

    //como essa imagem é muito grande iremos dar um rezise
    resize(mustang, mustang, Size(), 1/6.0, 1/6.0, INTER_LINEAR_EXACT);

    Mat background = mustang.clone();   //criando uma matriz para representar o background
                                        //e atribuindo a ela a imagem que usaremos como background


    int velocidade = 10, posicao = 0;   //a velocidade que se deseja fazer o background se mexer e
                                        //a variavel auxiliar posicao para o funcionamento da função
    
    while(1){
        circularDraw(mustang, background, posicao);
        posicao += velocidade;

        char c = (char)waitKey(100);
        if(c == 27 || c == 'q'){ //apertar q para sair do programa (quit)
            break;
        }

        cout << background.cols << " x " << background.rows << endl; //diz o tamanho da matriz do background

        imshow("result", background); //abre uma aba exibindo uma matriz, o primeiro parametro é o nome da aba
    }


    return 0;
}