/** The canvas type. */
type t;

/** Find a canvas by its DOM id. */
let findById: (string) => t;

/** Resize a canvas to its client width and height */
let resize: (t) => unit;

/** Get a WebGL rendering context for a canvas. */
let context: (t) => option(GLContext.t);

/** Get the width of the canvas in pixels. */
let width: (t) => int;

/** Get the height of the canvas in pixels. */
let height: (t) => int;