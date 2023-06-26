#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;


int main () {
    Mat imagemEscondida, imagemFinal;
    Vec3b valEscondida, valFinal, valAux;
    int nbits = 3;

    imagemFinal = imread ( "esteganografia.png", IMREAD_COLOR );

    if ( imagemFinal.empty () ) {
        cout << "Deu ruim" << endl;
        return -1;
    }

    imagemEscondida = imagemFinal.clone ();

    imshow ( "", imagemFinal );
    waitKey ();
    destroyWindow ( "" );

    for ( int i = 0; i < imagemEscondida.rows; i++ ) {
        for ( int j = 0; j < imagemEscondida.cols; j++ ) {
            valEscondida = imagemEscondida.at<Vec3b>( i, j );
            valEscondida [ 0 ] = valEscondida [ 0 ] << ( 8 - nbits );
            valEscondida [ 1 ] = valEscondida [ 1 ] << ( 8 - nbits );
            valEscondida [ 2 ] = valEscondida [ 2 ] << ( 8 - nbits );
            imagemEscondida.at<Vec3b>( i, j ) = valEscondida;
        }
    }

    imwrite ( "esteganografia_decode.png", imagemEscondida );
    imshow ( "", imagemEscondida );
    waitKey ();

    return 0;
}
