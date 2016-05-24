#include <algorithm>
#include <fstream>
#include <string>
#include <utility>
#include <vector>

#include <dirent.h>
#include <sys/types.h>

#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui_c.h>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

int main(int argc, char *argv[])
{
  string lmfile(argv[1]);
  ifstream lmf(lmfile.c_str());

  int idx, xs[5], ys[5];
  string impath;
  while (lmf >> idx) {
    lmf >> impath;
    for (int i = 0; i < 5; ++i) {
      lmf >> xs[i] >> ys[i];
    }

    Mat im = imread(impath.c_str(), CV_LOAD_IMAGE_COLOR);
    for (int i = 0; i < 5; ++i) {
      circle(im, Point(xs[i], ys[i]), 2, Scalar(0, 0, 255), 2);
    }
    imshow("", im);
    waitKey(0);
  }
  return EXIT_SUCCESS;
}
