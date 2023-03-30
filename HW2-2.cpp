#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;

class USM {
	public:
        Mat gaussian(Mat src) {
            Mat img_blur;
            GaussianBlur(src, img_blur, Size(3, 3), 15, 0, 4);
            return img_blur;
        }

        Mat mask(Mat src, Mat blur) {
            Mat mask;
            mask = src - blur;
            return mask;
        }

        Mat unsharpMask(Mat src, Mat mask) {
            Mat img_unsharp_mask;
            img_unsharp_mask = src + mask;
            return img_unsharp_mask;
        }
};
int main() {
    Mat img_src = imread("2-2_Image.png");
    Mat img_usm, img_blur, img_mask;
    if (!img_src.data)
    {
        cout << "檔案開啟失敗" << endl;
        return 0;
    }
    USM usm;
    img_blur = usm.gaussian(img_src);
    img_mask = usm.mask(img_src, img_blur);
    img_usm = usm.unsharpMask(img_src, img_mask);
    
    //模糊化
    imshow("Blur", img_blur);
    imwrite("Blur.png", img_blur);

    //mask
    imshow("Mask", img_mask);
    imwrite("Mask.png", img_mask);

    //USM
    imshow("UnsharpMask", img_usm);
    imwrite("UnsharpMask.png", img_usm);

    waitKey(0);
	return 0;
}
