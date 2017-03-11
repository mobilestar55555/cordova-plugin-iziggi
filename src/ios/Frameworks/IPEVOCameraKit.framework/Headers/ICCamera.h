//
//  ICCamera.h
//  IPEVOCameraKit
//
//  Created by Kevin on 2014/10/27.
//  Copyright (c) 2014 IPEVO Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#define ICNotificationCameraPropertyDidChange @"CameraPropertyDidChange"

#define ICCameraPropertyKeyBrightness       @"brightness"
#define ICCameraPropertyKeyContrast         @"contrast"
#define ICCameraPropertyKeyGamma            @"gamma"
#define ICCameraPropertyKeyHue              @"hue"
#define ICCameraPropertyKeySaturation       @"saturation"
#define ICCameraPropertyKeySharpness        @"sharpness"
#define ICCameraPropertyKeyExposure         @"exposure"
#define ICCameraPropertyKeyFocus            @"focus"
#define ICCameraPropertyKeyAutoFocus        @"autofocus"
#define ICCameraPropertyKeyResolution       @"resolution"
#define ICCameraPropertyKeyFrequency        @"frequency"
#define ICCameraPropertyKeyAutoWhiteBalance @"autoWhiteBalance"
#define ICCameraPropertyKeyWhiteBalance     @"whiteBalance"
#define ICCameraPropertyKeyAutoExposure     @"autoExposure"

@interface ICCamera : NSObject

@property (nonatomic, strong, readonly) NSString * model;
@property (nonatomic, strong) NSString * instanceName;
@property (nonatomic, assign) BOOL active;
@property (nonatomic, readonly, strong) NSString * uuid;

- (void) setUserObject:(id) object forKey:(NSString *) key;
- (id) getUserObjectForKey:(NSString *) key;

- (void) updateInfo;
- (void) prepareToWork;
- (void) prepareToDetatch;

@end
