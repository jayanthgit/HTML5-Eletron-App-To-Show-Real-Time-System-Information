angular.module('app').factory("deviceDataService", ['$rootScope', function ($rootScope) {
   
    const worker = require("streaming-worker");
    const through = require('through');
    const path = require("path");

    const addon_path = path.join(__dirname, "../NativeCode/build/Release/sensor_sim");
    const wobbly_sensor = worker(addon_path, { name: "System Data" });

    function startMonitoring() {
        wobbly_sensor.from.on('systemData', function (data) {
            $rootScope.$broadcast("deviceSystemDataChangedEvent", data);                    
        });

        wobbly_sensor.from.on('log', function (data) {
            console.log(data);        
        });
    };

    return {
        startMonitoring: startMonitoring
    };
}
]);