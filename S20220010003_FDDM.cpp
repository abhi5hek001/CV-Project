#include <opencv2/opencv.hpp>
#include <opencv2/features2d.hpp> 
#include <iostream>

using namespace cv;
using namespace std;

int main() {
    Mat img = imread("img1.jpeg", IMREAD_GRAYSCALE);
    if (img.empty()) {
        cerr << "Error: Could not load image img1.jpeg" << endl;
        return -1;
    }

    Mat harrisCorners, harrisNormalized;
    harrisCorners = Mat::zeros(img.size(), CV_32FC1);

    cornerHarris(img, harrisCorners, 2, 3, 0.04);
    normalize(harrisCorners, harrisNormalized, 0, 255, NORM_MINMAX, CV_32FC1, Mat());

    Mat harrisScaled;
    convertScaleAbs(harrisNormalized, harrisScaled);

    for (int i = 0; i < harrisNormalized.rows; i++) {
        for (int j = 0; j < harrisNormalized.cols; j++) {
            if ((int)harrisNormalized.at<float>(i, j) > 200) {
                circle(img, Point(j, i), 5, Scalar(255), 2);
            }
        }
    }

    Ptr<SIFT> sift = SIFT::create();  
    vector<KeyPoint> keypoints;
    Mat descriptors;

    sift->detectAndCompute(img, noArray(), keypoints, descriptors);  

    Mat imgKeypoints;
    drawKeypoints(img, keypoints, imgKeypoints, Scalar::all(-1), DrawMatchesFlags::DEFAULT);

    Mat img2 = imread("img2.jpeg", IMREAD_GRAYSCALE);
    if (img2.empty()) {
        cerr << "Error: Could not load image img2.jpeg" << endl;
        return -1;
    }

    vector<KeyPoint> keypoints2;
    Mat descriptors2;
    sift->detectAndCompute(img2, noArray(), keypoints2, descriptors2);

    BFMatcher matcher(NORM_L2);
    vector<vector<DMatch>> knnMatches;
    matcher.knnMatch(descriptors, descriptors2, knnMatches, 2);

    vector<DMatch> goodMatches;
    for (size_t i = 0; i < knnMatches.size(); i++) {
        if (knnMatches[i][0].distance < 0.75 * knnMatches[i][1].distance) {
            goodMatches.push_back(knnMatches[i][0]);
        }
    }

    Mat imgMatches;
    drawMatches(img, keypoints, img2, keypoints2, goodMatches, imgMatches, Scalar::all(-1), Scalar::all(-1), vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);

    imshow("Harris Corners", harrisScaled);     
    imshow("SIFT Keypoints", imgKeypoints);     
    imshow("Feature Matches", imgMatches);      

    waitKey(0);
    return 0;
}

