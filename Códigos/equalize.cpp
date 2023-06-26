#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main () {
    Mat image;
    int width, height;
    VideoCapture cap;
    vector<Mat> planes;
    Mat histR, histG, histB;
    int nbins = 64;
    float range [] = { 0, 256 };
    const float *histrange = { range };
    bool uniform = true;
    bool acummulate = false;

    cap.open ( 0 );

    if ( !cap.isOpened () ) {
        cout << "Deu ruim";
        return -1;
    }

    cap.set ( CAP_PROP_FRAME_WIDTH, 640);
    cap.set ( CAP_PROP_FRAME_HEIGHT, 480 );
    width = cap.get ( CAP_PROP_FRAME_WIDTH );
    height = cap.get ( CAP_PROP_FRAME_HEIGHT );

    cout << "largura = " << width << endl;
    cout << "altura  = " << height << endl;

    int histw = nbins, histh = nbins / 2;
    Mat histImgR ( histh, histw, CV_8UC3, Scalar ( 0, 0, 0 ) );
    Mat histImgG ( histh, histw, CV_8UC3, Scalar ( 0, 0, 0 ) );
    Mat histImgB ( histh, histw, CV_8UC3, Scalar ( 0, 0, 0 ) );

    while ( 1 ) {
        cap >> image;
        split ( image, planes );

        equalizeHist ( planes [ 0 ], planes [ 0 ] );
        equalizeHist ( planes [ 1 ], planes [ 1 ] );
        equalizeHist ( planes [ 2 ], planes [ 2 ] );

        calcHist ( &planes [ 0 ], 1, 0, Mat (), histR, 1, &nbins, &histrange, uniform, acummulate );
        calcHist ( &planes [ 1 ], 1, 0, Mat (), histG, 1, &nbins, &histrange, uniform, acummulate );
        calcHist ( &planes [ 2 ], 1, 0, Mat (), histB, 1, &nbins, &histrange, uniform, acummulate );

        normalize ( histR, histR, 0, histImgR.rows, NORM_MINMAX, -1, Mat () );
        normalize ( histG, histB, 0, histImgR.rows, NORM_MINMAX, -1, Mat () );
        normalize ( histB, histB, 0, histImgR.rows, NORM_MINMAX, -1, Mat () );

        merge ( planes, image );

        histImgR.setTo ( Scalar ( 0 ) );
        histImgG.setTo ( Scalar ( 0 ) );
        histImgB.setTo ( Scalar ( 0 ) );

        for ( int i = 0; i < nbins; i++ ) {
            line ( histImgR, Point ( i, histh ), Point ( i, cvRound ( histR.at<float>( i ) ) ), Scalar ( 0, 0, 255 ), 1, 8, 0 );
            line ( histImgG, Point ( i, histh ), Point ( i, cvRound ( histG.at<float>( i ) ) ), Scalar ( 0, 255, 0 ), 1, 8, 0 );
            line ( histImgB, Point ( i, histh ), Point ( i, cvRound ( histB.at<float>( i ) ) ), Scalar ( 255, 0, 0 ), 1, 8, 0 );
        }

        histImgR.copyTo ( image ( Rect ( 0, 0, nbins, histh ) ) );
        histImgG.copyTo ( image ( Rect ( 0, histh, nbins, histh ) ) );
        histImgB.copyTo ( image ( Rect ( 0, 2 * histh, nbins, histh ) ) );

        imshow ( "Resultado", image );
        if ( waitKey ( 30 ) == 27 ) break;
    }
    return 0;
}
