//
//  BrotherPrinterPlugin.h
//  BrotherPrinterPlugin
//
//  Created by Ye Star on 4/9/16.
//
//

#import <Cordova/CDVPlugin.h>
#import <IPEVOCameraKit/IPEVOCameraKit.h>

#import "CamerasViewController.h"
#import "ResolutionSelectorViewController.h"
#import "ViewController.h"


@interface iZiggi : CDVPlugin<ICCameraStreamProxyDelegate, ICImagePickerControllerDelegate>
/*
 AirTurn Support On/Off
 Detect AirTurn connected
 Get Device Name
 Get AirTurn Interface Version
 */
    
- (void)init_iZiggi:(CDVInvokedUrlCommand*)command;
- (void)getCameraList:(CDVInvokedUrlCommand*)command;
- (void)selectCameraByIndex:(CDVInvokedUrlCommand*)command;
    
- (void)getResolutions:(CDVInvokedUrlCommand*)command;
- (void)selectResolution:(CDVInvokedUrlCommand*)command;
    
- (void)pick:(CDVInvokedUrlCommand*)command;
- (void)focus:(CDVInvokedUrlCommand*)command;

@end
