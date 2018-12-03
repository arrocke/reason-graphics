type t;

let identity: t;

let translation: (float, float, float) => t;
let scale: (float, float, float) => t;
let rotationX: (float) => t;
let rotationY: (float) => t;
let rotationZ: (float) => t;
let rotation: (float, float, float, float) => t;
let perspective: (float, float, float, float) => t;

let multiply: (t, t) => t;
let inverse: (t) => t;
let transpose: (t) => t;

let at: (t, int, int) => float;

let array_of_matrix: t => array(float);