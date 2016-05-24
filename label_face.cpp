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

const char *WINNAME = "WINANME";

int g_xs[5], g_ys[5];
const int N_LANDMARK = (sizeof(g_xs) / sizeof(*g_xs));

vector<string> get_files(const string &dir) {
  DIR *dp;
  struct dirent *dirp;
  vector<string> filenames;

  if (!(dp = opendir(dir.c_str()))) {
    std::cerr << "Error opening dir." << std::endl;
    return filenames;
  }
  while ((dirp = readdir(dp))) {
    if (dirp->d_name == string(".") || dirp->d_name == string(".."))
      continue;
    string fname = dir + dirp->d_name;
    filenames.push_back(fname);
  }
  closedir(dp);

  return filenames;
}

static int on_mouse_idx = 0;

void on_mouse(int event, int x, int y, int flags, void *param)
{
  Mat &im = *(Mat *) param;
  if(event == CV_EVENT_LBUTTONDOWN) {
    g_xs[on_mouse_idx] = x;
    g_ys[on_mouse_idx] = y;
    on_mouse_idx = (on_mouse_idx + 1) % N_LANDMARK;
   
    circle(im, Point(x, y), 5, Scalar(0, 255, 0), 2);
    imshow(WINNAME, im);
  }
}

int main(int argc, char *argv[])
{
  string dir(argv[1]);
  int off;
  if (argv[2])
    off = atoi(argv[2]);
  else
    off = 0;
  vector<string> filepaths;

  filepaths = get_files(dir);
  if (filepaths.empty()) {
    return EXIT_FAILURE;
  }

  namedWindow(WINNAME, 1); 
  moveWindow(WINNAME, 400, 200);

  for (int i = off; i < filepaths.size(); ++i) {
    Mat im;
redraw:
    im = imread(filepaths[i], CV_LOAD_IMAGE_COLOR);
    on_mouse_idx = 0;
    setMouseCallback(WINNAME, on_mouse, &im);
    imshow(WINNAME, im);

    int kb = waitKey(0);
    switch (kb % 256) {
    case 'f':
      printf("%s", filepaths[i].c_str());
      for (int i = 0; i < N_LANDMARK; ++i) {
        printf("%4d %4d", g_xs[i], g_ys[i]);
      }
      puts("");
      break;
    default:
      goto redraw;
    }
  }
  return EXIT_SUCCESS;
}
