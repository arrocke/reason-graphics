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

  let context = switch(Canvas.getContext(canvas)) {
    | Some(ctx) => ctx
    | None => raise(WebGLNotSupported)
    };

  module Context = {
    let context = context;
  };

  module Matrix = Matrix;
  module Point3 = Point3;
  module TypedArray = TypedArray;
  module Vector3 = Vector3;

  let start = (startState: 'a, update: ('a, float) => 'a, draw: 'a => 'a) => {
    /* Setup canvas and context for rendering. */
    Canvas.resize(canvas);

    context##enable(GLConsts.cullFace);
    context##cullFace(GLConsts.back);
    context##enable(GLConsts.depthTest);

    /* Update method that runs every on every animation frame. */
    let loopStep = (state, dt) => {
      /* Update the simulation. */
      let newState = update(state, dt);

      /* Clear the screen and update the view port. */
      Canvas.resize(canvas);
      context##viewport(0, 0, Canvas.width(canvas), Canvas.height(canvas));
      context##clearColor(0.0, 0.0, 0.0, 1.0);
      context##clear(GLConsts.colorBufferBit lor GLConsts.depthBufferBit);

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