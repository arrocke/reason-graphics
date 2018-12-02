module TestApp = Graphics.Application({
  type state = {
    renderer: Renderer.t,
    m: Mesh.t
  };

  let setup = () => {
    renderer: Renderer.default(),
    m: Mesh.setVertices(Mesh.create(), [
      Point3.create(0., 0., 0.),
      Point3.create(0., 0.5, 0.),
      Point3.create(0.7, 0.0, 0.)
    ])
  };

  let update = (state, dt) => state;

  let draw = (state) => {
    let m = Renderer.drawMesh(state.renderer, state.m);
    {
      ...state,
      m
    };
  };
});

TestApp.start();