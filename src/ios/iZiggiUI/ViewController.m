//
//  ViewController.m
//  IPEVOCameraKitDemo
//
//  Created by Kevin on 2014/11/21.
//  Copyright (c) 2014 IPEVO Inc. All rights reserved.
//

#import "ViewController.h"

@interface ViewController () {
}

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    // Get the new view controller using [segue destinationViewController].
    // Pass the selected object to the new view controller.
    if ([segue.destinationViewController isKindOfClass:[CamerasViewController class]]) {
        ((CamerasViewController *) segue.destinationViewController).delegate = self;
    } else if ([segue.destinationViewController isKindOfClass:[ResolutionSelectorViewController class]]) {
        NSInteger selectionIndex = NSNotFound;
        NSInteger index = -1;
        for (NSDictionary * resolutionDict in self.resolutions) {
            index++;
            if ([[resolutionDict[@"resolution"] stringByTrimmingCharactersInSet:[NSCharacterSet characterSetWithCharactersInString:@" "]] isEqualToString:self.currentResolution]) {
                selectionIndex = index;
                break;
            }
        }
        ((ResolutionSelectorViewController *) segue.destinationViewController).delegate = self;
        ((ResolutionSelectorViewController *) segue.destinationViewController).resolutions = self.resolutions;
        ((ResolutionSelectorViewController *) segue.destinationViewController).selectionIndex = selectionIndex;
    }
}

- (IBAction)focus:(id)sender {
    if ([self.camera isKindOfClass:[ICNetCamera class]]) {
        [(ICNetCamera *) self.camera startFocusingWithUsername:@"Admin" andPassword:@"admin" completionHandler:^{
            
        } failureHandler:^(NSError *error) {
            
        }];
    }
}

- (IBAction)test:(id)sender {
    ICImagePickerController * imagePicker = [[ICImagePickerController alloc] init];
    imagePicker.delegate = self;
    [self presentViewController:imagePicker animated:YES completion:^{
        
    }];
}

-(void)selectCamera:(ICCamera *) camera
{
    NSLog(@"%@", camera);
    [[ICCameraStreamProxy sharedProxy] removeStreamObserver:self forCamera:self.camera];
    self.camera = camera;
    [[ICCameraStreamProxy sharedProxy] addStreamObserver:self forCamera:camera];
    self.focusButtonItem.enabled = NO;
    self.resolutionButtonItem.enabled = NO;
    
    if ([self.camera isKindOfClass:[ICNetCamera class]]) {
        __weak ICNetCamera * netCamera = (ICNetCamera *) self.camera;
        __weak ViewController * myself = self;
        [netCamera getSupportedResolutionsWithUsername:@"Admin" andPassword:@"admin" completionHandler:^(NSArray *resolutions) {
            [netCamera getCurrentResolutionWithUsername:@"Admin" andPassword:@"admin" completionHandler:^(NSString *resolution) {
                myself.resolutions = [resolutions sortedArrayUsingComparator:^NSComparisonResult(id obj1, id obj2) {
                    return [[obj2 objectForKey:@"resolution"] compare:[obj1 objectForKey:@"resolution"] options:NSNumericSearch];
                }];
                myself.currentResolution = resolution;
                myself.focusButtonItem.enabled = YES;
                myself.resolutionButtonItem.enabled = YES;
            } failureHandler:^(NSError *error) {
                
            }];
        } failureHandler:^(NSError *error) {
            
        }];
    }
}

#pragma mark - CamerasViewControllerDelegate

- (void) camerasViewController:(CamerasViewController *) viewController didSelectCamera:(ICCamera *) camera
{
    [self selectCamera:camera];
}

#pragma mark - ICCaptureSteramProxyDelegate
- (void)cameraStreamProxy:(ICCameraStreamProxy *)cameraStreamProxy didReceiveFrame:(CIImage *)image fromCamera:(ICCamera *)camera
{
    dispatch_async(dispatch_get_main_queue(), ^{
        self.imageView.image = [UIImage imageWithCIImage:image];
    });
}

#pragma mark - ResolutionSelectorDelegate
- (void) resolutionSelector:(ResolutionSelectorViewController *) selector didSelectResolutionAtIndex:(NSInteger) index;
{
    NSString * resolution = [[self.resolutions objectAtIndex:index][@"resolution"] stringByTrimmingCharactersInSet:[NSCharacterSet characterSetWithCharactersInString:@" "]];
    if ([self.camera isKindOfClass:[ICNetCamera class]]) {
        __weak ViewController * myself = self;
        [(ICNetCamera *) self.camera setResolution:resolution withUsername:@"Admin" andPassword:@"admin" completionHandler:^(NSString *resolution) {
            NSLog(@"resolution changed");
            myself.currentResolution = resolution;
        } failureHandler:^(NSError *error) {
            
        }];
    }
}

#pragma mark - ICCameraViewControllerDelegate
- (void) imagePickerController:(ICImagePickerController *)imagePickerController didFinishPickingImage:(UIImage *)image
{
    NSLog(@"%@", image);
    [imagePickerController dismissViewControllerAnimated:YES completion:^{
        
    }];
}

- (void) imagePickerControllerDidCancel:(ICImagePickerController *)imagePickerController
{
    [imagePickerController dismissViewControllerAnimated:YES completion:^{
        
    }];
}
@end
