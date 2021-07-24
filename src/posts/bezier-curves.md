---
title: Bezier Curves
author: BergerAPI
date: 23th Jul 2021
---

In this tutorial I want to show you how to create a linear/quadratic Bézier curve.

---

## Linear Bézier Curve

![thumbnail gif](/img/bezier/linear.gif)

The formula for the linear Bézier curve is: $b\left(t\right)=\left(1-t\right)P_{1}+tP_{2}$.
This function calculates the x or y on the curve at a given time $t$. In this case, function $b\left(t\right)$ is the same for the x and the y. The time, $t$, is a value between 0 and 1.

An example code of a linear Bézier curve is:

```javascript
for (let t = 0; t < 1; t += 0.01) {
  let x = (1 - t) * P1.x + t * P2.x;
  let y = (1 - t) * P1.y + t * P2.y;

  ...
}
```

---

## Quadratic Bézier Curve

![thumbnail gif](/img/bezier/quadratic.gif)

The formula for the linear Bézier curve is: $b\left(t\right)=\left(1-t\right)^{2}b_{0}+2t\left(1-t\right)b_{1}+t^{2}b_{2}$.
This function calculates the x or y on the curve at a given time $t$. In this case, function $b\left(t\right)$ is the same for the x and the y. The time, $t$, is a value between 0 and 1.

An example code of a quadratic Bézier curve is:

```javascript
for (let t = 0; t < 1; t += 0.01) {
  let x = Math.pow((1 - t), 2) * b0.x + 2 * t * (1 - t) * b1.x + Math.pow(t, 2) * b2.x;
  let y = Math.pow((1 - t), 2) * b0.y + 2 * t * (1 - t) * b1.y + Math.pow(t, 2) * b2.y;

  ...
}
```

**Happy Coding!**
