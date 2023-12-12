// Get current sensor readings when the page loads  
window.addEventListener('load', getReadings);

// Create Heat Index Celcius Gauge
var gaugeHeatC = new LinearGauge({
  renderTo: 'gauge-heat-index-celcius',
  width: 120,
  height: 400,
  units: "Heat Index (°C)",
  minValue: 0,
  startAngle: 90,
  ticksAngle: 180,
  maxValue: 50,
  colorValueBoxRect: "#049faa",
  colorValueBoxRectEnd: "#049faa",
  colorValueBoxBackground: "#f1fbfc",
  valueDec: 2,
  valueInt: 2,
  majorTicks: [
      "0",
      "5",
      "10",
      "15",
      "20",
      "25",
      "30",
      "35",
      "40",
      "45",
      "50"
  ],
  minorTicks: 4,
  strokeTicks: true,
  highlights: [
      {
          "from": 35,
          "to": 50,
          "color": "rgba(200, 50, 50, .75)"
      }
  ],
  colorPlate: "#fff",
  colorBarProgress: "#CC2936",
  colorBarProgressEnd: "#049faa",
  borderShadowWidth: 0,
  borders: false,
  needleType: "arrow",
  needleWidth: 2,
  needleCircleSize: 7,
  needleCircleOuter: true,
  needleCircleInner: false,
  animationDuration: 1500,
  animationRule: "linear",
  barWidth: 10,
}).draw();

// Create Heat Index Fahrenheit Gauge
var gaugeHeatF = new LinearGauge({
  renderTo: 'gauge-heat-index-fahrenheit',
  width: 120,
  height: 400,
  units: "Heat Index (°F)",
  minValue: 32,
  startAngle: 90,
  ticksAngle: 180,
  maxValue: 122,
  colorValueBoxRect: "#049faa",
  colorValueBoxRectEnd: "#049faa",
  colorValueBoxBackground: "#f1fbfc",
  valueDec: 2,
  valueInt: 2,
  majorTicks: [
      "32",
      "41",
      "50",
      "59",
      "68",
      "77",
      "86",
      "95",
      "104",
      "113",
      "122"
  ],
  minorTicks: 4,
  strokeTicks: true,
  highlights: [
      {
          "from": 95,
          "to": 122,
          "color": "rgba(200, 50, 50, .75)"
      }
  ],
  colorPlate: "#fff",
  colorBarProgress: "#CC2936",
  colorBarProgressEnd: "#049faa",
  borderShadowWidth: 0,
  borders: false,
  needleType: "arrow",
  needleWidth: 2,
  needleCircleSize: 7,
  needleCircleOuter: true,
  needleCircleInner: false,
  animationDuration: 1500,
  animationRule: "linear",
  barWidth: 10,
}).draw();

// Create Temperature Celcius Gauge
var gaugeTempC = new LinearGauge({
  renderTo: 'gauge-temperature-celcius',
  width: 120,
  height: 400,
  units: "Temperature (°C)",
  minValue: 0,
  startAngle: 90,
  ticksAngle: 180,
  maxValue: 50,
  colorValueBoxRect: "#049faa",
  colorValueBoxRectEnd: "#049faa",
  colorValueBoxBackground: "#f1fbfc",
  valueDec: 2,
  valueInt: 2,
  majorTicks: [
      "0",
      "5",
      "10",
      "15",
      "20",
      "25",
      "30",
      "35",
      "40",
      "45",
      "50"
  ],
  minorTicks: 4,
  strokeTicks: true,
  highlights: [
      {
          "from": 35,
          "to": 50,
          "color": "rgba(200, 50, 50, .75)"
      }
  ],
  colorPlate: "#fff",
  colorBarProgress: "#CC2936",
  colorBarProgressEnd: "#049faa",
  borderShadowWidth: 0,
  borders: false,
  needleType: "arrow",
  needleWidth: 2,
  needleCircleSize: 7,
  needleCircleOuter: true,
  needleCircleInner: false,
  animationDuration: 1500,
  animationRule: "linear",
  barWidth: 10,
}).draw();
  
