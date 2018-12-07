/* The mesh type. */
type t;

let create: (GL.context, ~vertices: list(Point3.t)=?, ~normals: list(Vector3.t)=?, ~indices: list(int)=?, unit) => t;

let addVertex: (t, Point3.t) => t;

let setVertices: (t, list(Point3.t)) => t;

let addIndex: (t, int) => t;

let setIndices: (t, list(int)) => t;

let addNormal: (t, Vector3.t) => t;

let setNormals: (t, list(Vector3.t)) => t;

let draw: (t, ShaderProgram.t) => t;