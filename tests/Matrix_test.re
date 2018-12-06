/* open Jest;
open Expect;

describe("identity", () => {
  test("returns correct matrix", () => {
    let identityMatrix = Matrix.create(
      1.0, 0.0, 0.0, 0.0,
      0.0, 1.0, 0.0, 0.0,
      0.0, 0.0, 1.0, 0.0,
      0.0, 0.0, 0.0, 1.0
    );
    expect(Matrix.identity) |> toEqual(identityMatrix);
  });
});

describe("transpose", () => {
  test("transposes the give matrix correctly.", () => {
    let testMatrix = Matrix.create(
      1.0, 2.0, 3.0, 4.0,
      4.0, 3.0, 2.0, 1.0,
      5.0, 6.0, 7.0, 8.0,
      8.0, 7.0, 6.0, 5.0
    );
    let transposedMatrix = Matrix.create(
      1.0, 4.0, 5.0, 8.0,  
      2.0, 3.0, 6.0, 7.0,
      3.0, 2.0, 7.0, 6.0,
      4.0, 1.0, 8.0, 5.0
    );
    expect(testMatrix |> Matrix.transpose)
      |> toEqual(transposedMatrix);
  });
});

describe("translation", () => {
  test("returns the correct translation matrix.", () => {
    let translationMatrix = Matrix.create(
      1.0, 0.0, 0.0, 2.0,
      0.0, 1.0, 0.0, 3.0,
      0.0, 0.0, 1.0, 4.0,
      0.0, 0.0, 0.0, 1.0
    );
    expect(Matrix.translation(2.0, 3.0, 4.0)) |> toEqual(translationMatrix);
  });
});

describe("scale", () => {
  test("returns the correct scale matrix.", () => {
    let scaleMatrix = Matrix.create(
      2.0, 0.0, 0.0, 0.0,
      0.0, 3.0, 0.0, 0.0,
      0.0, 0.0, 4.0, 0.0,
      0.0, 0.0, 0.0, 1.0
    );
    expect(Matrix.scale(2.0, 3.0, 4.0)) |> toEqual(scaleMatrix);
  });
});

describe("rotationX", () => {
  test("returns the correct rotation matrix.", () => {
    let rotationMatrix = Matrix.create(
      1.0, 0.0,      0.0,        0.0,
      0.0, cos(1.0), -.sin(1.0), 0.0,
      0.0, sin(1.0), cos(1.0),   0.0,
      0.0, 0.0,      0.0,        1.0
    );
    expect(Matrix.rotationX(1.0)) |> toEqual(rotationMatrix);
  });
});

describe("rotationY", () => {
  test("returns the correct rotation matrix.", () => {
    let rotationMatrix = Matrix.create(
      cos(1.0),   0.0, sin(1.0), 0.0,
      0.0,        1.0, 0.0,      0.0,
      -.sin(1.0), 0.0, cos(1.0), 0.0,
      0.0,        0.0, 0.0,      1.0
    );
    expect(Matrix.rotationY(1.0)) |> toEqual(rotationMatrix);
  });
});

describe("rotationZ", () => {
  test("returns the correct rotation matrix.", () => {
    let rotationMatrix = Matrix.create(
      cos(1.0), -.sin(1.0), 0.0, 0.0,
      sin(1.0), cos(1.0),   0.0, 0.0,
      0.0,      0.0,        1.0, 0.0,
      0.0,      0.0,        0.0, 1.0
    );
    expect(Matrix.rotationZ(1.0)) |> toEqual(rotationMatrix);
  });
});

describe("rotation", () => {
  test("returns the correct rotation matrix around the x-axis.", () => {
    expect(Matrix.rotation(1.0, 0.0, 0.0, 1.0)) |> toEqual(Matrix.rotationX(1.0));
  });

  test("returns the correct rotation matrix around the y-axis.", () => {
    expect(Matrix.rotation(0.0, 1.0, 0.0, 1.0)) |> toEqual(Matrix.rotationY(1.0));
  });

  test("returns the correct rotation matrix around the z-axis.", () => {
    expect(Matrix.rotation(0.0, 0.0, 1.0, 1.0)) |> toEqual(Matrix.rotationZ(1.0));
  });

  test("normalizes the rotation vector.", () => {
    expect(Matrix.rotation(0.0, 0.0, 2.0, 1.0)) |> toEqual(Matrix.rotationZ(1.0));
  });
});

describe("at", () => {
  let testMatrix = Matrix.create(
    0.0,  1.0,  2.0,  3.0,
    4.0,  5.0,  6.0,  7.0,
    8.0,  9.0,  10.0, 11.0,
    12.0, 13.0, 14.0, 15.0
  );

  testAll(
    "returns element at row, column.",
    [(0,0), (0,1), (0,2), (0,3),
     (1,0), (1,1), (1,2), (1,3),
     (2,0), (2,1), (2,2), (2,3),
     (3,0), (3,1), (3,2), (3,3)],
    ((x,y)) => expect(Matrix.at(testMatrix, x, y)) |> toEqual(float_of_int(4 * x + y))
  );
});

describe("multiply", () => {
  test("identity times another matrix is that matrix.", () => {
    expect(Matrix.multiply(Matrix.identity, Matrix.rotationX(1.0))) |> toEqual(Matrix.rotationX(1.0));
  });

  test("multiplies two matricies correctly.", () => {
    let testMatrix = Matrix.create(
      1.0,  2.0,  3.0,  4.0,
      5.0,  6.0,  7.0,  8.0,
      9.0,  10.0, 11.0, 12.0,
      13.0, 14.0, 15.0, 16.0
    );
    let resultMatrix = Matrix.create(
      90.0,  100.0, 110.0, 120.0,
      202.0, 228.0, 254.0, 280.0,
      314.0, 356.0, 398.0, 440.0,
      426.0, 484.0, 542.0, 600.0
    );
    expect(Matrix.multiply(testMatrix, testMatrix)) |> toEqual(resultMatrix);
  });
});

describe("inverse", () => {
  test("inverse of the identity is the identity.", () => {
    expect(Matrix.inverse(Matrix.identity)) |> toEqual(Matrix.identity);
  });

  test("throws NoInverse if the determinant is zero.", () => {
    let testMatrix = Matrix.create(
      1.0,  2.0,  3.0,  4.0,
      5.0,  6.0,  7.0,  8.0,
      9.0,  10.0, 11.0, 12.0,
      13.0, 14.0, 15.0, 16.0
    );
    expect(() => Matrix.inverse(testMatrix)) |> toThrowException(Matrix.NoInverse);
  });

  test("computed inverse of a translation matrix correctly.", () => {
    let translate = Matrix.translation(1.0, 2.0, 3.0);
    let reverse = Matrix.translation(-.1.0, -.2.0, -.3.0);
    expect(Matrix.inverse(translate)) |> toEqual(reverse);
  });

  test("computed inverse of a rotation matrix correctly.", () => {
    let rotation = Matrix.rotationX(1.0);
    let reverse = Matrix.rotationX(-.1.0);
    expect(Matrix.inverse(rotation)) |> toEqual(reverse);
  });
});

describe("perspective", () => {
  test("computes the perspective matrix correctly.", () => {
    let perspectiveMatrix = Matrix.create(
      2.8103896819890215, 0.0, 0.0, 0.0,
      0.0, 1.7319841428265121, 0.0, 0.0,
      0.0, 0.0, -.1.0040080160320641, -.0.20040080160320642,
      0.0, 0.0, -.1.0, 0.0
    );
    let aspect = 0.616279;
    expect(Matrix.perspective(60.0, aspect, 0.1, 50.0)) |> toEqual(perspectiveMatrix);
  });
});
*/