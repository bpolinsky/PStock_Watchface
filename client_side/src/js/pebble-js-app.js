
var xhrRequest = function (url, type, callback) {
  var xhr = new XMLHttpRequest();
  xhr.onload = function () {
    callback(this.responseText);
  };
  xhr.open(type, url);
  xhr.send();
};


function retrieval(meep) {
  var url = "http://spring.rutgers.edu:8080/pstockwatchface/interface.json";

  xhrRequest(url, 'GET', 
    function(responseText) {
      var json = JSON.parse(responseText);

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


function retrievalError(err) {
  console.log("Error requesting info!");
}

function getInfo() {
  navigator.geolocation.getCurrentPosition(	//from example from Pebble's developer website (which still made our hack work surprisingly)
    retrieval,
    retrievalError,
    {timeout: 15000, maximumAge: 60000}
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

