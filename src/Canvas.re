[@bs.deriving abstract]
type t = pri {
  clientHeight: int,
  clientWidth: int,
  mutable width: int,
  mutable height: int
};

exception WebGLNotSupported;

[@bs.scope "document"] [@bs.val] external querySelector : (string) => Js.Nullable.t(t) = "querySelector";
[@bs.scope "document"] [@bs.val] external createCanvas : ([@bs.as "canvas"] _, unit) => t = "createElement";
[@bs.scope "document.body"] [@bs.val] external appendCanvas : t => unit = "appendChild";
[@bs.scope "document.body"] [@bs.val] external setBodyStyle : ([@bs.as "style"] _, string) => unit = "setAttribute";
[@bs.send] external setCanvasStyle : (t, [@bs.as "style"] _, string) => unit = "setAttribute";
[@bs.send] external getWebGLContext : (t, [@bs.as "webgl"] _) => Js.Nullable.t(GL.context) = "getContext";

let create = () => {
  let canvas = createCanvas();
  setCanvasStyle(canvas, "position: absolute; width: 100%; height: 100%;");
  setBodyStyle("margin: 0; padding: 0");
  appendCanvas(canvas);
  canvas;
};

let getContext = canvas => {
  switch(getWebGLContext(canvas) |> Js.Nullable.toOption) {
  | Some(ctx) => ctx
  | None => raise(WebGLNotSupported)
  };
};

let find = selector =>  querySelector(selector) |> Js.Nullable.toOption; 

let resize = canvas => {
  heightSet(canvas, clientHeightGet(canvas));
  widthSet(canvas, clientWidthGet(canvas));
};

let width = canvas => widthGet(canvas);
let height = canvas => heightGet(canvas);
let aspectRatio = canvas => (width(canvas) |> float_of_int) /. (height(canvas) |> float_of_int);