type t;

let identity: t;

let translation: (float, float, float) => t;
let scale: (float, float, float) => t;
let rotationX: (float) => t;
let rotationY: (float) => t;
let rotationZ: (float) => t;
let rotation: (float, float, float, float) => t;

let at: (t, int, int) => float;