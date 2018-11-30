[@bs.deriving abstract]
type t = pri {
  clientHeight: int,
  clientWidth: int,
  mutable width: int,
  mutable height: int
};

[@bs.scope "document"] [@bs.val] external findById : string => t = "getElementById";

[@bs.send] external getContext : (t, string) => option(GLContext.t) = "getContext";

let resize = (c) => {
  heightSet(c, clientHeightGet(c));
  widthSet(c, clientWidthGet(c));
};

let context = c => getContext(c, "webgl");

let width = c => widthGet(c);
let height = c => heightGet(c);