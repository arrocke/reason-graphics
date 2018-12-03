module TestApp = Graphics.Application({
  type state = {
    renderer: Renderer.t,
    perspective: Matrix.t,
    m: Mesh.t
  };

  let setup = () => {
    renderer: Renderer.default(),
    perspective: Matrix.perspective(60.0, Canvas.aspect(), 0.1, 50.0),
    m: Mesh.setVertices(Mesh.create(), [
      Point3.create(0., 0., 0.0),
      Point3.create(0., 500.0, 0.0),
      Point3.create(700.0, 0.0, 0.0)
    ])
  };

  let update = (state, dt) => state;

  let draw = (state) => {
    let m = Renderer.drawMesh(state.renderer, Matrix.translation(0.2, 0., 0.), Matrix.translation(0.0, 0.0, -.50.0), state.perspective, state.m);
    {
      ...state,
      m
    };
  };
});

TestApp.start();