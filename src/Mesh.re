type typedarray;

type t = {
  vertices: list(Point3.t),
  vertexCount: int,
  vertexBuffer: GLInterface.buffer,
  dirty: bool
};


let create = () => {
  vertices: [],
  vertexCount: 0,
  vertexBuffer: GLInterface.createBuffer(Canvas.context),
  dirty: true
};

let addVertex = (mesh, vert) => {
  ...mesh,
  vertexCount: mesh.vertexCount + 1,
  vertices: [vert, ...mesh.vertices],
  dirty: true
};

let setVertices = (mesh, vertices) => {
  ...mesh,
  vertexCount: List.length(vertices),
  vertices,
  dirty: true
}

let updateGL = (mesh, program) => {
  GLInterface.bindBuffer(Canvas.context, GLConsts.arrayBuffer, mesh.vertexBuffer);
  let vertexArray = List.fold_left(
    (verts, v) => [Point3.z(v), Point3.y(v), Point3.x(v), ...verts],
    [], mesh.vertices)
    |> List.rev |> Array.of_list |> GLInterface.createTypedArray;
  GLInterface.bufferData(Canvas.context, GLConsts.arrayBuffer, vertexArray, GLConsts.staticDraw);
  let vertexAttrib = ShaderProgram.getAttrib(program, "a_position");
  GLInterface.enableVertexAttribArray(Canvas.context, vertexAttrib);
  GLInterface.bindBuffer(Canvas.context, GLConsts.arrayBuffer, mesh.vertexBuffer);
  GLInterface.vertexAttribPointer(Canvas.context, vertexAttrib, 3, GLConsts.float, false, 0, 0);
  {
    ...mesh,
    dirty: true
  }
};

let draw = (mesh, program) => {
  let updatedMesh = 
    if (mesh.dirty) {
      updateGL(mesh, program);
    } else {
      mesh;
    }
  GLInterface.drawArrays(Canvas.context, GLConsts.triangles, 0, mesh.vertexCount);
  updatedMesh;
}