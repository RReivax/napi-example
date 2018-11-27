const promaths = require("./build/Release/promaths")

promaths.double_it(3, function (res) {
  console.log(res); //outputs 6
});