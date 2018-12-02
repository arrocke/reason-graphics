/* The mesh type. */
type t;

let create: unit => t;

let addVertex: (t, Point3.t) => t;

let setVertices: (t, list(Point3.t)) => t;

let draw: (t, ShaderProgram.t) => t;