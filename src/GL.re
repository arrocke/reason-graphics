open GLConsts;

type context;

[@bs.send] external clear: (context, enum) => unit = "";
[@bs.send] external clearColor: (context, float, float, float, float) => unit = "";
[@bs.send] external cullFace: (context, enum) => unit = "";
[@bs.send] external enable: (context, enum) => unit = "";
[@bs.send] external viewport: (context, int, int, int, int) => unit = "";