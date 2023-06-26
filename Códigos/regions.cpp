#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

bool verificaPontos ( Point P1, Point P2, Point tamanho_imagem ); //Verificar a validade dos pontos

int main () {
    Mat image;

    image = imread ( "biel.png", IMREAD_GRAYSCALE ); //Abrir imagem
    if ( !image.data ) {
        cout << "Deu ruim" << endl;
        return -1;
    }

    namedWindow ( "Imagem_Original", WINDOW_AUTOSIZE ); //Criação da janela
    imshow ( "Imagem_Original", image ); //Exibição da janela
    waitKey ();
    destroyWindow ("Imagem_Original"); //Fechamento da janela

    Point P1, P2, tamanho_imagem;
    bool flag;

    tamanho_imagem.x = image.rows;
    tamanho_imagem.y = image.cols;

    cout << "Tamanho da imagem: " << tamanho_imagem.x << " x " << tamanho_imagem.y << endl;

    do {
        cout << "Digite as coordenadas (x,y) do pontos P1" << endl;
        cin >> P1.x >> P1.y;
        cout << "Digite as coordenadas (x,y) do pontos P2" << endl;
        cin >> P2.x >> P2.y;

        if ( P1.x >= P2.x || P1.y >= P2.y ) {
            cout << "\nAs coordenadas de P1 devem ser menores que as coordenadas de P2" << endl;
            continue;
        }
        flag = verificaPontos ( P1, P2, tamanho_imagem );
        if ( !flag ) {
            cout << "\nCoordenadas fora dos limites da imagem" << endl;
            cout << "Tamanho da imagem: " << tamanho_imagem.x << " x " << tamanho_imagem.y << endl;
        }

    } while ( !flag );

    /*P1.x = 30;
    P1.y = 90;
    P2.x = 200;
    P2.y = 180;*/

    for ( int i = P1.x; i < P2.x; i++ ) {
        for ( int j = P1.y; j < P2.y; j++ ) {
            image.at<uchar>( i, j ) = 255 - image.at<uchar>( i, j ); //Negativo da imagem
        }
    }

    namedWindow ( "Imagem_Negativa", WINDOW_AUTOSIZE ); //Criação da janela
    //imwrite ( "biel_negativa.png", image ); //Salvar imagem modificada
    imshow ( "Imagem_Negativa", image ); //Exibição da janela
    waitKey ();

    return 0;
}

bool verificaPontos ( Point P1, Point P2, Point tamanho_imagem ) {
    if ( P1.x > 0 && P1.x < tamanho_imagem.x && P1.y > 0 && P1.y < tamanho_imagem.y ) {
        if ( P2.x > 0 && P2.x < tamanho_imagem.x && P2.y > 0 && P2.y < tamanho_imagem.y ) {
            return true;
        }
    }
    return false;
}
