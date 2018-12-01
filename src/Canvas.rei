exception WebGLNotSupported;

/** The WebGL context for the canvas. */
let context: GLTypes.context;

/** The width of the canvas in pixels. */
let width: unit => int;

/** The height of the canvas in pixels. */
let height: unit => int;

/** Resize a canvas to its client width and height */
let resize: unit => unit;
