# CSSG

This is a simple Static-Site-Generator and my blog. Since I am very creative, I call the SSG "CSSG", dueto it being written in C.

# Building

To build this, you'll need `Cmake` and a build-tool like `Make`.

```shell
$ mkdir build ; cd build # Creating and going into the build directory
$ cmake .. # Generating the files for the build-tool
$ make # Compiling
```

This uses a build-directory so the root-directory isn't full of build files.

Now you can run the SSG. See #usage

# Usage

There are 2 parameters that you will need to provide:

- `-file`: Defines the file to parse and generate HTML from
- `-template`: The template of the html code, which gets all the infos from the file injected in.

An example could look like this:

```shell
$ cssg -file content/test.md -template template/post.html 
```
