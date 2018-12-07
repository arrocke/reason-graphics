/* Shader program type. */
type t;

/* Create a program with the given vertex shader and fragment shader. */
let create: (string, string) => t;

/* Use a program to render objects. */
let use: t => unit;

/* Get an attribute location for a program. */
let getAttrib: (t, string) => GL.attrib;

/* Set a matrix uniform */
let setMatrixUniform: (t, string, Matrix.t) => unit;