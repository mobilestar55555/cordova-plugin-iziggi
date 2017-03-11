//
//  ICCameraManager.h
//  IPEVOCameraKit
//
//  Created by Kevin on 2014/10/27.
//  Copyright (c) 2014 IPEVO Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ICNetCamera.h"

/*
    If the manager found a new camera, the ICNotificationCameraAttached will be fired through NSNotificationCenter.
    You can observe the notification to retrieve new camera list.
*/
#define ICNotificationCameraAttached @"CameraAttached"

/*
    If the manager found a camera disconnected, the ICNotificationCameraDetached will be fired through NSNotificationCenter.
    You can observe the notification to retrieve new camera list.
*/
#define ICNotificationCameraDetached @"CameraDetached"

#define CM_NET_DOMAIN (@"local.")
#define NS_TYPE_IPEVO_DEV_ANNOUNCE   (@"_ipeDevPub._udp.")
#define NS_TYPE_MJPEG_STREAMER       (@"_mjpegStreamer._tcp.")
#define NS_TYPE_IPEVO_DEVICE_SETTING (@"_ipeDevSet._tcp.")
#define NS_TYPE_IPEVO_CAMERA_SETTING (@"_ipeCamSet._tcp.")
#define NS_TYPE_IPEVO_FILE_BROWSING  (@"_ipeFileServ._tcp.")

@interface ICCameraManager : NSObject <NSNetServiceBrowserDelegate>

@property (nonatomic, strong, readonly) NSArray * cameras;
@property (nonatomic, readonly) dispatch_queue_t monitorQueue;

+ (ICCameraManager *) sharedManager;
@end
