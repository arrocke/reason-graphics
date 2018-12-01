[@bs.deriving abstract]
type t = pri {
  clientHeight: int,
  clientWidth: int,
  mutable width: int,
  mutable height: int
};

exception WebGLNotSupported;

[@bs.scope "document"] [@bs.val] external createCanvas : ([@bs.as "canvas"] _, unit) => t = "createElement";
[@bs.scope "document.body"] [@bs.val] external appendCanvas : t => unit = "appendChild";
[@bs.send] external setCanvasStyle : (t, [@bs.as "style"] _, string) => unit = "setAttribute";
[@bs.scope "document.body"] [@bs.val] external setBodyStyle : ([@bs.as "style"] _, string) => unit = "setAttribute";
[@bs.send] external getContext : (t, string) => option(GLContext.t) = "getContext";

/* Create the canvas and insert into the page. */
let canvas = createCanvas();
setCanvasStyle(canvas, "position: absolute; width: 100%; height: 100%;")
setBodyStyle("margin: 0; padding: 0");
appendCanvas(canvas);

let context = switch(getContext(canvas, "webgl")) {
| Some(ctx) => ctx
| None => raise(WebGLNotSupported)
};

let resize = () => {
  heightSet(canvas, clientHeightGet(canvas));
  widthSet(canvas, clientWidthGet(canvas));
};

let width = () => widthGet(canvas);
let height = () => heightGet(canvas);