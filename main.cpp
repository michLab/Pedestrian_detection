#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>
#include <opencv2/features2d.hpp>
#include <math.h>

using namespace std;
using namespace cv;

int main()
{
    // Load an cascadeclassifier xml file:
    string body_cascade_name = "haarcascade_fullbody.xml";
    CascadeClassifier body_cascade;
    body_cascade.load(body_cascade_name);

    // Load a video from file:
    Mat frame;
    VideoCapture cap;
    string video_name = "walking.avi";
    if (!cap.open(video_name))
    {
        cout << "Cannot open the video file " << video_name << endl;
    }

    // Do things with this video:
    Mat frame_resized; // for resized video frame
    Mat gray; // for gray, resized video
    while (cap.read(frame))
    {
        resize(frame, frame_resized, Size(0,0), 0.5, 0.5);
        //imshow("Original size", frame);
        imshow("Resized", frame_resized);
        cvtColor(frame_resized, gray, COLOR_BGR2GRAY);
        // Find bodies using classifier:
        vector<Rect> bodies;
        body_cascade.detectMultiScale(gray, bodies, 1.3, 5);
        if (bodies.empty() == true)
        {
            cout << "No bodies found" << endl;
            continue;
        }
        else
        {
            cout << bodies.size() << " body(ies) found" << endl;
            imshow("Pedestrians", frame_resized);
        }
        for (auto elem : bodies)
        {
            Rect body_roi;
            body_roi.x = elem.x;
            body_roi.y = elem.y;
            body_roi.width = elem.width;
            body_roi.height = elem.height;

            rectangle(frame_resized, Point(body_roi.x,body_roi.y),
                      Point(body_roi.x + body_roi.width,
                            body_roi.y + body_roi.height),
                      Scalar(127,0,255),2);
            imshow("Pedestrians", frame_resized);
        }

        int k = waitKey(1);
        if (k == 27)
        {
           break;
        }
    }

    return 0;
}
