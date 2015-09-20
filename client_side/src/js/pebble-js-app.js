
var xhrRequest = function (url, type, callback) {
    var xhr = new XMLHttpRequest();
    xhr.onload = function () {
	callback(this.responseText);
    };
    xhr.open(type, url);
    xhr.send();
};

//var pending_request = false;

function getInfo() {
    console.log("getInfo - start");
    // if(pending_request) {
    // 	console.log("getInfo not sending request!");
    // 	return;
    // }

    // console.log("getInfo Sending request!");
    // pending_request = true;
    var url = "http://spring.rutgers.edu:8080/pstockwatchface/interface.json";
    
    xhrRequest(url, 'GET', 
	       function(responseText) {
		   // pending_request = false;
		   var json = JSON.parse(responseText);
		   console.log("getInfo response");
		   
		   var identifier = json.Data[0].identifier;
		   console.log("Identifier is " + identifier);
		   
		   var value = json.Data[0].value;      
		   console.log("Value is " + value);
		   
		   // Assemble dictionary using our keys
		   var dictionary = {
		       "KEY_IDENTIFIER": identifier,
		       "KEY_VALUE": value
		   };
		   
		   Pebble.sendAppMessage(dictionary,
					 function(e) {
					     console.log("Info sent to Pebble successfully!");
					 },
					 function(e) {
					     console.log("Error sending info to Pebble!");
					 }
					);
	       }      
	      );
}

Pebble.addEventListener('ready', 
			function(e) {
			    console.log("PebbleKit JS ready!");
			    getInfo();
			}
		       );

Pebble.addEventListener('appmessage',
			function(e) {
			    console.log("AppMessage received!");
			    getInfo();
			}                     
		       );

