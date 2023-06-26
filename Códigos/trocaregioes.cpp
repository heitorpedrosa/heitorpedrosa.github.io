#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main () {
    Mat image, A, B, C, D, aux;

    image = imread ( "biel.png", IMREAD_GRAYSCALE ); //Abrir imagem
    if ( !image.data ) {
        cout << "Deu ruim" << endl;
        return -1;
    }

    namedWindow ( "Imagem_Original", WINDOW_AUTOSIZE ); //Criação da janela
    imshow ( "Imagem_Original", image ); //Exibição da janela
    waitKey ();
    destroyWindow ("Imagem_Original"); //Fechamento da janela

    Point centro;

    centro.x = ( int ) image.rows / 2;
    centro.y = ( int ) image.cols / 2;

    A = image ( Rect ( 0, 0, centro.x, centro.y ) ); //Superior esquerdo
    B = image ( Rect (centro.x, 0, centro.x, centro.y ) ); //Inferior esquerdo
    C = image ( Rect ( 0, centro.y, centro.x, centro.y ) ); //Superior direito
    D = image ( Rect (centro.x, centro.y, centro.x, centro.y ) ); //Inferior direito

    //Trocando superior esquerdo com inferior direito
    A.copyTo ( aux );
    D.copyTo ( A );
    aux.copyTo ( D );

    //Trocando superior direito com inferior esquerdo
    B.copyTo ( aux );
    C.copyTo ( B );
    aux.copyTo ( C );

    namedWindow ( "Imagem_Trocada", WINDOW_AUTOSIZE ); //Criação da janela
    //imwrite ( "biel_trocada.png", image ); //Salvar imagem modificada
    imshow ( "Imagem_Trocada", image ); //Exibição da janela
    waitKey ();

    return 0;
}
