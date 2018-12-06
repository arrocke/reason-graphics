type t;

/**
 * Get the aspect ratio of a canvase element.
 */
let aspectRatio: t => float;

/**
 * Create a fullscreen canvas element.
 */
let create: unit => t;

/**
 * Find a canvas element by its CSS selector.
 */
let find: string => option(t);

/**
 * Get a WebGL context from a canvas element.
 */
let getContext: t => GL.context;

/**
 * Get the height of a canvas element..
 */
let height: t => int;

/**
 * Resize a canvas' drawing dimensions to match the element's size.
 */
let resize: t => unit;

/**
 * Get the width of a canvas element.
 */
let width: t => int;