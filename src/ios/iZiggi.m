//
//  BrotherPrinterPlugin.m
//  BrotherPrinterPlugin
//
//  Created by Ye Star on 4/9/16.
//
//

#import <Cordova/CDVAvailability.h>
#import "iZiggi.h"

static NSString* toBase64(NSData* data) {
    SEL s1 = NSSelectorFromString(@"cdv_base64EncodedString");
    SEL s2 = NSSelectorFromString(@"base64EncodedString");
    SEL s3 = NSSelectorFromString(@"base64EncodedStringWithOptions:");
    
    if ([data respondsToSelector:s1]) {
        NSString* (*func)(id, SEL) = (void *)[data methodForSelector:s1];
        return func(data, s1);
    } else if ([data respondsToSelector:s2]) {
        NSString* (*func)(id, SEL) = (void *)[data methodForSelector:s2];
        return func(data, s2);
    } else if ([data respondsToSelector:s3]) {
        NSString* (*func)(id, SEL, NSUInteger) = (void *)[data methodForSelector:s3];
        return func(data, s3, 0);
    } else {
        return nil;
    }
}

@interface iZiggi()

@property (retain) NSString* callbackId;
@property (retain) NSString* pickCallbackId;

@property (nonatomic, strong) NSArray * cameras;
@property (nonatomic, strong) ICCamera * camera;
@property (nonatomic, strong) NSArray * resolutions;
@property (nonatomic, strong) NSString * currentResolution;
@property (nonatomic, strong) NSString * eventName;
@property (nonatomic, strong) ViewController *controller;

@end

@implementation iZiggi

- (void)dealloc
{
    
}

/*
 *  pluginInitialize
 */
- (void)pluginInitialize
{
}

- (void)onAppTerminate
{
   
}

- (void)init_iZiggi:(CDVInvokedUrlCommand*)command
{
    NSLog(@"pluginInitialize");
    [ICCameraManager sharedManager];
    
    CDVPluginResult* pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK];
    
    [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
}

- (void)getCameraList:(CDVInvokedUrlCommand*)command
{
    self.cameras = [ICCameraManager sharedManager].cameras;
    NSMutableArray *returnArray = [[NSMutableArray alloc] init];
    
    for(int i=0; i<self.cameras.count; i++)
    {
        ICCamera * camera = self.cameras[i];
        NSDictionary *dic = @{
         @"instanceName": camera.instanceName,
         @"model": camera.model,
         @"active": @(camera.active),
         @"uuid": camera.uuid
         };
        [returnArray addObject:dic];
    }
    
    CDVPluginResult* pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsArray:returnArray];
    
    [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
}

- (void)selectCameraByIndex:(CDVInvokedUrlCommand*)command
{
    NSArray *arguments = [command arguments];
    self.callbackId = command.callbackId;
    __block int index = [[arguments objectAtIndex:0] intValue];
    self.eventName = [arguments objectAtIndex:1];

    
    if(self.cameras.count <=0)
    {
        CDVPluginResult* pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR];
        [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
        
        //self.imageView.image = [UIImage imageWithCIImage:image];
        return;
    }
    
    if(self.camera)
        [[ICCameraStreamProxy sharedProxy] removeStreamObserver:self forCamera:self.camera];
    
    self.camera = self.cameras[index];
    
    [[ICCameraStreamProxy sharedProxy] addStreamObserver:self forCamera:self.cameras[index]];
    
    CDVPluginResult* pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK];
    [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
    
    //self.focusButtonItem.enabled = NO;
    //self.resolutionButtonItem.enabled = NO;
    
    if ([self.camera isKindOfClass:[ICNetCamera class]]) {
        __weak ICNetCamera * netCamera = (ICNetCamera *) self.camera;
        __weak iZiggi * myself = self;

        [netCamera getSupportedResolutionsWithUsername:@"Admin" andPassword:@"admin" completionHandler:^(NSArray *resolutions) {
            [netCamera getCurrentResolutionWithUsername:@"Admin" andPassword:@"admin" completionHandler:^(NSString *resolution) {
                self.resolutions = [resolutions sortedArrayUsingComparator:^NSComparisonResult(id obj1, id obj2) {
                    return [[obj2 objectForKey:@"resolution"] compare:[obj1 objectForKey:@"resolution"] options:NSNumericSearch];
                }];
                myself.currentResolution = resolution;
                
            } failureHandler:^(NSError *error) {
            }];
            
        } failureHandler:^(NSError *error) {
        }];
    }
}

