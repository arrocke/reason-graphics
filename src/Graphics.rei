/* Defines a WebGL application. */
module type ApplicationOptionsType = {
  /* Runs once to setup the WebGL environment. */
  let setup: unit => unit;
  /* Runs on every animation frame updating the simulation. */
  let update: float => unit;
  /* Draws the canvas using WebGL. */
  let draw: unit => unit;
};

/* Runs the application. */
module type ApplicationType = (App: ApplicationOptionsType) => {
  /* Start the application. */
  let start: unit => unit;
};

module Application: ApplicationType;
