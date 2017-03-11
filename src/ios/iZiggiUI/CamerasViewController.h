//
//  CamerasViewController.h
//  IPEVOCameraKit
//
//  Created by Kevin on 2014/11/21.
//  Copyright (c) 2014 IPEVO Inc. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <IPEVOCameraKit/IPEVOCameraKit.h>

@protocol CamerasViewControllerDelegate;

@interface CamerasViewController : UITableViewController

@property (nonatomic, weak) id<CamerasViewControllerDelegate> delegate;

@end

@protocol CamerasViewControllerDelegate <NSObject>

- (void) camerasViewController:(CamerasViewController *) viewController didSelectCamera:(ICCamera *) camera;

@end