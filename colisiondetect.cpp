#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
using namespace cv;

int main(){
    //usando como base o inicio.cpp com o video.mp4 como um background
    //nesse exemplo foi usado a detecção de rostos para poder mexer um retangulo
    //e ver se ele colide com algum outro
    Mat background; //criando uma matriz para representar o background

    VideoCapture capture; //objeto responsável pela captura do video

    //if(!capture.open(0)){ //se for utilizar a camera
    if(!capture.open("video.mp4")){ //se for utilizar um video
        cout << "Capture from camera #0 didn't work" << endl;
        return 1;
    }

    cout << "Ativei a camera\n"; //debug  

    //definindo as variaveis para detecçao
    CascadeClassifier cascade;
    string cascadeName = "haarcascade_frontalface_default.xml";

    //tentando abrir o cascade
    if (!cascade.load(cascadeName)) {
        cerr << "ERROR: Could not load classifier cascade: " << cascadeName << endl;
        return -1;
    }

    vector<Rect> fixo(3, Rect(Point(0, 0), Size(80, 100))); //inicializando 3 retangulos na posicao (0,0) e de tamanho (80 x 100)
    //Rect face(Point(0, 0), Size(80, 100)); //inicializando 1 retangulo na posicao (0,0) e de tamanho (80 x 100)
    vector<Rect> face;

    //definindo as posicoes de cada retangulo fixo
    fixo[0].x = 200;
    fixo[0].y = 70;
    fixo[1].x = 500;
    fixo[1].y = 200;
    fixo[2].x = 830;
    fixo[2].y = 400;
    
    while(1){
        capture.read(background); //passando o que for lido na camera para o background 

        resize(background, background, Size(), 1/2.0, 1/2.0, INTER_LINEAR_EXACT); //divindo a imagem da camera por 2 em cada dimensão

        //passos para poder identificar as faces
        Mat gray;
        cvtColor(background, gray, COLOR_BGR2GRAY);
        equalizeHist(gray, gray);

        cascade.detectMultiScale(gray, face,
        1.3, 2, 0
        //|CASCADE_FIND_BIGGEST_OBJECT
        //|CASCADE_DO_ROUGH_SEARCH
        |CASCADE_SCALE_IMAGE,
        Size(40, 40));



        //desenhando os retangulos no background
        //os parametros sao onde quer colocar o retangulo, o retangulo, cor(definida como blue green red) e a espessura
        for(int i = 0; i < fixo.size(); i++){
            if((fixo[i] & face[0]).area() > 10){                        //se houver intersecçao com area maior que 10(parametro arbitrario),
                rectangle(background, fixo[i], Scalar(0, 0, 255), 3);   //o retangulo que colidiu ira ficar vermelho 
            }else{
                rectangle(background, fixo[i], Scalar(0, 255, 255), 3); 
            }
        }

        //desenhando o retangulo da face
        rectangle(background, face[0], Scalar(255, 0, 255), 3);

        char c = (char)waitKey(100);
        if(c == 27 || c == 'q'){ //apertar q para sair do programa (quit)
            break;
        }

        cout << background.cols << " x " << background.rows << endl; //diz o tamanho da matriz do background

        imshow("result", background); //abre uma aba exibindo uma matriz, o primeiro parametro é o nome da aba
    }

    return 0;
}