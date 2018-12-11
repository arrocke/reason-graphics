/* The 3d point type. */
type t;

let create: (float, float, float) => t;

let x: t => float;
let y: t => float;
let z: t => float;

let dot: (t, t) => float;
let cross: (t, t) => t;

let len: t => float;
let unit: t => t;