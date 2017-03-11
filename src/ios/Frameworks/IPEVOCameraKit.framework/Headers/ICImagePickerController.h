//
//  ICImagePickerController.h
//  IPEVOCameraKit
//
//  Created by Kevin on 2014/12/29.
//  Copyright (c) 2014 IPEVO Inc. All rights reserved.
//

#import <UIKit/UIKit.h>

@protocol ICImagePickerControllerDelegate;

@interface ICImagePickerController : UINavigationController

@property (nonatomic, weak) id<ICImagePickerControllerDelegate, UINavigationControllerDelegate> delegate;

@end

@protocol ICImagePickerControllerDelegate <NSObject, UINavigationControllerDelegate>

@optional
- (void) imagePickerController:(ICImagePickerController *) imagePickerController didFinishPickingImage:(UIImage *)image;
- (void) imagePickerControllerDidCancel:(ICImagePickerController *)imagePickerController;
@end