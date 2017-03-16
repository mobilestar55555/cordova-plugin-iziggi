cordova.define("cordova-plugin-iziggi.iziggi", function(require, exports, module) {
var exec = require('cordova/exec');
var channel = require('cordova/channel');

module.exports = {

    _channels: {},
    createEvent: function(type, data) {
        var event = document.createEvent('Event');
        event.initEvent(type, false, false);
        if (data) {
            for (var i in data) {
                if (data.hasOwnProperty(i)) {
                    event[i] = data[i];
                }
            }
        }
        return event;
    },

    init_iZiggi: function (success, error) {
        exec(success, error, "iZiggi", "init_iZiggi", null);
    },
        
    getCameraList: function (success, error) {
        exec(success, error, "iZiggi", "getCameraList", null);
    },
        
    /*selectCameraByIndex: function (index, success, error) {
        exec(success, error, "iZiggi", "selectCameraByIndex", [index]);
    },*/
        
    getResolutions: function (success, error) {
        exec(success, error, "iZiggi", "getResolutions", null);
    },
        
    selectResolution: function (index, success, error) {
        exec(success, error, "iZiggi", "selectResolution", [index]);
    },

   fireEvent: function (type, data) {
       var event = this.createEvent( type, data);
       if (event && (event.type in this._channels)) {
           this._channels[event.type].fire(event);
       }
   },
               
    selectCameraByIndex: function (index, eventname, f) {
        if (!(eventname in this._channels)) {
            var me = this;
            exec( function() {
                me._channels[eventname] = channel.create(eventname);
                me._channels[eventname].subscribe(f);
                }, function(err)  {
                }, "iZiggi", "selectCameraByIndex", [index, eventname]);
        }
        else {
            this._channels[eventname].subscribe(f);
        }
    },
                   
    pick: function (success, error) {
        exec(success, error, "iZiggi", "pick", null);
    },
                   
    focus: function (success, error) {
        exec(success, error, "iZiggi", "focus", null);
    },
    
   removeCamera: function (success, error) {
       exec(success, error, "iZiggi", "removeCamera", null);
   },
   
    };
});
