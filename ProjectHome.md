Basically the objective of this project is to construct a textured 3D model out of range scan data.
There are a couple of minor features, such as volume calculation of 3D object, and sectional views and intuitive UI but the main component is 3D model building and texturing.

Fortunately we have a good programs to start with (with source code) at  http://graphics.stanford.edu/software/scanalyze/

The task can be decomposed into

```
Aligning range scan data     (http://graphics.stanford.edu/software/scanalyze/)
Merging to a single geometry  (http://graphics.stanford.edu/software/vrip/)
Filling any possible holes  (http://graphics.stanford.edu/software/volfill/)
Texturing (image alignment tools are included in scanalyze)
```

All above code was developed with older c++ (often on Linux)  and Tcl/Tk

So the first task is to port those source code to MSVC 2010  and  Qt (replacement of Tcl/Tk UI)

Then we need to simplify the process of above four steps. The ICP algorithm used in scanalyze is quite generic so we don't have any condition on range scan data. However, we can assume reasonable pre-conditions to simplify and streamline the process (i.e. good starting point for alignments)


The time table for this project is to complete this by the end of this semester.