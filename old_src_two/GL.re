exception CanvasNotFound;

module CreateInterface = (Options: {
  let canvasSelector: option(string);
}) => {
  module Types = GLTypes;
  module Consts = GLConsts;

  /* Find or create a canvas */
  let canvas = switch(Options.canvasSelector) {
  | Some(selector) => switch(Canvas.find(selector)) {
    | Some(canvas) => canvas;
    | None => raise(CanvasNotFound);
    }
  | None => Canvas.create()
  };

  /* Setup the context from the canvas. */
  Canvas.resize(canvas);
  let context = Canvas.getContext(canvas);

  module Bindings = GLBindings.Bindings({ let context = context; });
  open Bindings;
}