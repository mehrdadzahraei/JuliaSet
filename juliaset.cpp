/*!\file windows.c
 *
 * \brief Programmation Temps Réel : Fractales de Julia
 *
 * \author Mehrdad ZAHRAEI
 * \date 13.03.2017
 */
#include <stdio.h>
#include <iostream>
#include <fstream>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <thread>
using namespace cv;
using namespace std;
#ifndef NB_THREAD
#define NB_THREAD thread::hardware_concurrency() //to get nof cores
#endif
#ifndef _W
#define _W 400
#endif
#ifndef _H
#define _H 400
#endif

/*!\brief image partagé en global pour donner accés a tout les threads */
Mat img(_H, _W, CV_8UC3);//img(cols, rows, flags)
/*!\brief constante complexe globale */
complex<long double> c;

/*!\brief variable permet de centrer l'image par un décalage sur x,y */
Point _offset = Point(0, 0);

/*!\brief Fonction pour incrementer le nombre complex
 * \param nb_complex Nombre complexe
*/
long double incr(long double& nb_complex){
  return (( (nb_complex += 0.00005) < 1. )? nb_complex : (nb_complex -= 2.));
} 

/*!\brief Fonction qui calcul la valeur d'un pixel
 * \param x La partie reel
 * \param y La partie imaginaire
*/
Vec3b calcul_pixel(long double x, long double y){
  complex<long double> z(x, y);
  int val(0);
  while((val < 255) && (norm(z) < 4)){
    z = z * z + c;
    val++;
  }
  return Vec3b(135 , 255  , 255 -val);
}

/*!\brief Fonction threads
*/
void thread_func(){

  int i = 0, n = img.rows;
  for(; i < n; i++)
    for(int j(0); j < img.cols; j++){
      img.at<Vec3b>(Point(j, i)) = calcul_pixel(((long double)(i + _offset.x)/(img.rows)) * 2. - 1.,
                                                ((long double)(j + _offset.y)/(img.cols)) * 2. - 1.);
    }
}

/*!\brief Fonction principale (Main)
 * \param argc Nombre de paramètres 
 * \param argv Tableau de paramètres
*/
int main(int argc, char ** argv) { 
  Point pt;
  long double reel(0.285), imaginaire(0.013);
  int cnt(0), round_max = ((argc >= 2)? atoi(argv[1]):10);
  cvNamedWindow("Fractale de julia", CV_WINDOW_AUTOSIZE);
  moveWindow("Fractale de julia", 0, 0);
  while(1) {
    c = complex<long double> (incr(reel), incr(imaginaire));
    thread_func();
    cvtColor(img, img, CV_HSV2RGB);
    imshow("Fractale de julia", img);
    if((waitKey(10) & 0xFF) == 'q' || (waitKey(10) & 0xFF) == 27 || cnt >= round_max){
    return 0;
    }
  }
  return 0;
}
