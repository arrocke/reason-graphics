type t = {
  vertices: list(Point3.t),
  vertexCount: int,
  indices: list(int),
  indexCount: int,
  vertexBuffer: GLInterface.buffer,
  indexBuffer: GLInterface.buffer,
  dirty: bool
};


let create = (~vertices=[], ~indices=[], ()) => {
  vertices: List.rev(vertices),
  vertexCount: List.length(vertices),
  indices: List.rev(indices),
  indexCount: List.length(indices),
  vertexBuffer: GLInterface.createBuffer(Canvas.context),
  indexBuffer: GLInterface.createBuffer(Canvas.context),
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
  vertices: List.rev(vertices),
  dirty: true
};

let addIndex = (mesh, index) => {
  ...mesh,
  indexCount: mesh.indexCount + 1,
  indices: [index, ...mesh.indices],
  dirty: true
};

let setIndices = (mesh, indices) => {
  ...mesh,
  indexCount: List.length(indices),
  indices: List.rev(indices),
  dirty: true
};

let updateGL = (mesh, program) => {
  GLInterface.bindBuffer(Canvas.context, GLConsts.arrayBuffer, mesh.vertexBuffer);

  /* Load vertices */
  let vertexArray = List.fold_left(
    (verts, v) => [Point3.z(v), Point3.y(v), Point3.x(v), ...verts],
    [], mesh.vertices)
    |> List.rev |> Array.of_list |> TypedArray.createFloat32Array;
  GLInterface.bufferData(Canvas.context, GLConsts.arrayBuffer, vertexArray, GLConsts.staticDraw);

  /* Load indices */
  if (mesh.indexCount > 0) {
    let indexArray = mesh.indices |> List.rev |> Array.of_list |> TypedArray.createUint16Array;
    GLInterface.bindBuffer(Canvas.context, GLConsts.elementArrayBuffer, mesh.indexBuffer);
    GLInterface.bufferData(Canvas.context, GLConsts.elementArrayBuffer, indexArray, GLConsts.staticDraw);
  }

  let vertexAttrib = ShaderProgram.getAttrib(program, "position");
  GLInterface.enableVertexAttribArray(Canvas.context, vertexAttrib);
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
  if (updatedMesh.indexCount > 0) {
    GLInterface.bindBuffer(Canvas.context, GLConsts.elementArrayBuffer, updatedMesh.indexBuffer);
    GLInterface.drawElements(Canvas.context, GLConsts.triangles, updatedMesh.indexCount, GLConsts.unsignedShort, 0);
  } else {
    GLInterface.drawArrays(Canvas.context, GLConsts.triangles, 0, updatedMesh.vertexCount);
  }
  updatedMesh;
}