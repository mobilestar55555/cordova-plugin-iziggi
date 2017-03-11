//
//  ViewController.h
//  IPEVOCameraKitDemo
//
//  Created by Kevin on 2014/11/21.
//  Copyright (c) 2014 IPEVO Inc. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "CamerasViewController.h"
#import "ResolutionSelectorViewController.h"
#import <IPEVOCameraKit/IPEVOCameraKit.h>

@interface ViewController : UIViewController <CamerasViewControllerDelegate, ICCameraStreamProxyDelegate, ResolutionSelectorDelegate, ICImagePickerControllerDelegate>
@property (weak, nonatomic) IBOutlet UIImageView *imageView;
@property (weak, nonatomic) IBOutlet UIBarButtonItem *focusButtonItem;
@property (weak, nonatomic) IBOutlet UIBarButtonItem *resolutionButtonItem;

@property (nonatomic, strong) ICCamera * camera;
@property (nonatomic, strong) NSArray * resolutions;
@property (nonatomic, strong) NSString * currentResolution;

-(void)selectCamera:(ICCamera *) camera;

- (IBAction)focus:(id)sender;
- (IBAction)test:(id)sender;
@end

