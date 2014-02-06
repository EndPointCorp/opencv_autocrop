// autocrop.cpp:
// Perform auto-cropping image with arbitrary background color

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <stdio.h>

/**
 * Function to check if the color of the given image
 * is the same as the given color
 *
 * Parameters:
 *   edge        The source image
 *   color   The color to check
 */
bool is_border(cv::Mat& edge, cv::Vec3b color)
{
    cv::Mat im = edge.clone().reshape(0,1);

    bool res = true;
    for (int i = 0; i < im.cols; ++i)
        res &= (color == im.at<cv::Vec3b>(0,i));

    return res;
}

/**
 * Function to auto-cropping image
 *
 * Parameters:
 *   src   The source image
 *   dst   The destination image
 */
void autocrop(cv::Mat& src, cv::Mat& dst)
{
    cv::Rect win(0, 0, src.cols, src.rows);

    std::vector<cv::Rect> edges;
    edges.push_back(cv::Rect(0, 0, src.cols, 1));
    edges.push_back(cv::Rect(src.cols-2, 0, 1, src.rows));
    edges.push_back(cv::Rect(0, src.rows-2, src.cols, 1));
    edges.push_back(cv::Rect(0, 0, 1, src.rows));

    cv::Mat edge;
    int nborder = 0;
    cv::Vec3b color = src.at<cv::Vec3b>(0,0);

    for (int i = 0; i < edges.size(); ++i)
    {
        edge = src(edges[i]);
        nborder += is_border(edge, color);
    }

    if (nborder < 4)
    {
        src.copyTo(dst);
        return;
    }

    bool next;

    do {
        edge = src(cv::Rect(win.x, win.height-2, win.width, 1));
        if (next = is_border(edge, color))
            win.height--;
    }
    while (next && win.height > 0);

    do {
        edge = src(cv::Rect(win.width-2, win.y, 1, win.height));
        if (next = is_border(edge, color))
            win.width--;
    }
    while (next && win.width > 0);

    do {
        edge = src(cv::Rect(win.x, win.y, win.width, 1));
        if (next = is_border(edge, color))
            win.y++, win.height--;
    }
    while (next && win.y <= src.rows);

    do {
        edge = src(cv::Rect(win.x, win.y, 1, win.height));
        if (next = is_border(edge, color))
            win.x++, win.width--;
    }
    while (next && win.x <= src.cols);

    dst = src(win);
}

/**
 * Test the autocrop() function above
 */
int main(int argc, char *argv[])
{

	if (argc != 3 ) {
		printf("Please launch me with two arguments - source file and destination file like:\n");
		printf("  ./autocrop input.png output.png\n");
		return -1;
	} else {
		cv::Mat src = cv::imread(argv[1]);
		if (!src.data)
			return -1;

		cv::Mat dst;
		autocrop(src, dst);

		cv::imwrite(argv[2], dst);
		return 0;
	}
}
