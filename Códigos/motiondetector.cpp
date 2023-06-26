#include <iostream>
#include <opencv2/opencv.hpp>
#include  <time.h>
#include <math.h>

using namespace cv;
using namespace std;

int main () {
    Mat image;
    int width, height;
    VideoCapture cap;
    vector<Mat> planes;
    Mat histR,histV;
    int nbins = 64;
    float range [] = { 0, 256 };
    const float *histrange = { range };
    bool uniform = true;
    bool acummulate = false;

    int intervalo = 500;
    clock_t time_1, time_2;
    int saida_1 = -1;
    float thres = 40, dif = 0;
    double saida_2;

    cap.open ( 0 );

    if ( !cap.isOpened () ) {
        cout << "Deu ruim";
        return -1;
    }

    cap.set ( CAP_PROP_FRAME_WIDTH, 640 );
    cap.set ( CAP_PROP_FRAME_HEIGHT, 480 );
    width = cap.get ( CAP_PROP_FRAME_WIDTH );
    height = cap.get ( CAP_PROP_FRAME_HEIGHT );

    cout << "largura = " << width << endl;
    cout << "altura  = " << height << endl;

    int histw = nbins, histh = nbins / 2;
    Mat histImgR ( histh, histw, CV_8UC3, Scalar ( 0, 0, 0 ) );

    time_1 = clock ();
    histV.setTo ( Scalar ( 0 ) );

    while ( 1 ) {
        cap >> image;
        split ( image, planes );
        calcHist ( &planes [ 0 ], 1, 0, Mat (), histR, 1, &nbins, &histrange, uniform, acummulate );

        normalize ( histR, histR, 0, histImgR.rows, NORM_MINMAX, -1, Mat () );

        if ( saida_1 == -1 ) {
            histV = histR.clone ();
        }
        histImgR.setTo ( Scalar ( 0 ) );

        for ( int i = 0; i < nbins; i++ ) {
            dif += abs ( histV.at<float>( i ) - histR.at<float>( i ) );

            line ( histImgR, Point ( i, histh ), Point ( i, cvRound ( histR.at<float>( i ) ) ),Scalar ( 0, 0, 255 ), 1, 8, 0 );
        }

        if ( dif > thres ) {
            circle ( image, Point ( image.cols / 2, image.rows / 2 ), 200, Scalar ( 0, 0, 255 ), -200 );
        }

        dif = 0;

        histImgR.copyTo ( image ( Rect ( 0, 0 ,nbins, histh ) ) );
        imshow ( "", image );
        if ( waitKey ( 30 ) == 27 ) break;

        saida_1 = ( int ) clock () - ( time_1 );
        saida_2 = ( double ) ( ( saida_1 ) / ( double ) CLOCKS_PER_SEC );
        saida_2 *= 1000.0;
        if ( ( int ) saida_2 % intervalo < 100 ) {
            histV = histR.clone ();
        }
    }
    return 0;
}
