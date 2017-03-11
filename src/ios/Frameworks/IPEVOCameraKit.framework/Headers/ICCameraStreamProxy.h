//
//  ICCameraStreamProxy.h
//  IPEVOCameraKit
//
//  Created by Kevin on 2014/11/21.
//  Copyright (c) 2014 IPEVO Inc. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <QuartzCore/QuartzCore.h>
#import <CoreImage/CoreImage.h>
#import "ICCaptureSession.h"

@protocol ICCameraStreamProxyDelegate;

@interface ICCameraStreamProxy : NSObject <ICCaptureSessionDelegate>

+ (instancetype) sharedProxy;

- (void) addStreamObserver:(id<ICCameraStreamProxyDelegate>) observer forCamera:(ICCamera *) camera;
- (void) removeStreamObserver:(id) observer forCamera:(ICCamera *) camera;
- (ICCaptureSession *) captureSessionForCamera:(ICCamera *) camera;

@end

@protocol ICCameraStreamProxyDelegate <NSObject>

- (void) cameraStreamProxy:(ICCameraStreamProxy *) cameraStreamProxy didReceiveFrame:(CIImage *) image fromCamera:(ICCamera *) camera;

@end