type t;

let default: GL.context => t;

let drawMesh: (t, Matrix.t, Matrix.t, Matrix.t, Mesh.t) => Mesh.t;