/* Defines a WebGL application. */
module type ApplicationOptionsType = {
  type state;
  /* Runs once to setup the WebGL environment. */
  let setup: unit => state;
  /* Runs on every animation frame updating the simulation. */
  let update: (state, float) => state;
  /* Draws the canvas using WebGL. */
  let draw: state => state;
};

/* Runs the application. */
module type ApplicationType = (App: ApplicationOptionsType) => {
  /* Start the application. */
  let start: unit => unit;
};

module Application: ApplicationType;