// Create Humidity Gauge
var gaugeHum = new RadialGauge({
  renderTo: 'gauge-humidity',
  width: 300,
  height: 300,
  units: "Humidity (%)",
  minValue: 0,
  maxValue: 100,
  colorValueBoxRect: "#049faa",
  colorValueBoxRectEnd: "#049faa",
  colorValueBoxBackground: "#f1fbfc",
  valueInt: 2,
  majorTicks: [
      "0",
      "20",
      "40",
      "60",
      "80",
      "100"

  ],
  minorTicks: 4,
  strokeTicks: true,
  highlights: [
      {
          "from": 80,
          "to": 100,
          "color": "#03C0C1"
      }
  ],
  colorPlate: "#fff",
  borderShadowWidth: 0,
  borders: false,
  needleType: "line",
  colorNeedle: "#007F80",
  colorNeedleEnd: "#007F80",
  needleWidth: 2,
  needleCircleSize: 3,
  colorNeedleCircleOuter: "#007F80",
  needleCircleOuter: true,
  needleCircleInner: false,
  animationDuration: 1500,
  animationRule: "linear"
}).draw();

// Create Temperature Fahrenheit Gauge
var gaugeTempF = new LinearGauge({
  renderTo: 'gauge-temperature-fahrenheit',
  width: 120,
  height: 400,
  units: "Temperature (°F)",
  minValue: 32,
  startAngle: 90,
  ticksAngle: 180,
  maxValue: 122,
  colorValueBoxRect: "#049faa",
  colorValueBoxRectEnd: "#049faa",
  colorValueBoxBackground: "#f1fbfc",
  valueDec: 2,
  valueInt: 2,
  majorTicks: [
      "32",
      "41",
      "50",
      "59",
      "68",
      "77",
      "86",
      "95",
      "104",
      "113",
      "122"
  ],
  minorTicks: 4,
  strokeTicks: true,
  highlights: [
      {
          "from": 95,
          "to": 122,
          "color": "rgba(200, 50, 50, .75)"
      }
  ],
  colorPlate: "#fff",
  colorBarProgress: "#CC2936",
  colorBarProgressEnd: "#049faa",
  borderShadowWidth: 0,
  borders: false,
  needleType: "arrow",
  needleWidth: 2,
  needleCircleSize: 7,
  needleCircleOuter: true,
  needleCircleInner: false,
  animationDuration: 1500,
  animationRule: "linear",
  barWidth: 10,
}).draw();
  
// Create Smoke Sensor Gauge
var gaugeSmoke = new RadialGauge({
  renderTo: 'gauge-smoke',
  width: 300,
  height: 300,
  units: "Smoke Sensor (ppm)",
  minValue: 0,
  maxValue: 10000,
  colorValueBoxRect: "#FF8700",
  colorValueBoxRectEnd: "#FF8700",
  colorValueBoxBackground: "#FCF6F1",
  valueInt: 2,
  majorTicks: [
      "0",
      "2000",
      "4000",
      "6000",
      "8000",
      "10000"

  ],
  minorTicks: 4,
  strokeTicks: true,
  highlights: [
      {
          "from": 0,
          "to": 2000,
          "color": "#00FFFB"
      },
      {
          "from": 2000,
          "to": 4000,
          "color": "#04FF00"
      },
      {
          "from": 4000,
          "to": 6000,
          "color": "#F7FF00"
      },
      {
        "from": 6000,
        "to": 8000,
        "color": "#FF9700"
      },
      {
          "from": 8000,
          "to": 10000,
          "color": "#FF0000"
      }
  ],
  colorPlate: "#fff",
  borderShadowWidth: 0,
  borders: false,
  needleType: "line",
  colorNeedle: "#800000",
  colorNeedleEnd: "#800000",
  needleWidth: 2,
  needleCircleSize: 3,
  colorNeedleCircleOuter: "#800000",
  needleCircleOuter: true,
  needleCircleInner: false,
  animationDuration: 1500,
  animationRule: "linear"
}).draw();

// Create Temperature Fahrenheit Gauge
var gaugePressure = new LinearGauge({
  renderTo: 'gauge-pressure',
  width: 120,
  height: 400,
  units: "Pressure (hPa)",
  minValue: 500,
  startAngle: 90,
  ticksAngle: 180,
  maxValue: 1500,
  colorValueBoxRect: "#049faa",
  colorValueBoxRectEnd: "#049faa",
  colorValueBoxBackground: "#f1fbfc",
  valueDec: 2,
  valueInt: 2,
  majorTicks: [
      "500",
      "600",
      "700",
      "800",
      "900",
      "1000",
      "1100",
      "1200",
      "1300",
      "1400",
      "1500"
  ],
  minorTicks: 4,
  strokeTicks: true,
  highlights: [
      {
          "from": 1200,
          "to": 1500,
          "color": "rgba(50, 145, 199, 0.75)"
      }
  ],
  colorPlate: "#fff",
  colorBarProgress: "#CC2936",
  colorBarProgressEnd: "#049faa",
  borderShadowWidth: 0,
  borders: false,
  needleType: "arrow",
  needleWidth: 2,
  needleCircleSize: 7,
  needleCircleOuter: true,
  needleCircleInner: false,
  animationDuration: 1500,
  animationRule: "linear",
  barWidth: 10,
}).draw();

