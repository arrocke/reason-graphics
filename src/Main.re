type state = {
  renderer: Renderer.t,
  perspective: Matrix.t,
  m: Mesh.t,
  p: float,
  t: float
};

module TestApp = Graphics.Initialize({
  let canvasSelector = None;
});

let startState = {
  renderer: Renderer.default(TestApp.context),
  perspective: Matrix.perspective(60.0, Canvas.aspectRatio(TestApp.canvas), 0.1, 50.0),
  m: Mesh.create(
    TestApp.context,
    ~vertices=[
      Point3.create(0.0, 0.0, 0.0),
      Point3.create(1.0, 0.0, 0.0),
      Point3.create(1.0, 1.0, 0.0),
      Point3.create(0.0, 1.0, 0.0),
      Point3.create(1.0, 0.0, 0.0),
      Point3.create(1.0, 0.0, -.1.0),
      Point3.create(1.0, 1.0, -.1.0),
      Point3.create(1.0, 1.0, 0.0),
      Point3.create(0.0, 0.0, -.1.0),
      Point3.create(1.0, 0.0, -.1.0),
      Point3.create(1.0, 0.0, 0.0),
      Point3.create(0.0, 0.0, 0.0),
      Point3.create(0.0, 0.0, -.1.0),
      Point3.create(0.0, 0.0, 0.0),
      Point3.create(0.0, 1.0, 0.0),
      Point3.create(0.0, 1.0, -.1.0),
      Point3.create(0.0, 1.0, 0.0),
      Point3.create(1.0, 1.0, 0.0),
      Point3.create(1.0, 1.0, -.1.0),
      Point3.create(0.0, 1.0, -.1.0),
      Point3.create(1.0, 0.0, -.1.0),
      Point3.create(0.0, 0.0, -.1.0),
      Point3.create(0.0, 1.0, -.1.0),
      Point3.create(1.0, 1.0, -.1.0),
    ],
    ~indices=[
      0, 2, 1,
      3, 2, 0,
      4, 6, 5,
      7, 6, 4,
      8, 10, 9,
      11, 10, 8,
      12, 14, 13,
      15, 14, 12,
      16, 18, 17,
      19, 18, 16,
      20, 22, 21,
      23, 22, 20
    ],
    ~normals=[
      Vector3.create(0.0, 0.0, 1.0),
      Vector3.create(0.0, 0.0, 1.0),
      Vector3.create(0.0, 0.0, 1.0),
      Vector3.create(0.0, 0.0, 1.0),
      Vector3.create(1.0, 0.0, 0.0),
      Vector3.create(1.0, 0.0, 0.0),
      Vector3.create(1.0, 0.0, 0.0),
      Vector3.create(1.0, 0.0, 0.0),
      Vector3.create(0.0, -.1.0, 0.0),
      Vector3.create(0.0, -.1.0, 0.0),
      Vector3.create(0.0, -.1.0, 0.0),
      Vector3.create(0.0, -.1.0, 0.0),
      Vector3.create(-.1.0, 0.0, 0.0),
      Vector3.create(-.1.0, 0.0, 0.0),
      Vector3.create(-.1.0, 0.0, 0.0),
      Vector3.create(-.1.0, 0.0, 0.0),
      Vector3.create(0.0, 1.0, 0.0),
      Vector3.create(0.0, 1.0, 0.0),
      Vector3.create(0.0, 1.0, 0.0),
      Vector3.create(0.0, 1.0, 0.0),
      Vector3.create(0.0, 0.0, -.1.0),
      Vector3.create(0.0, 0.0, -.1.0),
      Vector3.create(0.0, 0.0, -.1.0),
      Vector3.create(0.0, 0.0, -.1.0),
    ],
  ()),
  p: 0.0,
  t: 0.0
};

let update = (state, dt) => {
  ...state,
  p: if (state.p >= 9.0) {
    -9.0;
  } else {
    state.p +. dt /. 800.0;
  },
  t: state.t +. dt /. 1000.0
};

let draw = (state) => {
  let moveToOrigin = Matrix.translation(-.0.5, -.0.5, 0.5)
  let rot = Matrix.rotation(1.0, 1.0, 1.0, state.t)
  let transMotion = Matrix.translation(state.p, 0.0, 0.0);
  let model = moveToOrigin
    |> Matrix.multiply(rot)
    |> Matrix.multiply(transMotion);
  let m = Renderer.drawMesh(state.renderer, model, Matrix.translation(0.0, 0.0, -.5.0), state.perspective, state.m);
  {
    ...state,
    m
  };
};

TestApp.start(startState, update, draw);