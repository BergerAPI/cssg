---
title: Bézier Curves
author: BergerAPI
date: 23th Jul 2021
---

In this tutorial I want to show you how to create a linear/quadratic Bézier curve.

---

A bézier curve is defined by a certain number of points, from $P_{0}$ through $P_{n}$. The first and last point of the bézier curve are always the endpoints.

---

## Linear Bézier Curve

![linear.gif](/img/bezier/linear.gif)

In this case, we have given the point $P_{0}$ and the point $P_{1}$. The linear Bezier curve is a straight line between 2 points ($P_{0}$ and $P_{1}$). Furthermore, this curve is equivalent to the linear interpolation. The curve is given by:

${\displaystyle \mathbf {B} (t)=\mathbf {P} _{0}+t(\mathbf {P} _{1}-\mathbf {P} _{0})=(1-t)\mathbf {P} _{0}+t\mathbf {P} _{1},\ 0\leq t\leq 1}$

The function $B(t)$ ith the time $t$, represents the x and y position at the defined time.

We can see a code example here:

```javascript
const p0 = { x: 10, y: 10 };
const p1 = { x: 20, y: 20 };

for (let t = 0; t < 1; t += 0.01) {
  let x = (1 - t) * p0.x + t * p1.x;
  let y = (1 - t) * p0.y + t * p1.y;

  ...
}
```

---

## Quadratic Bézier Curve

![linear.gif](/img/bezier/quadratic.gif)

In this case, we have given the point $P_{0}$, $P_{1}$ and the point $P_{2}$.

```javascript
const p0 = { x: 10, y: 10 };
const p1 = { x: 20, y: 20 };
const p2 = { x: 20, y: 20 };

for (let t = 0; t < 1; t += 0.01) {
  let x = pow((1 - t), 2) * p0.x + 2 * t * (1 - t) * p1.x + pow(t, 2) * p2.x;
  let y = pow((1 - t), 2) * p0.y + 2 * t * (1 - t) * p1.y + pow(t, 2) * p2.y;

  ...
}
```

The function $B(t)$ ith the time $t$, represents the x and y position at the defined time.

---

The images are from (c) [Wikipedia](https://en.wikipedia.org/wiki/B%C3%A9zier_curve), and under the "Public Domain" license.
