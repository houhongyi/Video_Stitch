#include <opencv2/opencv.hpp>
#include "Camera.h"
using namespace cv;

#define Mouse_Scale_Max 1.6
#define Mouse_Scale_Min 1
#define OutImg_W 640//1920
#define OutImg_H 480//1080

Point Mouse_pt(0,0);
float Mouse_Scale=1.0f;
void on_MouseHandle(int event,int x,int y, int flags ,void* param);
int Mouse_LB=0;
int Mouse_RB=0;


inline void MaxMin(float* a,float max,float min)
{
    if(*a>max)*a=max;
    if(*a<min)*a=min;
}


int main()
{

    std::vector<cv::Mat> vImg;
    cv::Mat rImg;
    cv::Mat img_l, img_r, img_l_l, img_r_l;
    img_l = cv::imread("imgStitch/Img_02.jpg");
    img_r = cv::imread("imgStitch/Img_01.jpg");


    cv::resize(img_l, img_l_l, cv::Size(), 1,1);
    cv::resize(img_r, img_r_l, cv::Size(), 1,1);
    printf("Size of img->(%d , %d) \r\n",img_l_l.cols,img_l_l.rows);
    vImg.push_back(img_l_l);
    vImg.push_back(img_r_l);
    //vImg.push_back(cv::imread("Img3.jpeg"));
    //vImg.push_back(cv::imread("Img4.jpeg"));

    for (int i = 0; i < vImg.size(); ++i) {
        if (!vImg[i].data) {
            printf("There are no enough picture\r\n");
            return 0;
        }
    }

    cv::Stitcher stitcher = cv::Stitcher::createDefault();
    stitcher.do_wave_correct_= false;
    stitcher.conf_thresh_=1;

    unsigned long AAtime = 0, BBtime = 0; //check processing time
    AAtime = cv::getTickCount(); //check processing time

    cv::Stitcher::Status status = stitcher.stitch(vImg, rImg);

    BBtime = cv::getTickCount(); //check processing time
    printf("Time consuming: %.2lf sec \n", (BBtime - AAtime) / cv::getTickFrequency()); //check processing time
    cv::Mat out;
    if (cv::Stitcher::OK == status) {
        cv::resize(rImg, out,cv::Size(),0.1,0.1);
        cv::imshow("Stitching Result", out);
        printf("outImgSize> %d,%d\r\n", rImg.cols, rImg.rows);
        cv::imwrite("Stitched_Img.jpg", rImg);
    } else{
        printf("Stitching fail.");
        return 0;
    }


    waitKey(0);
    namedWindow("WholeView");
    namedWindow("Out_1080P");
    setMouseCallback("WholeView",on_MouseHandle,NULL);
    Point Display_pt(0,0);
    float Display_W=OutImg_W;
    float Display_H=OutImg_H;
    Rect DisplayRect;
    while(1)
    {
        char c=waitKey(5);
        if (27==c)
            return 0;

        Display_pt.x+=(Mouse_pt.x-Display_pt.x)*0.05;
        Display_pt.y+=(Mouse_pt.y-Display_pt.y)*0.05;


        if(!Mouse_LB)Mouse_Scale+=0.05;
        else Mouse_Scale-=0.05;
        MaxMin(&Mouse_Scale,Mouse_Scale_Max,Mouse_Scale_Min);

        Display_W=OutImg_W*Mouse_Scale;
        Display_H=OutImg_H*Mouse_Scale;

        Mat WholeView=out.clone();

        //防止鼠标飘离有效区域

        if(Display_pt.x-Display_W/2<0)Display_pt.x=Display_W/2;
        if(Display_pt.y-Display_H/2<0)Display_pt.y=Display_H/2;
        if(Display_pt.x+Display_W/2>rImg.cols)Display_pt.x=rImg.cols-Display_W/2;
        if(Display_pt.y+Display_H/2>rImg.rows)Display_pt.y=rImg.rows-Display_H/2;

        DisplayRect=Rect(Display_pt.x-Display_W/2,Display_pt.y-Display_H/2,Display_W,Display_H);
        Mat temOut=rImg(DisplayRect).clone();

        resize(temOut,temOut,Size(OutImg_W,OutImg_H));
        imshow("Out_1080P",temOut);
        rectangle(WholeView,Rect(DisplayRect.x/10,DisplayRect.y/10,DisplayRect.width/10,DisplayRect.height/10),Scalar(255,255,255));
        imshow("WholeView",WholeView);

    }

#ifdef RepeatStiting
    //===================================连续拼合====================================
    UMat img_remaped_l,img_remaped_r,img_resault;
    img_remaped_l.create(stitcher.warpmapsX_[0].size(),img_l_l.type());
    img_remaped_r.create(stitcher.warpmapsX_[1].size(),img_r_l.type());
    unsigned long Remaptime = 0;
    unsigned long stitichtime = 0;
    unsigned long blendtime = 0;
    Remaptime = cv::getTickCount();
    stitichtime=Remaptime;
    cv::Mat blended;
    for(int n=0;n<1;n++)1.5
    {
        remap(img_l_l, img_remaped_l, stitcher.warpmapsX_[0], stitcher.warpmapsY_[0], INTER_LINEAR, BORDER_REFLECT);
        remap(img_r_l, img_remaped_r, stitcher.warpmapsX_[1], stitcher.warpmapsY_[1], INTER_LINEAR, BORDER_REFLECT);
        printf("Remap consuming: %.4lf sec \n", ( cv::getTickCount() - Remaptime) / cv::getTickFrequency());
        blendtime=cv::getTickCount();
        stitcher.blender_->clear();
        stitcher.blender_->feed(img_remaped_l,stitcher.maskwarped_[0],stitcher.warpdst_roi_[0].tl());
        stitcher.blender_->feed(img_remaped_r,stitcher.maskwarped_[1],stitcher.warpdst_roi_[1].tl());
        stitcher.blender_->blend(img_resault,UMat());
        img_resault.con/home/happy/ClionProjects/OpencvTest/DebugvertTo(blended, CV_8U);
        printf("Blend consuming: %.4lf sec \n", ( cv::getTickCount() - blendtime) / cv::getTickFrequency());
    }
    printf("Stitch consuming: %.4lf sec \n", ( cv::getTickCount() - stitichtime) / cv::getTickFrequency()); //check processing time
    imshow("remap_l",img_remaped_l);
    imshow("remap_R",img_remaped_r);
    imshow("remap_resault",blended);
    imshow("mask",stitcher.            maskMouse_LBwarped_[0]);
    imwrite("output.jpg",blended);*/
#endif
    waitKey(0);
    return 0;
}


void on_MouseHandle(int event,int x,int y, int flags ,void* param)
{
    switch(event)
    {
        case EVENT_MOUSEMOVE:
            Mouse_pt.x=x*10;
            Mouse_pt.y=y*10;
            break;
        case EVENT_LBUTTONDOWN:
            Mouse_LB=1;
            //MaxMin(&Mouse_Scale,Mouse_Scale_Max,Mouse_Scale_Min);
            break;
        case EVENT_LBUTTONUP:
            Mouse_LB=0;
            break;
        case EVENT_RBUTTONDOWN:
            Mouse_RB=1;
            //MaxMin(&Mouse_Scale,Mouse_Scale_Max,Mouse_Scale_Min);
            break;
        case EVENT_RBUTTONUP:
            Mouse_RB=0;
            break;
    }

}