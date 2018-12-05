module TestApp = Graphics.Application({
  type state = {
    renderer: Renderer.t,
    perspective: Matrix.t,
    m: Mesh.t,
    p: float
  };

  let setup = () => {
    renderer: Renderer.default(),
    perspective: Matrix.perspective(60.0, Canvas.aspect(), 0.1, 50.0),
    m: Mesh.create(
      ~vertices=[
        Point3.create(0., 0., 40.0),
        Point3.create(0., 4.0, 40.0),
        Point3.create(4.0, 0.0, 40.0),
      ],
      ~indices=[
        0, 1, 2
      ],
    ()),
    p: 0.0
  };

  let update = (state, dt) => {
    ...state,
    p: if (state.p >= 15.0) {
      -15.0;
    } else {
      state.p +. dt /. 100.0;
    }
  };

  let draw = (state) => {
    let m = Renderer.drawMesh(state.renderer, Matrix.translation(state.p, 0., 0.), Matrix.translation(0.0, 0.0, -.50.0), state.perspective, state.m);
    {
      ...state,
      m
    };
  };
});

TestApp.start();