- (void)getResolutions:(CDVInvokedUrlCommand*)command
{
    CDVPluginResult* pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsArray:self.resolutions];
    
    [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
}

- (void)selectResolution:(CDVInvokedUrlCommand*)command
{
    NSArray *arguments = [command arguments];
    
    __block int index = [[arguments objectAtIndex:0] intValue];
    
    NSString * resolution = [[self.resolutions objectAtIndex:index][@"resolution"] stringByTrimmingCharactersInSet:[NSCharacterSet characterSetWithCharactersInString:@" "]];
    
    if ([self.camera isKindOfClass:[ICNetCamera class]]) {
        __weak iZiggi * myself = self;
        [(ICNetCamera *) self.camera setResolution:resolution withUsername:@"Admin" andPassword:@"admin" completionHandler:^(NSString *resolution) {
            NSLog(@"resolution changed");
            myself.currentResolution = resolution;
            
            CDVPluginResult* pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK];
            
            [myself.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
            
        } failureHandler:^(NSError *error) {
            CDVPluginResult* pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR];
            [myself.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
        }];
    }
}

- (void)focus:(CDVInvokedUrlCommand*)command
{
    //[self.controller focus:nil];
    if ([self.camera isKindOfClass:[ICNetCamera class]]) {
        __weak iZiggi * myself = self;

        [(ICNetCamera *) self.camera startFocusingWithUsername:@"Admin" andPassword:@"admin" completionHandler:^{
            CDVPluginResult* pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK];
            [myself.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
        } failureHandler:^(NSError *error) {
            CDVPluginResult* pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR];
            [myself.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
        }];
    }
    else
    {
        CDVPluginResult* pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR];
        [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
    }
}

- (void)pick:(CDVInvokedUrlCommand*)command
{
    ICImagePickerController * imagePicker = [[ICImagePickerController alloc] init];
    imagePicker.delegate = self;
    [self.viewController presentViewController:imagePicker animated:YES completion:^{
    }];
    
    self.pickCallbackId = command.callbackId;
    //CDVPluginResult* pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK];
    
    //[self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
}

- (void)fireEvent:(NSString *)eventName data:(NSString*)data
{
    NSDictionary *dic = @{@"image":data};
    NSError *error;
    NSData *jsonData = [NSJSONSerialization dataWithJSONObject:dic
                                                       options:(NSJSONWritingOptions)0
                                                         error:&error];
    
    NSString *jsonDataString = [[NSString alloc] initWithData:jsonData encoding:NSUTF8StringEncoding];
    NSString *func = [NSString stringWithFormat:@"window.iziggi.fireEvent('%@', %@);", eventName, jsonDataString];
    
    [self.commandDelegate evalJs:func];
}

#pragma mark - ICCaptureSteramProxyDelegate
- (void)cameraStreamProxy:(ICCameraStreamProxy *)cameraStreamProxy didReceiveFrame:(CIImage *)image fromCamera:(ICCamera *)camera
{
    __block NSData* data = nil;
    __typeof(self) __weak weakSelf = self;
    //
    dispatch_async(dispatch_get_main_queue(), ^{
        //self.imageView.image = [UIImage imageWithCIImage:image];
        CIContext *context = [CIContext contextWithOptions:nil];
        UIImage * returnImage;
        CGImageRef processedCGImage = [context createCGImage:image fromRect:[image extent]];
        returnImage = [UIImage imageWithCGImage:processedCGImage];
        CGImageRelease(processedCGImage);
        data = UIImageJPEGRepresentation(returnImage, 0.8);
        __typeof(self) __strong strongSelf = weakSelf;
        [strongSelf fireEvent:self.eventName data:toBase64(data)];
        
    });
}

#pragma mark - ICCameraViewControllerDelegate
- (void) imagePickerController:(ICImagePickerController *)imagePickerController didFinishPickingImage:(UIImage *)image
{
    [imagePickerController dismissViewControllerAnimated:YES completion:^{
        NSData *data = UIImageJPEGRepresentation(image, 0.8);
        //[self fireEvent:self.eventName data:toBase64(data)];
        //UIImage * myImage = [UIImage imageNamed: @"christmas.jpg"];
        //NSData *data = UIImageJPEGRepresentation(myImage, 0.5);
        CDVPluginResult* pluginResult =  [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsString:toBase64(data)];
        [self.commandDelegate sendPluginResult:pluginResult callbackId:self.pickCallbackId];
    }];
}

- (void) imagePickerControllerDidCancel:(ICImagePickerController *)imagePickerController
{
    [imagePickerController dismissViewControllerAnimated:YES completion:^{
        
    }];
}
@end
