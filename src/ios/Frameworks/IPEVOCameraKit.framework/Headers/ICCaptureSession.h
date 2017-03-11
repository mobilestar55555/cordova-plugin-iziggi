//
//  ICCaptureSession.h
//  IPEVOCameraKit
//
//  Created by Kevin on 2014/10/29.
//  Copyright (c) 2014 IPEVO Inc. All rights reserved.
//

//#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "ICNetCamera.h"

#define ICNotificationCaptureSessionWillRestart @"CaptureSessionWillRestart"

@protocol ICCaptureSessionDelegate;

@interface ICCaptureSession : NSObject <NSNetServiceDelegate>
@property (nonatomic, strong, readonly) ICCamera * camera;
@property (nonatomic, weak) id<ICCaptureSessionDelegate> delegate;
@property (nonatomic, assign) BOOL isRunning;
@property (nonatomic, assign) CGFloat fps;

- (ICCaptureSession *) initWithCamera:(ICCamera *) camera;

- (void) startRunning;
- (void) stopRunning;

- (CALayer *) createDisplayLayer;

@end

@protocol ICCaptureSessionDelegate <NSObject>

- (void) captureSession:(ICCaptureSession *) captureSession didCaptureImage:(CIImage *) image;

@end