#ifndef _ARDRONE_DRIVER_H_
#define _ARDRONE_DRIVER_H_

#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <tf/transform_broadcaster.h>
#include <sensor_msgs/Image.h>
#include <sensor_msgs/Imu.h>
#include <sensor_msgs/SetCameraInfo.h>
#include <camera_info_manager/camera_info_manager.h>
#include <ardrone_autonomy/Navdata.h>
#include "ardrone_sdk.h"

#define _DEG2RAD 0.01745331111
#define _RAD2DEG 57.2957184819

class ARDroneDriver
{
public:
	ARDroneDriver();
	~ARDroneDriver();

	void run();
    double getRosParam(char* param, double defaultVal);
private:
	void publish_video();
	void publish_navdata();
    void publish_tf();

    ros::NodeHandle node_handle;
	ros::ServiceServer set_camera_info_srv_;
	boost::shared_ptr<camera_info_manager::CameraInfoManager> cinfo_;
	ros::Subscriber cmd_vel_sub;
	ros::Subscriber takeoff_sub;
	ros::Subscriber reset_sub;
	ros::Subscriber land_sub;
	image_transport::ImageTransport image_transport;
	image_transport::CameraPublisher image_pub;
    image_transport::CameraPublisher hori_pub;
	image_transport::CameraPublisher vert_pub;

    ros::Publisher navdata_pub;
    ros::Publisher imu_pub;

	sensor_msgs::CameraInfoPtr cam_info_ptr_;

    tf::TransformBroadcaster tf_broad;

	//ros::Subscriber toggleCam_sub;
	ros::ServiceServer toggleCam_service;
	ros::ServiceServer toggleNavdataDemo_service;
	ros::ServiceServer setCamChannel_service;
	ros::ServiceServer setLedAnimation_service;
	
	/*
	 * Orange Green : 1
	 * Orange Yellow: 2
	 * Orange Blue: 3
	 */
	//ros::ServiceServer setEnemyColor_service; 
	
	/*
	 * Indoor: 1
	 * Oudoor: 0
	 */
	//ros::ServiceServer setHullType_service;

	int last_frame_id;
	int flying_state;

    bool inited;
    std::string droneFrameId;
    std::string intrinsic_ini;


    /*
     * TF Frames
     * Base: Should be COM
     */
    std::string droneFrameBase, droneFrameIMU, droneFrameFrontCam, droneFrameBottomCam;

    // Huge part of IMU message is constant, let's fill'em once.
    sensor_msgs::Imu imu_msg;

};

#endif
