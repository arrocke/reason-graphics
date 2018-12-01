module type ApplicationOptionsType = {
  let setup: unit => unit;
  let update: float => unit;
  let draw: unit => unit;
};

module type ApplicationType = (App: ApplicationOptionsType) => {
  let start: unit => unit;
};

[@bs.send] external clearColor : (GLTypes.context, float, float, float, float) => unit = "clearColor";
[@bs.send] external clear : (GLTypes.context, int) => unit = "clear";
[@bs.send] external viewport : (GLTypes.context, int, int, int, int) => unit = "viewport";

module Application = (App: ApplicationOptionsType) => {
  [@bs.val] external requestAnimationFrame : (float => unit) => unit = "";

  let ctx = Canvas.context;

  /* Update method that runs every on every animation frame. */
  let update = (dt) => {
    App.update(dt);

    /* Clear the screen and update the view port on every update. */
    viewport(Canvas.context, 0, 0, Canvas.width(), Canvas.height());
    clearColor(ctx, 0.0, 0.0, 0.0, 1.0);
    clear(ctx, GLConsts.colorBufferBit);


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