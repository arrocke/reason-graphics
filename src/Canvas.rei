exception WebGLNotSupported;

/** The WebGL context for the canvas. */
let context: GLInterface.context;

/** The width of the canvas in pixels. */
let width: unit => int;

/** The height of the canvas in pixels. */
let height: unit => int;

/** The aspect ratio of the cavnas. */
let aspect: unit => float;

/** Resize a canvas to its client width and height */
let resize: unit => unit;
