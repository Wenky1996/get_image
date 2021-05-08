#include<iostream>
#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>


void imageCallback(const sensor_msgs::ImageConstPtr& msg)
{
    try
    {
        cv::Mat  getImage=cv_bridge::toCvShare(msg, "bgr8")->image;

        cv::imshow("view", getImage);
	    std::string namePicture{"rgb_image"};
        if (cv::waitKey(50)==32){
            std::cout<<getImage.size<<std::endl;
            int numberPicture;
            std::cout<<"color image !!! \n input the number of picture"<<std::endl;
            std::cin>>numberPicture;
            namePicture+std::to_string(numberPicture);
            cv::imwrite(namePicture+std::to_string(numberPicture)+".bmp",getImage);
        }
    }
    catch (cv_bridge::Exception& e)
    {
        ROS_ERROR("Could not convert from '%s' to 'bgr8'.", msg->encoding.c_str());
    }
}

void imageLeftCallback(const sensor_msgs::ImageConstPtr& msg){
    try{
        cv::Mat getImage=cv_bridge::toCvShare(msg,"mono8")->image;
        cv::imshow("image left",getImage);
        std::string namePicture{"left_image"};
        if(cv::waitKey(50)==32){
            std::cout<<getImage.size<<std::endl;
            int numberPicture;
            std::cout<<"input the number of picture"<<std::endl;
            std::cin>>numberPicture;
            namePicture+std::to_string(numberPicture);
            cv::imwrite(namePicture+std::to_string(numberPicture)+".bmp",getImage);
        }
    }
    catch (cv_bridge::Exception& e)
    {
        ROS_ERROR("Could not convert from '%s' to 'mono8'.", msg->encoding.c_str());
    }
}

void imageRightCallback(const sensor_msgs::ImageConstPtr& msg){
    try{
        cv::Mat getImage=cv_bridge::toCvShare(msg,"mono8")->image;
        cv::imshow("image right",getImage);
        std::string namePicture{"right_image"};
        if(cv::waitKey(50)==32){
            std::cout<<getImage.size<<std::endl;
            int numberPicture;
            std::cout<<"input the number of picture"<<std::endl;
            std::cin>>numberPicture;
            namePicture+std::to_string(numberPicture);
            cv::imwrite(namePicture+std::to_string(numberPicture)+".bmp",getImage);
        }
    }
    catch (cv_bridge::Exception& e)
    {
        ROS_ERROR("Could not convert from '%s' to 'mono8'.", msg->encoding.c_str());
    }
}


int main(int argc, char **argv)
{
    ros::init(argc, argv, "image_listener");
    ros::NodeHandle nh;
    cv::namedWindow("view");
    cv::startWindowThread();
    image_transport::ImageTransport it(nh);
    image_transport::Subscriber subRgb = it.subscribe("/camera/color/image_raw", 1, imageCallback);
    image_transport::Subscriber subRight = it.subscribe("/camera/infra1/image_rect_raw",1, imageLeftCallback);
    image_transport::Subscriber subLeft = it.subscribe("/camera/infra2/image_rect_raw",1, imageRightCallback);
    ros::spin();
    cv::destroyWindow("view");
}
