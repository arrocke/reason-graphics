/* The mesh type. */
type t;

let create: (~vertices: list(Point3.t)=?, ~indices: list(int)=?, unit) => t;

let addVertex: (t, Point3.t) => t;

let setVertices: (t, list(Point3.t)) => t;

let addIndex: (t, int) => t;

let setIndices: (t, list(int)) => t;

let draw: (t, ShaderProgram.t) => t;