open Jest;
open Expect;

describe("create", () => {
  let v = Vector3.create(1.0, 2.0, 3.0);

  test("stores x component correctly.", () => {
    expect(Vector3.x(v)) |> toBe(1.0);
  });

  test("stores y component correctly.", () => {
    expect(Vector3.y(v)) |> toBe(2.0);
  });

  test("stores z component correctly.", () => {
    expect(Vector3.z(v)) |> toBe(3.0);
  });
});

describe("dot", () => {
  test("calculates the dot product correctly.", () => {
    let u = Vector3.create(1.0, 2.0, 3.0);
    let v = Vector3.create(3.0, 2.0, 1.0);
    expect(Vector3.dot(u, v)) |> toEqual(10.0);
  });
});

describe("cross", () => {
  let u = Vector3.create(1.0, 2.0, 3.0);
  let v = Vector3.create(3.0, 2.0, 1.0);

  test("calculates the cross product correctly.", () => {
    expect(Vector3.cross(u, v)) |> toEqual(Vector3.create(-.4.0, 8.0, -.4.0));
  });

  test("order matters.", () => {
    expect(Vector3.cross(v, u)) |> toEqual(Vector3.create(4.0, -.8.0, 4.0));
  });
});

describe("len", () => {
  test("returns the length of the vector.", () => {
    let actual = Vector3.create(4.0, 3.0, 2.0);
    expect(Vector3.len(actual)) |> toEqual(sqrt(16.0 +. 9.0 +. 4.0));
  });
});

describe("unit", () => {
  test("returns the correct unit vector", () => {
    let sq3 = 1.0 /. sqrt(3.0);
    let expected = Vector3.create(sq3, sq3, sq3);
    let actual = Vector3.create(1.0, 1.0, 1.0);
    expect(Vector3.unit(actual)) |> toEqual(expected);
  });
});