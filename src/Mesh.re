type typedarray;

type t = {
  vertices: list(Point3.t),
  vertexCount: int,
  vertexBuffer: GLTypes.buffer,
  mutable dirty: bool
};

[@bs.send] external createBuffer : (GLTypes.context) => GLTypes.buffer = "createBuffer";
[@bs.send] external bindBuffer : (GLTypes.context, int, GLTypes.buffer) => unit = "bindBuffer";
[@bs.send] external bufferData : (GLTypes.context, int, typedarray, int) => unit = "bufferData";
[@bs.send] external drawArrays : (GLTypes.context, int, int, int) => unit = "drawArrays";
[@bs.new] external createTypedArray : (array(float)) => typedarray = "Float32Array"
[@bs.send] external enableVertexAttribArray : (GLTypes.context, GLTypes.attrib) => unit = "enableVertexAttribArray";
[@bs.send] external vertexAttribPointer : (GLTypes.context, GLTypes.attrib, int, int, bool, int, int) => unit = "vertexAttribPointer";

let create = () => {
  vertices: [],
  vertexCount: 0,
  vertexBuffer: createBuffer(Canvas.context),
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
  bindBuffer(Canvas.context, GLConsts.arrayBuffer, mesh.vertexBuffer);
  let vertexArray = List.fold_left(
    (verts, v) => [Point3.y(v), Point3.x(v), ...verts],
    [], mesh.vertices)
    |> List.rev |> Array.of_list |> createTypedArray;
  bufferData(Canvas.context, GLConsts.arrayBuffer, vertexArray, GLConsts.staticDraw);
  let vertexAttrib = ShaderProgram.getAttrib(program, "a_position");
  enableVertexAttribArray(Canvas.context, vertexAttrib);
  bindBuffer(Canvas.context, GLConsts.arrayBuffer, mesh.vertexBuffer);
  vertexAttribPointer(Canvas.context, vertexAttrib, 2, GLConsts.float, false, 0, 0);
  mesh.dirty = false
};

let draw = (mesh, program) => {
  if (mesh.dirty) {
    updateGL(mesh, program);
  }
  drawArrays(Canvas.context, GLConsts.triangles, 0, mesh.vertexCount);
}