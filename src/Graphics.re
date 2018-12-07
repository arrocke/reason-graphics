[@bs.val] external requestAnimationFrame : (float => unit) => unit = "";

module Initialize(Options: {
  let canvasSelector: option(string)
}) = {
  exception CanvasNotFound;
  exception WebGLNotSupported;

  /* Find or create a canvas */
  let canvas = switch(Options.canvasSelector) {
  | Some(selector) => switch(Canvas.find(selector)) {
    | Some(canvas) => canvas;
    | None => raise(CanvasNotFound);
    }
  | None => Canvas.create()
  };

  /* Get the context, if supported. */
  let context = switch(Canvas.getContext(canvas)) {
    | Some(ctx) => ctx
    | None => raise(WebGLNotSupported)
    };

  GL.setContext(context);

  /* Load graphics modules. */
  module Point3 = Point3;
  module Vector3 = Vector3;
  module Matrix = Matrix;
  module ShaderProgram = ShaderProgram;
  module Mesh = Mesh;

  /* Start the application with its event loop. */
  let loop = (setup, update, draw) => {
    /* Setup context for rendering. */
    GL.enable(context, GLConsts.cullFace);
    GL.cullFace(context, GLConsts.back);
    GL.enable(context, GLConsts.depthTest);
    Canvas.resize(canvas);
    GL.viewport(context, 0, 0, Canvas.width(canvas), Canvas.height(canvas));

    let startState = setup();

    /* Update method that runs every on every animation frame. */
    let loopStep = (state, dt) => {
      /* Update the simulation. */
      let newState = update(state, dt);

      /* Clear the screen and update the view port. */
      GL.clearColor(context, 0.0, 0.0, 0.0, 1.0);
      GL.clear(context, GLConsts.colorBufferBit lor GLConsts.depthBufferBit);

      draw(newState);
    };

    /* Run application main loop. */
    /* It receives the previous timestamp from the last animation frame. */
    /*   and the current timestamp from the current animation frame. */
    let rec step = (state, lastTimestamp, currentTimestamp) => {
      let newState = loopStep(state, currentTimestamp -. lastTimestamp);
      requestAnimationFrame(step(newState, currentTimestamp));
    };
    /* First frame has zero elapsed time. */
    requestAnimationFrame((currentTimestamp) => {
      let newState = loopStep(startState, 0.0);
      requestAnimationFrame(step(newState, currentTimestamp));
    });
  };
};