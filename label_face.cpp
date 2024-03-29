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
const double RESIZE_ALPHA = 2;

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
    string fname = dir + "/" + dirp->d_name;
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
    if (on_mouse_idx >= N_LANDMARK) {
      std::cerr << "JESUS, You have clicked too many times!" << std::endl;
      return;
    }
    g_xs[on_mouse_idx] = x;
    g_ys[on_mouse_idx] = y;
    on_mouse_idx++;
   
    circle(im, Point(x, y), 2, Scalar(0, 0, 255), 2);
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
    if (!im.data) {
      cerr << "Warning: can't open" << filepaths[i] << ", trash-put it!" << endl;
      system((string("trash-put ") + filepaths[i]).c_str());
      continue;
    }
    resize(im, im, Size(), RESIZE_ALPHA, RESIZE_ALPHA);

    on_mouse_idx = 0;
    setMouseCallback(WINNAME, on_mouse, &im);
    try {
      imshow(WINNAME, im);
    }
    catch (cv::Exception ex) {
      cerr << "Warning: " << filepaths[i] << " can't be displaied" << endl;
      continue;
    }

    int kb = waitKey(0);
    switch (kb % 256) {
    case 'f':
      printf("%-5d %-20s", i, filepaths[i].c_str());
      for (int i = 0; i < N_LANDMARK; ++i) {
        printf("%5d %5d", (int) (g_xs[i] / RESIZE_ALPHA), (int) (g_ys[i] / RESIZE_ALPHA));
      }
      puts("");
      break;
    case 'q':
      return EXIT_SUCCESS;
    default:
      goto redraw;
    }
  }
  return EXIT_SUCCESS;
}
