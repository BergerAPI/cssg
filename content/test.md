---
name: test Post
description: A test post.
author: niclas
---

# Hello World!

```go
package main

import "fmt"

func main() {
    ch := make(chan float64)
    ch <- 1.0e10    // magic number
    x, ok := <- ch
    defer fmt.Println(`exitting now\`)
    go println(len("hello world!"))
    return
}
```

Welcome to this blog post, which currently acts as placeholder for other posts.
