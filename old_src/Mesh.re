type t = {
  vertices: list(Point3.t),
  vertexCount: int,
  normals: list(Vector3.t),
  normalCount: int,
  indices: list(int),
  indexCount: int,
  vertexBuffer: GLInterface.buffer,
  normalsBuffer: GLInterface.buffer,
  indexBuffer: GLInterface.buffer,
  dirty: bool
};


let create = (~vertices=[], ~normals=[], ~indices=[], ()) => {
  vertices: List.rev(vertices),
  vertexCount: List.length(vertices),
  normals: List.rev(normals),
  normalCount: List.length(normals),
  indices: List.rev(indices),
  indexCount: List.length(indices),
  vertexBuffer: GLInterface.createBuffer(Canvas.context),
  normalsBuffer: GLInterface.createBuffer(Canvas.context),
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

let addNormal = (mesh, norm) => {
  ...mesh,
  normalCount: mesh.normalCount + 1,
  normals: [norm, ...mesh.normals],
  dirty: true
};

let setNormal = (mesh, normals) => {
  ...mesh,
  normalCount: List.length(normals),
  normals: List.rev(normals),
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

  /* Load vertices */
  let vertexArray = List.fold_left(
    (verts, v) => [Point3.z(v), Point3.y(v), Point3.x(v), ...verts],
    [], mesh.vertices)
    |> List.rev |> Array.of_list |> TypedArray.createFloat32Array;
  GLInterface.bindBuffer(Canvas.context, GLConsts.arrayBuffer, mesh.vertexBuffer);
  GLInterface.bufferData(Canvas.context, GLConsts.arrayBuffer, vertexArray, GLConsts.staticDraw);

  /* Load normals */
  if (mesh.normalCount > 0) {
    let normalArray = List.fold_left(
      (verts, v) => [Vector3.z(v), Vector3.y(v), Vector3.x(v), ...verts],
    [], mesh.normals)
    |> List.rev |> Array.of_list |> TypedArray.createFloat32Array;
    GLInterface.bindBuffer(Canvas.context, GLConsts.arrayBuffer, mesh.normalsBuffer);
    GLInterface.bufferData(Canvas.context, GLConsts.arrayBuffer, normalArray, GLConsts.staticDraw);
  }

  /* Load indices */
  if (mesh.indexCount > 0) {
    let indexArray = mesh.indices |> List.rev |> Array.of_list |> TypedArray.createUint16Array;
    GLInterface.bindBuffer(Canvas.context, GLConsts.elementArrayBuffer, mesh.indexBuffer);
    GLInterface.bufferData(Canvas.context, GLConsts.elementArrayBuffer, indexArray, GLConsts.staticDraw);
  };

  /* Enable the position attribute. */
  let vertexAttrib = ShaderProgram.getAttrib(program, "position");
  GLInterface.bindBuffer(Canvas.context, GLConsts.arrayBuffer, mesh.vertexBuffer);
  GLInterface.enableVertexAttribArray(Canvas.context, vertexAttrib);
  GLInterface.vertexAttribPointer(Canvas.context, vertexAttrib, 3, GLConsts.float, false, 0, 0);

  /* Enable the normal attribute. */
  if (mesh.normalCount > 0) {
    let normalAttrib = ShaderProgram.getAttrib(program, "normal");
    GLInterface.bindBuffer(Canvas.context, GLConsts.arrayBuffer, mesh.normalsBuffer);
    GLInterface.enableVertexAttribArray(Canvas.context, normalAttrib);
    GLInterface.vertexAttribPointer(Canvas.context, normalAttrib, 3, GLConsts.float, false, 0, 0);
  };

  {
    ...mesh,
    dirty: false
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