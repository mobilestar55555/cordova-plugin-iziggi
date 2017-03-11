//
//  ICNetCamera.h
//  IPEVOCameraKit
//
//  Created by Kevin on 2014/10/29.
//  Copyright (c) 2014 IPEVO Inc. All rights reserved.
//

#import "ICCamera.h"

#define ICNotificationCameraSettingAvailable @"CameraSettingAvailable"

typedef NS_ENUM(NSInteger, IPEVOCameraCommand)  {
    IPEVOCameraCommandSetResolution = 0x29,
    IPEVOCameraCommandGetCurrentResolution = 0x2A,
    IPEVOCameraCommandGetSupportedResolutions = 0x2B,
    IPEVOCameraCommandFocus = 0x04,
    IPEVOCameraCommandSetAutoExposure = 0x02,
    IPEVOCameraCommandGetAutoExposure = 0x0B,
    IPEVOCameraCommandSetExposure = 0x03, // value 1~15
    IPEVOCameraCommandGetEposure = 0x06,
    IPEVOCameraCommandGetFocusMode = 0x05, // 0: AF-S, 1:AF-C
    IPEVOCameraCommandGetFocusStatus = 0x09, // 0: normal, 1: focusing
    IPEVOCameraCommandSetPowerFrequency = 0x01, // 0: 60Hz, 1: 50Hz
    IPEVOCameraCommandGetPowerFrequency = 0x07, // 0: 60Hz, 1: 50Hz
    IPEVOCameraCommandGetAllStatus = 0x0A,
    IPEVOCameraCommandGetAPIVersion = 0x0C
};

@interface ICNetCamera : ICCamera <NSNetServiceDelegate>
/*
    parameters:
        username: The administrator account on iZiggi.
        password: The password of the administrator on iZiggi.
    
    completionHandler parameters:
        resolutions: An array contains the resolution infomation.
    
    failureHandler parameters:
        error: The reason of failure.
*/
- (void) getSupportedResolutionsWithUsername:(NSString *) username andPassword:(NSString *) password completionHandler:(void (^)(NSArray * resolutions)) completionHandler failureHandler:(void (^)(NSError * error)) failureHandler;

/*
    parameters:
        username: The administrator account on iZiggi.
        password: The password of the administrator on iZiggi.
    
    completionHandler parameters:
        resolution: The current resolution. e.g. @"1024x768"
    
    failureHandler parameters:
        error: The reason of failure.
*/
- (void) getCurrentResolutionWithUsername:(NSString *) username andPassword:(NSString *) password completionHandler:(void (^)(NSString * resolution)) completionHandler failureHandler:(void (^)(NSError * error)) failureHandler;

/*
    parameters:
        resolution: The resolution to be set. e.g. @"1024x768"
        username: The administrator account on iZiggi.
        password: The password of the administrator on iZiggi.
    
    completionHandler parameters:
        resolution: The current resolution after setting. e.g. @"1024x768"
    
    failureHandler parameters:
        error: The reason of failure.
*/
- (void) setResolution:(NSString *) resolution withUsername:(NSString *) username andPassword:(NSString *) password completionHandler:(void (^)(NSString * resolution)) completionHandler failureHandler:(void (^)(NSError * error)) failureHandler;

/*
    parameters:
        username: The administrator account on iZiggi.
        password: The password of the administrator on iZiggi.
    
    completionHandler parameters:
        none
    
    failureHandler parameters:
        error: The reason of failure.
*/
- (void) startFocusingWithUsername:(NSString *) username andPassword:(NSString *) password completionHandler:(void (^)(void)) completionHandler failureHandler:(void (^)(NSError * error)) failureHandler;

/*
    parameters:
        value: 0 -> Enable auto exposure, 1 -> Disable auto exposure
        username: The administrator account on iZiggi.
        password: The password of the administrator on iZiggi.
    
    completionHandler parameters:
        none
    
    failureHandler parameters:
        error: The reason of failure.
*/
- (void) setAutoExposure:(NSInteger) value withUsername:(NSString *) username andPassword:(NSString *) password completionHandler:(void (^)(void)) completionHandler failureHandler:(void (^)(NSError * error)) failureHandler;

