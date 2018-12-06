module type ApplicationOptionsType = {
  type state;
  let setup: unit => state;
  let update: (state, float) => state;
  let draw: state => state;
};

module type ApplicationType = (App: ApplicationOptionsType) => {
  let start: unit => unit;
};

module Application = (App: ApplicationOptionsType) => {
  [@bs.val] external requestAnimationFrame : (float => unit) => unit = "";

  let ctx = Canvas.context;

  /* Update method that runs every on every animation frame. */
  let update = (state, dt) => {
    let newState = App.update(state, dt);

    /* Clear the screen and update the view port on every update. */
    GLInterface.viewport(Canvas.context, 0, 0, Canvas.width(), Canvas.height());
    GLInterface.clearColor(ctx, 0.0, 0.0, 0.0, 1.0);
    GLInterface.clear(ctx, GLConsts.colorBufferBit lor GLConsts.depthBufferBit);


    App.draw(newState);
  }

  /* Runs the application. */
  let start = () => {
    /* Setup canvas and context for rendering. */
    Canvas.resize();
    let state = App.setup();

    GLInterface.enable(Canvas.context, GLConsts.cullFace);
    GLInterface.cullFace(Canvas.context, GLConsts.back);
    GLInterface.enable(Canvas.context, GLConsts.depthTest);

    /* Run application main loop. */
    /* It receives the previous timestamp from the last animation frame. */
    /*   and the current timestamp from the current animation frame. */
    let rec step = (state, lastTimestamp, currentTimestamp) => {
      let newState = update(state, currentTimestamp -. lastTimestamp);
      requestAnimationFrame(step(newState, currentTimestamp));
    }
    /* First frame has zero elapsed time. */
    requestAnimationFrame((currentTimestamp) => {
      let newState = update(state, 0.0);
      requestAnimationFrame(step(newState, currentTimestamp));
    });
  }
}