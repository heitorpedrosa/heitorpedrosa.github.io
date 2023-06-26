#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;


int main () {
    Mat original, image;
    Point p;
    int n_com_furos = 0, n_sem_furos = 0;

    original = imread ( "bolhas.png", IMREAD_GRAYSCALE );

    if ( original.empty () ) {
        cout << "Deu ruim" << endl;
        return -1;
    }

    image = original.clone ();

    p.x = 0;
    p.y = 0;

    //Retirar as bolhas que estejam nas bordas
    for ( int i = 0; i < image.rows; i++ ) {
        //Borda esquerda
        if ( image.at<uchar>( i, 0 ) == 255 ) {
            p.x = 0;
            p.y = i;
            floodFill ( image, p, 0 );
        }
        //Borda direita
        if ( image.at<uchar>( i, image.cols - 1 ) == 255 ) {
            p.x = image.cols - 1;
            p.y = i;
            floodFill ( image, p, 0 );
        }
    }

    for ( int i = 0; i < image.cols; i++ ) {
        //Borda superior
        if ( image.at<uchar>( 0, i ) == 255 ) {
            p.x = i;
            p.y = 0;
            floodFill ( image, p, 0 );
        }
        //Borda inferior
        if ( image.at<uchar>( image.rows - 1 , i ) == 255 ) {
            p.x = i;
            p.y = image.cols - 1;
            floodFill ( image, p, 0 );
        }
    }

    //Preencher fundo com cor diferente
    p.x = 0;
    p.y = 0;
    floodFill ( image, p, 1 );

    //Bolhas com 1 furo ou mais
    for ( int i = 0; i < image.rows; i++ ) {
        for ( int j = 0; j < image.cols; j++ ) {
            if ( image.at<uchar>( i, j ) == 0 && image.at<uchar>( i - 1, j - 1 ) == 255 ) {
                n_com_furos++;

                p.x = j - 1;
                p.y = i - 1;
                floodFill ( image, p, 80 );

                p.x = j;
                p.y = i;
                floodFill ( image, p, 128 );
            }

            //Furos dentro de bolhas já contadas
            if ( image.at<uchar>( i, j ) == 255 && image.at<uchar>( i - 1, j - 1 ) == 128 ) {
                p.x = j;
                p.y = i;
                floodFill ( image, p, 180 );
            }
        }
    }

    //Bolhas sem furos
    for ( int i = 0; i < image.rows; i++ ) {
        for ( int j = 0; j < image.cols; j++ ) {
            if ( image.at<uchar>( i, j ) == 255 ) {
                n_sem_furos++;
                p.x = j;
                p.y = i;
                floodFill ( image, p, 254 );
            }
        }
    }

    cout << "Bolhas com furos: " << n_com_furos << endl;
    cout << "Bolhas sem furos: " << n_sem_furos << endl;

    imshow ( "image", image );
    imwrite ( "bolhas.png", image );
    waitKey ();

    return 0;
}

