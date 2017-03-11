//
//  ResolutionSelectorViewController.h
//  IPEVOCameraKit
//
//  Created by Kevin on 2014/11/24.
//  Copyright (c) 2014 IPEVO Inc. All rights reserved.
//

#import <UIKit/UIKit.h>

@protocol ResolutionSelectorDelegate;

@interface ResolutionSelectorViewController : UITableViewController

@property (nonatomic, strong) NSArray * resolutions;
@property (nonatomic, assign) NSInteger selectionIndex;
@property (nonatomic, weak) id<ResolutionSelectorDelegate> delegate;
@end

@protocol ResolutionSelectorDelegate <NSObject>

- (void) resolutionSelector:(ResolutionSelectorViewController *) selector didSelectResolutionAtIndex:(NSInteger) index;

@end