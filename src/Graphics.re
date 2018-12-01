module type ApplicationOptionsType = {
  let setup: unit => unit;
  let update: float => unit;
  let draw: unit => unit;
};

module type ApplicationType = (App: ApplicationOptionsType) => {
  let start: unit => unit;
};

module Application = (App: ApplicationOptionsType) => {
  [@bs.val] external requestAnimationFrame : (float => unit) => unit = "";

  let ctx = Canvas.context;

  /* Update method that runs every on every animation frame. */
  let update = (dt) => {
    App.update(dt);

    /* Clear the screen on every update. */
    GLContext.clearColor(ctx, 0.0, 0.0, 0.0, 1.0);
    GLContext.clear(ctx, GLConsts.colorBufferBit);

    App.draw();
  }

  /* Runs the application. */
  let start = () => {
    /* Setup canvas and context for rendering. */
    Canvas.resize();
    App.setup();

    /* Run application main loop. */
    /* It receives the previous timestamp from the last animation frame. */
    /*   and the current timestamp from the current animation frame. */
    let rec step = (lastTimestamp, currentTimestamp) => {
      update(currentTimestamp -. lastTimestamp);
      requestAnimationFrame(step(currentTimestamp));
    }
    /* First frame has zero elapsed time. */
    requestAnimationFrame((currentTimestamp) => {
      update(0.0);
      requestAnimationFrame(step(currentTimestamp));
    });
  }
}