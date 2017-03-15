Cordova iZiggi HD
=====================

Cordova Plugin For iZiggi HD Device

IOS
===

INSTALL
========

```javascript
$ cordova create <PATH> [ID [NAME [CONFIG]]] [options]
$ cd <PATH>
$ cordova platform add ios
$ cordova plugin add https://github.com/mobilestar55555/cordova-plugin-iziggi.git
```

### Add Embedded IPEVOCameraKit.framework in Xcode
Please check Embedded IPEVOCameraKit Framework.PNG

USAGE:
======

## From Native to Javascript mobilestar55555

### Javascript

```javascript
/*
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */
var app = {
    // Application Constructor
    initialize: function() {
        document.addEventListener('deviceready', this.onDeviceReady.bind(this), false);
    },

    // deviceready Event Handler
    //
    // Bind any cordova events here. Common events are:
    // 'pause', 'resume', etc.
    onDeviceReady: function() {
        window.iziggi.init_iZiggi(function(data){
            alert("init iziggi success");
        },
        function errorHandler(err){
        console.log(err);
        });

        var initiZiggi = document.getElementById('initiZiggi');
        
        var getCameras = document.getElementById('getCameras');
        var selectCameraByIndex = document.getElementById('selectCameraByIndex');
        var getResolutions = document.getElementById('getResolutions');
        var selectResolution0 = document.getElementById('selectResolution0');
        var selectResolution1 = document.getElementById('selectResolution1');
        var selectResolution2 = document.getElementById('selectResolution2');
        var selectResolution3 = document.getElementById('selectResolution3');
        var selectResolution4 = document.getElementById('selectResolution4');
        var selectResolution5 = document.getElementById('selectResolution5');

        var pick = document.getElementById('pick');
        var focus = document.getElementById('focus');

        selectCameraByIndex.disabled = true;
        getResolutions.disabled = true;
        selectResolution0.disabled = true;
        selectResolution1.disabled = true;
        selectResolution2.disabled = true;
        selectResolution3.disabled = true;
        selectResolution4.disabled = true;
        selectResolution5.disabled = true;

        pick.disabled = true;
        focus.disabled = true;

        getCameras.addEventListener('click', function() {
            window.iziggi.getCameraList(function(data){
                  document.getElementById("camera_list").innerHTML = JSON.stringify(data);
                  selectCameraByIndex.disabled = false;
            },
                                    
            function errorHandler(err){
            console.log(err);
            alert(JSON.stringify(err));

            });
        });
        
        selectCameraByIndex.addEventListener('click', function() {
              window.iziggi.selectCameraByIndex(0,"cameraEvent", function(data){
                var largeImage = document.getElementById('largeImage');
                largeImage.style.display = 'block';
                largeImage.src = "data:image/jpeg;base64," + data.image;
                                                
                getResolutions.disabled = false;
                selectResolution0.disabled = false;
                selectResolution1.disabled = false;
                selectResolution2.disabled = false;
                selectResolution3.disabled = false;
                selectResolution4.disabled = false;
                selectResolution5.disabled = false;

                pick.disabled = false;
                focus.disabled = false;
            });
        });
        
        getResolutions.addEventListener('click', function() {
            window.iziggi.getResolutions(function(data){
                alert("getResolutions success");
                document.getElementById("resolution_list").innerHTML = JSON.stringify(data);
            },
            function errorHandler(err){
                console.log(err);
                alert(JSON.stringify(err));

            });
        });
        
        selectResolution0.addEventListener('click', function() {
            window.iziggi.selectResolution(0, function(data){
                alert("selectResolution success");
            },
            function errorHandler(err){
                console.log(err);
               alert(JSON.stringify(err));
            });
        });
        
        selectResolution1.addEventListener('click', function() {
            window.iziggi.selectResolution(1, function(data){
            alert("selectResolution success");
            },
            function errorHandler(err){
            console.log(err);
            alert(JSON.stringify(err));
            });
        });

        selectResolution2.addEventListener('click', function() {
            window.iziggi.selectResolution(2, function(data){
            alert("selectResolution success");
            },
            function errorHandler(err){
            console.log(err);
            alert(JSON.stringify(err));
            });
        });

        selectResolution3.addEventListener('click', function() {
            window.iziggi.selectResolution(3, function(data){
            alert("selectResolution success");
            },
            function errorHandler(err){
            console.log(err);
            alert(JSON.stringify(err));
            });
        });

        selectResolution4.addEventListener('click', function() {
            window.iziggi.selectResolution(4, function(data){
            alert("selectResolution success");
            },
            function errorHandler(err){
            console.log(err);
            alert(JSON.stringify(err));
            });
        });

        selectResolution5.addEventListener('click', function() {
            window.iziggi.selectResolution(5, function(data){
            alert("selectResolution success");
            },
            function errorHandler(err){
            console.log(err);
            alert(JSON.stringify(err));
            });
        });
        
        pick.addEventListener('click', function() {
            window.iziggi.pick(function(data){
                alert("pick success");
                var largeImage = document.getElementById('largeImage');

                // Unhide image elements
                //
                largeImage.style.display = 'block';
                 document.getElementById("iziggi").innerHTML = JSON.stringify(data);

                // Show the captured photo
                // The inline CSS rules are used to resize the image
                //
                largeImage.src = "data:image/jpeg;base64," + data;
            },
            function errorHandler(err){
            console.log(err);
            });
        });

        focus.addEventListener('click', function() {
            window.iziggi.focus(function(data){
                alert("focus success");
                },
                function errorHandler(err){
                console.log(err);
            });
        });

    },

    // Update DOM on a Received Event
    receivedEvent: function(id) {
        
    }
};

app.initialize();

```
