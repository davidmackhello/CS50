
function construct() {


function Car() {}
car1 = new Car();
car2 = new Car();
 
console.log(car1.color);    // undefined
 
Car.prototype.color = null;
console.log(car1.color);    // null
console.log(car2.color);    // null
 
car1.color = "black";
console.log(car1.color);   // black

var coolarray = [7, 11, 420, 666, 69];

console.log(coolarray.length);

}