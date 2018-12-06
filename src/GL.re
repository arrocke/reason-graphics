module Types = GLTypes;
module Consts = GLConsts;

class type _context = [@bs] {
  pub clear: GLTypes.glEnum => unit;
};

type context = Js.t(_context);