/*
    parameters:
        username: The administrator account on iZiggi.
        password: The password of the administrator on iZiggi.
    
    completionHandler parameters:
        autoExposure: 0 -> Auto, 1 -> Not Auto
    
    failureHandler parameters:
        error: The reason of failure.
*/
- (void) getAutoExposureWithUsername:(NSString *) username andPassword:(NSString *) password completionHandler:(void (^)(NSInteger autoExposure)) completionHandler failureHandler:(void (^)(NSError * error)) failureHandler;

/*
    parameters:
        value: 1 ~ 15
        username: The administrator account on iZiggi.
        password: The password of the administrator on iZiggi.
    
    completionHandler parameters:
        none
    
    failureHandler parameters:
        error: The reason of failure.
*/
- (void) setExposure:(NSInteger) value withUsername:(NSString *) username andPassword:(NSString *) password completionHandler:(void (^)(void)) completionHandler failureHandler:(void (^)(NSError * error)) failureHandler;

/*
    parameters:
        username: The administrator account on iZiggi.
        password: The password of the administrator on iZiggi.
    
    completionHandler parameters:
        exposureValue: 1 ~ 15
    
    failureHandler parameters:
        error: The reason of failure.
*/
- (void) getExposureWithUsername:(NSString *) username andPassword:(NSString *) password completionHandler:(void (^)(NSInteger exposureValue)) completionHandler failureHandler:(void (^)(NSError * error)) failureHandler;

/*
    parameters:
        username: The administrator account on iZiggi.
        password: The password of the administrator on iZiggi.
    
    completionHandler parameters:
        afMode: 0 -> AF-Sigle, 1 -> AF-Continuous
    
    failureHandler parameters:
        error: The reason of failure.
*/
- (void) getAutoFocusModeWithUsername:(NSString *) username andPassword:(NSString *) password completionHandler:(void (^)(NSInteger afMode)) completionHandler failureHandler:(void (^)(NSError * error)) failureHandler;

/*
    parameters:
        username: The administrator account on iZiggi.
        password: The password of the administrator on iZiggi.
    
    completionHandler parameters:
        focusStatus: 0 -> normal, 1-> focusing
    
    failureHandler parameters:
        error: The reason of failure.
*/
- (void) getFocusStatusWithUsername:(NSString *) username andPassword:(NSString *) password completionHandler:(void (^)(NSInteger focusStatus)) completionHandler failureHandler:(void (^)(NSError * error)) failureHandler;

/*
    parameters:
        value: 0 -> 60Hz, 1 -> 50Hz
        username: The administrator account on iZiggi.
        password: The password of the administrator on iZiggi.
    
    completionHandler parameters:
        none
    
    failureHandler parameters:
        error: The reason of failure.
*/
- (void) setPowerFrequency:(NSInteger) value withUsername:(NSString *) username andPassword:(NSString *) password completionHandler:(void (^)(void)) completionHandler failureHandler:(void (^)(NSError * error)) failureHandler;

/*
    parameters:
        username: The administrator account on iZiggi.
        password: The password of the administrator on iZiggi.
    
    completionHandler parameters:
        powerFrequency: 0 -> 60Hz, 1 -> 50Hz
    
    failureHandler parameters:
        error: The reason of failure.
*/
- (void) getPowerFrequencyWithUsername:(NSString *) username andPassword:(NSString *) password completionHandler:(void (^)(NSInteger powerFrequency)) completionHandler failureHandler:(void (^)(NSError * error)) failureHandler;

/*
    parameters:
        username: The administrator account on iZiggi.
        password: The password of the administrator on iZiggi.
    
    completionHandler parameters:
        status: A dictionary contains status of Exposure, Focus Mode, Focus Status, Power Frequency, and Auto Exposure.
    
    failureHandler parameters:
        error: The reason of failure.
*/
- (void) getStatusWithUsername:(NSString *) username andPassword:(NSString *) password completionHandler:(void (^)(NSDictionary * status)) completionHandler failureHandler:(void (^)(NSError * error)) failureHandler;


@end
