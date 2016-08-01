"use strict";

angular.module("app").controller('systemMonitorController', 
                                ['$scope', 'deviceDataService', '$element',
function ($scope, deviceDataService, $element) {

     $scope.$on('deviceSystemDataChangedEvent', function (event, data) {
        $scope.$apply(function () {
            $scope.systemData = data;
        });
     });

     deviceDataService.startMonitoring();
}]);

