#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;


int main () {
    Mat imagemPortadora, imagemEscondida, imagemFinal;
    Vec3b valPortadora, valEscondida, valFinal;
    int nbits = 3;

    imagemPortadora = imread ( "sushi.png", IMREAD_COLOR );
    imagemEscondida = imread ( "biel_colorida.png", IMREAD_COLOR );

    if ( imagemPortadora.empty () || imagemEscondida.empty () ) {
        cout << "Deu ruim" << endl;
        return -1;
    }

    if ( imagemPortadora.rows != imagemEscondida.rows || imagemPortadora.cols != imagemEscondida.cols ) {
        cout << "As imagens devem ter o mesmo tamanho" << endl;
        return -1;
    }

    imagemFinal = imagemPortadora.clone ();

    for ( int i = 0; i < imagemPortadora.rows; i++ ) {
        for ( int j = 0; j < imagemPortadora.cols; j++ ) {
            valPortadora = imagemPortadora.at<Vec3b>( i, j );
            valEscondida = imagemEscondida.at<Vec3b>( i, j );
            valPortadora [ 0 ] = valPortadora [ 0 ] >> nbits << nbits;
            valPortadora [ 1 ] = valPortadora [ 1 ] >> nbits << nbits;
            valPortadora [ 2 ] = valPortadora [ 2 ] >> nbits << nbits;
            valEscondida [ 0 ] = valEscondida [ 0 ] >> ( 8 - nbits );
            valEscondida [ 1 ] = valEscondida [ 1 ] >> ( 8 - nbits );
            valEscondida [ 2 ] = valEscondida [ 2 ] >> ( 8 - nbits );
            valFinal [ 0 ] = valPortadora [ 0 ] | valEscondida [ 0 ];
            valFinal [ 1 ] = valPortadora [ 1 ] | valEscondida [ 1 ];
            valFinal [ 2 ] = valPortadora [ 2 ] | valEscondida [ 2 ];
            imagemFinal.at<Vec3b>( i, j ) = valFinal;
        }
    }

    imwrite ( "esteganografia.png", imagemFinal );

    return 0;
}

