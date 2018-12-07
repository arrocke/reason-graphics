module Initialize(Options: {
  let canvasSelector: option(string)
}): {
  module Matrix = Matrix;
  module Point3 = Point3;
  module Vector3 = Vector3;
  module ShaderProgram: ShaderProgram.Type;

  let start: (
    'a,
    ('a, float) => 'a,
    'a => 'a
  ) => unit;
};