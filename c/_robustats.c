#include <Python.h>
#include <numpy/arrayobject.h>
#include "robustats.h"

// Docstrings
static char module_docstring[] =
    "This module provides an interface for calculating the weighted median using C.";
static char weighted_median_docstring[] =
    "Calculate the weighted median of a data sample with respective weights.";

// Available functions
static PyObject *robustats_weighted_median(PyObject *self, PyObject *args);

// Module specification
static PyMethodDef module_methods[] = {
    {"weighted_median", (PyCFunction)robustats_weighted_median, METH_VARARGS, weighted_median_docstring},
    {NULL, NULL, 0, NULL}
};

static struct PyModuleDef robustatsmodule = {
    PyModuleDef_HEAD_INIT,
    "_robustats",   // Module name
    module_docstring,
    -1,       // size of per-interpreter state of the module,
              // or -1 if the module keeps state in global variables.
    module_methods
};

// Initialize the module
PyMODINIT_FUNC PyInit__robustats(void)
{
    PyObject *m;

    m = PyModule_Create(&robustatsmodule);
    if (m == NULL)
        return NULL;

    // Load Numpy functionality
    import_array();

    return m;
}

static PyObject *robustats_weighted_median(PyObject *self, PyObject *args)
{
    PyObject *x_obj, *w_obj;

    // Parse the input tuple
    if (!PyArg_ParseTuple(args, "OO", &x_obj, &w_obj))
        return NULL;

    // Interpret the input objects as numpy arrays
    PyObject *x_array = PyArray_FROM_OTF(x_obj, NPY_DOUBLE, NPY_IN_ARRAY);
    PyObject *w_array = PyArray_FROM_OTF(w_obj, NPY_DOUBLE, NPY_IN_ARRAY);

    // If that didn't work, throw an exception
    if (x_array == NULL || w_array == NULL) {
        Py_XDECREF(x_array);
        Py_XDECREF(w_array);
        return NULL;
    }

    // Number of data points
    int n = (int)PyArray_DIM(x_array, 0);

    // Get pointers to the data as C-types
    double *x = (double*)PyArray_DATA(x_array);
    double *w = (double*)PyArray_DATA(w_array);

    // Call the external C function to compute the chi-squared
    double value = weighted_median(x, w, 0, n - 1);

    // Clean up
    Py_DECREF(x_array);
    Py_DECREF(w_array);

    // Build the output tuple
    PyObject *ret = Py_BuildValue("d", value);
    return ret;
}
