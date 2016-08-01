"use strict";

angular.module("app").directive("systemMonitor", function () {
    return {
        controller: 'systemMonitorController',
        templateUrl: "app/systemMonitorControl/systemMonitorTemplate.html",
        link: function (scope, el, attr, ctrl) {
            console.log("inside link function")
        }
    };
});

