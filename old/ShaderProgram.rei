/* Shader program type. */
type t;

/* Create a program with the given vertex shader and fragment shader. */
let create: (string, string) => t;

/* Use a program to render objects. */
let use: t => unit;

let getAttrib: (t, string) => GL.attrib;

let setMatrix4Uniform: (t, string, Matrix.t) => unit;