// Create Smoke Sensor Gauge
var gaugeLight = new RadialGauge({
  renderTo: 'gauge-light',
  width: 300,
  height: 300,
  units: "Light Sensor (lux)",
  minValue: 0,
  maxValue: 150,
  colorValueBoxRect: "#FF8700",
  colorValueBoxRectEnd: "#FF8700",
  colorValueBoxBackground: "#FCF6F1",
  valueInt: 2,
  majorTicks: [
      "0",
      "30",
      "60",
      "90",
      "120",
      "150"
  ],
  minorTicks: 4,
  strokeTicks: true,
  highlights: [
      {
        "from": 0,
        "to": 30,
        "color": "#5A5A5A"
      },
      {
        "from": 30,
        "to": 60,
        "color": "#A7A7A7"
      },
      {
        "from": 60,
        "to": 90,
        "color": "#D6D6D6"
      },
      {
        "from": 90,
        "to": 120,
        "color": "#E8E8E8"
      },
      {
        "from": 120,
        "to": 150,
        "color": "#FFFFFF"
      }
  ],
  colorPlate: "#fff",
  borderShadowWidth: 0,
  borders: false,
  needleType: "line",
  colorNeedle: "#800000",
  colorNeedleEnd: "#800000",
  needleWidth: 2,
  needleCircleSize: 3,
  colorNeedleCircleOuter: "#800000",
  needleCircleOuter: true,
  needleCircleInner: false,
  animationDuration: 1500,
  animationRule: "linear"
}).draw();

// Create PIR Sensor Reading


// Create LDR Sensor Reading


// Function to get current readings on the webpage when it loads for the first time
function getReadings(){
  var xhr = new XMLHttpRequest();
  xhr.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      var myObj = JSON.parse(this.responseText);
      console.log(myObj);
      var heatC = myObj.heatIndexC;
      var heatF = myObj.heatIndexF;
      var tempC = myObj.temperatureC;
      var hum = myObj.humidity;
      var tempF = myObj.temperatureF;
      var smoke = myObj.smoke_sensor;
      var pressure = myObj.pressure_sensor;
      var light = myObj.LDR;
      // var isPIR = myObj.PIR_sensor;
      // var isFire = myObj.fire_sensor;
      gaugeHeatC = heatC;
      gaugeHeatF = heatF;
      gaugeTempC.value = tempC;
      gaugeHum.value = hum;
      gaugeTempF.value = tempF;
      gaugeSmoke.value = smoke;
      gaugePressure.value = pressure;
      gaugeLight.value = light;
      // gaugePIR.value = PIR;
      // gaugeFire.value = fire;
    }
  }; 
  xhr.open("GET", "/readings", true);
  xhr.send();
}

if (!!window.EventSource) {
  var source = new EventSource('/events');
  
  source.addEventListener('open', function(e) {
    console.log("Events Connected");
  }, false);

  source.addEventListener('error', function(e) {
    if (e.target.readyState != EventSource.OPEN) {
      console.log("Events Disconnected");
    }
  }, false);
  
  source.addEventListener('message', function(e) {
    console.log("message", e.data);
  }, false);
  
  source.addEventListener('new_readings', function(e) {
    console.log("new_readings", e.data);
    var myObj = JSON.parse(e.data);
    console.log(myObj);
    gaugeHeatC.value = myObj.heatIndexC;
    gaugeHeatF.value = myObj.heatIndexF;
    gaugeTempC.value = myObj.temperatureC;
    gaugeHum.value = myObj.humidity;
    gaugeTempF.value = myObj.temperatureF;
    gaugeSmoke.value = myObj.smoke_sensor;
    gaugePressure.value = myObj.pressure_sensor;
    gaugeLight.value = myObj.LDR;
    // gaugePIR.value = myObj.PIR_sensor;
    // gaugeFire.value = myObj.fire_sensor;
  }, false);
}
