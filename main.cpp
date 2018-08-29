#include <opencv2/opencv.hpp>
using namespace cv;

void Camaratest();

int main()
{
    /*std::vector<cv::Mat> vImg;
    cv::Mat rImg;
    cv::Mat img_l, img_r, img_l_l, img_r_l;
    img_l = cv::imread("IMG_L.jpg");
    img_r = cv::imread("IMG_M.jpg");

    cv::resize(img_l, img_l_l, cv::Size(), 0.3,0.3);
    cv::resize(img_r, img_r_l, cv::Size(), 0.3,0.3);
    printf("Size of img->(%d , %d) \r\n",img_l_l.cols,img_l_l.rows);
    vImg.push_back(img_l_l);
    vImg.push_back(img_r_l);

    for (int i = 0; i < vImg.size(); ++i) {
        if (!vImg[i].data) {
            printf("There are no enough picture\r\n");
            return 0;
        }
    }
    //MyStitcher(vImg);

    cv::Stitcher stitcher = cv::Stitcher::createDefault();

    unsigned long AAtime = 0, BBtime = 0; //check processing time
    AAtime = cv::getTickCount(); //check processing time

    cv::Stitcher::Status status = stitcher.stitch(vImg, rImg);

    BBtime = cv::getTickCount(); //check processing time
    printf("Time consuming: %.2lf sec \n", (BBtime - AAtime) / cv::getTickFrequency()); //check processing time

    if (cv::Stitcher::OK == status) {
        cv::Mat out;
        cv::resize(rImg, out, cv::Size(),0.25,0.25);
        cv::imshow("Stitching Result", out);
        printf("outImgSize> %d,%d\r\n", rImg.cols, rImg.rows);
        cv::imwrite("Stitched_Img.jpg", rImg);
    } else
        printf("Stitching fail.");

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
    for(int n=0;n<1;n++)
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
    imshow("mask",stitcher.maskwarped_[0]);
    imwrite("output.jpg",blended);*/
    waitKey(0);
    Camaratest();
    waitKey(0);
    return 0;
}

