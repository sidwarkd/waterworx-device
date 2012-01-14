var Devices = [];

var SprinklerDevice = function(deviceID, firmwareVersion){
  this.did = deviceID;
  this.fw = firmwareVersion;
};

SprinklerDevice.prototype = {
  getDeviceID: function(){
    return this.did;
  },
  
  getFirmwareVersion: function(){
    return this.fw;
  }
};

$(document).ready(function(){

  var did = $("#did"),
    fw = $("#fw");
    
  $("#new-device-button").click(function(){
    $("#dialog-form").dialog("open");
  });
  
  $( "#dialog-form" ).dialog({
			autoOpen: false,
			height: 280,
			width: 350,
			modal: true,
			buttons: {
				"Create Device": function() {

					Devices.push(new SprinklerDevice(did.val(), fw.val()));
          $("#device-view").append("<div><h2></h2>Device ID: " + did.val() + "<br/>Firmware: v" + fw.val() + "</div>");
					$( this ).dialog( "close" );
					
				},
				Cancel: function() {
					$( this ).dialog( "close" );
				}
			},
			close: function() {
				allFields.val( "" ).removeClass( "ui-state-error" );
			}
		});
});
