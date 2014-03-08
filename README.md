Calgo
=====

algo engine in C

To compile:

> make

> cd ./build

There will be 2 libraries in that directory, cd into the one that
starts with "lib." (it should NOT start with "tmp")

> mv algoengine.so ../..
> ln -sf algoengine.so libalgoengine.so
> LD_LIBRARY_PATH=.
(Yes, that is a period. You have to direct it to the current directory)
> export LD_LIBRARY_PATH

Now you can run the program with
./calgo <name of python script>


The python script must define strategy(), but can also define init(), which will
be called before the engine starts running.
