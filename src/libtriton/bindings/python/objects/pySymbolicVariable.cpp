//! \file
/*
**  Copyright (C) - Triton
**
**  This program is under the terms of the LGPLv3 License.
*/

#ifdef TRITON_PYTHON_BINDINGS

#include <api.hpp>
#include <pythonObjects.hpp>
#include <pythonUtils.hpp>
#include <pythonXFunctions.hpp>
#include <symbolicVariable.hpp>



/*! \page py_SymbolicVariable_page SymbolicVariable
    \brief [**python api**] All information about the SymbolicVariable python object.

\tableofcontents

\section py_SymbolicVariable_description Description
<hr>

This object is used to represent a symbolic variable contained in a \ref py_SymbolicExpression_page.

~~~~~~~~~~~~~{.py}
>>> symvar = convertRegisterToSymbolicVariable(REG.RAX)
>>> print symvar
SymVar_0:64
~~~~~~~~~~~~~

\section SymbolicVariable_py_api Python API - Methods of the SymbolicVariable class
<hr>

- **getBitSize(void)**<br>
Returns the size of the symbolic variable as integer.

- **getComment(void)**<br>
Returns the comment (if exists) of the symbolic variable as string.

- **getConcreteValue(void)**<br>
Returns the concrete value (if exists) of the symbolic variable.

- **getId(void)**<br>
Returns the id of the symbolic variable as integer. This id is always unique.<br>
e.g: `18`

- **getKind(void)**<br>
Returns the kind of the symbolic variable as \ref py_SYMEXPR_page.<br>
e.g: `SYMEXPR.REG`

- **getKindValue(void)**<br>
Returns the kind value according to the \ref py_SYMEXPR_page.<br>
If `getKind()` returns triton::engines::symbolic::REG, so `getKindValue()` returns the if of the register.<br>
Otherwise, if `getKind()` returns triton::engines::symbolic::MEM, so `getKindValue()` returns the address of the memory access.<br>
Then, if `getKind()` returns triton::engines::symbolic::UNDEF, so `getKindValue()` returns `0`.

- **getName(void)**<br>
Returns name of the the symbolic variable as string.<br>
e.g: `SymVar_18`

- **setComment(string comment)**<br>
Sets a comment of the symbolic variable.

- **setConcreteValue(integer value)**<br>
Sets a concrete value. `value` must be less than 512-bits.

*/



namespace triton {
  namespace bindings {
    namespace python {

      //! SymbolicVariable destructor.
      void SymbolicVariable_dealloc(PyObject* self) {
        std::cout << std::flush;
        Py_DECREF(self);
      }


      static PyObject* SymbolicVariable_getKind(PyObject* self, PyObject* noarg) {
        try {
          return Py_BuildValue("k", PySymbolicVariable_AsSymbolicVariable(self)->getKind());
        }
        catch (const std::exception& e) {
          return PyErr_Format(PyExc_TypeError, "%s", e.what());
        }
      }


      static PyObject* SymbolicVariable_getName(PyObject* self, PyObject* noarg) {
        try {
          return Py_BuildValue("s", PySymbolicVariable_AsSymbolicVariable(self)->getName().c_str());
        }
        catch (const std::exception& e) {
          return PyErr_Format(PyExc_TypeError, "%s", e.what());
        }
      }


      static PyObject* SymbolicVariable_getId(PyObject* self, PyObject* noarg) {
        try {
          return Py_BuildValue("k", PySymbolicVariable_AsSymbolicVariable(self)->getId());
        }
        catch (const std::exception& e) {
          return PyErr_Format(PyExc_TypeError, "%s", e.what());
        }
      }


      static PyObject* SymbolicVariable_getKindValue(PyObject* self, PyObject* noarg) {
        try {
          return PyLong_FromUint(PySymbolicVariable_AsSymbolicVariable(self)->getKindValue());
        }
        catch (const std::exception& e) {
          return PyErr_Format(PyExc_TypeError, "%s", e.what());
        }
      }


      static PyObject* SymbolicVariable_getBitSize(PyObject* self, PyObject* noarg) {
        try {
          return Py_BuildValue("k", PySymbolicVariable_AsSymbolicVariable(self)->getSize());
        }
        catch (const std::exception& e) {
          return PyErr_Format(PyExc_TypeError, "%s", e.what());
        }
      }


      static PyObject* SymbolicVariable_getComment(PyObject* self, PyObject* noarg) {
        try {
          return Py_BuildValue("s", PySymbolicVariable_AsSymbolicVariable(self)->getComment().c_str());
        }
        catch (const std::exception& e) {
          return PyErr_Format(PyExc_TypeError, "%s", e.what());
        }
      }


      static PyObject* SymbolicVariable_getConcreteValue(PyObject* self, PyObject* noarg) {
        try {
          return PyLong_FromUint512(PySymbolicVariable_AsSymbolicVariable(self)->getConcreteValue());
        }
        catch (const std::exception& e) {
          return PyErr_Format(PyExc_TypeError, "%s", e.what());
        }
      }


      static PyObject* SymbolicVariable_setComment(PyObject* self, PyObject* comment) {
        try {
          if (!PyString_Check(comment))
            return PyErr_Format(PyExc_TypeError, "SymbolicVariable::setComment(): Expected a string as argument.");
          PySymbolicVariable_AsSymbolicVariable(self)->setComment(PyString_AsString(comment));
          Py_INCREF(Py_None);
          return Py_None;
        }
        catch (const std::exception& e) {
          return PyErr_Format(PyExc_TypeError, "%s", e.what());
        }
      }


      static PyObject* SymbolicVariable_setConcreteValue(PyObject* self, PyObject* value) {
        try {
          if (!PyLong_Check(value) && !PyInt_Check(value))
            return PyErr_Format(PyExc_TypeError, "SymbolicVariable::setConcretevalue(): Expected an integer as argument.");
          PySymbolicVariable_AsSymbolicVariable(self)->setConcreteValue(PyLong_AsUint512(value));
          Py_INCREF(Py_None);
          return Py_None;
        }
        catch (const std::exception& e) {
          return PyErr_Format(PyExc_TypeError, "%s", e.what());
        }
      }


      static int SymbolicVariable_print(PyObject* self) {
        std::cout << PySymbolicVariable_AsSymbolicVariable(self);
        return 0;
      }


      static PyObject* SymbolicVariable_str(PyObject* self) {
        try {
          std::stringstream str;
          str << PySymbolicVariable_AsSymbolicVariable(self);
          return PyString_FromFormat("%s", str.str().c_str());
        }
        catch (const std::exception& e) {
          return PyErr_Format(PyExc_TypeError, "%s", e.what());
        }
      }


      //! SymbolicVariable methods.
      PyMethodDef SymbolicVariable_callbacks[] = {
        {"getBitSize",        SymbolicVariable_getBitSize,        METH_NOARGS,    ""},
        {"getComment",        SymbolicVariable_getComment,        METH_NOARGS,    ""},
        {"getConcreteValue",  SymbolicVariable_getConcreteValue,  METH_NOARGS,    ""},
        {"getId",             SymbolicVariable_getId,             METH_NOARGS,    ""},
        {"getKind",           SymbolicVariable_getKind,           METH_NOARGS,    ""},
        {"getKindValue",      SymbolicVariable_getKindValue,      METH_NOARGS,    ""},
        {"getName",           SymbolicVariable_getName,           METH_NOARGS,    ""},
        {"setComment",        SymbolicVariable_setComment,        METH_O,         ""},
        {"setConcreteValue",  SymbolicVariable_setConcreteValue,  METH_O,         ""},
        {nullptr,             nullptr,                            0,              nullptr}
      };


      PyTypeObject SymbolicVariable_Type = {
          PyObject_HEAD_INIT(&PyType_Type)
          0,                                          /* ob_size*/
          "SymbolicVariable",                         /* tp_name*/
          sizeof(SymbolicVariable_Object),            /* tp_basicsize*/
          0,                                          /* tp_itemsize*/
          (destructor)SymbolicVariable_dealloc,       /* tp_dealloc*/
          (printfunc)SymbolicVariable_print,          /* tp_print*/
          0,                                          /* tp_getattr*/
          0,                                          /* tp_setattr*/
          0,                                          /* tp_compare*/
          0,                                          /* tp_repr*/
          0,                                          /* tp_as_number*/
          0,                                          /* tp_as_sequence*/
          0,                                          /* tp_as_mapping*/
          0,                                          /* tp_hash */
          0,                                          /* tp_call*/
          (reprfunc)SymbolicVariable_str,             /* tp_str*/
          0,                                          /* tp_getattro*/
          0,                                          /* tp_setattro*/
          0,                                          /* tp_as_buffer*/
          Py_TPFLAGS_DEFAULT,                         /* tp_flags*/
          "SymbolicVariable objects",                 /* tp_doc */
          0,                                          /* tp_traverse */
          0,                                          /* tp_clear */
          0,                                          /* tp_richcompare */
          0,                                          /* tp_weaklistoffset */
          0,                                          /* tp_iter */
          0,                                          /* tp_iternext */
          SymbolicVariable_callbacks,                 /* tp_methods */
          0,                                          /* tp_members */
          0,                                          /* tp_getset */
          0,                                          /* tp_base */
          0,                                          /* tp_dict */
          0,                                          /* tp_descr_get */
          0,                                          /* tp_descr_set */
          0,                                          /* tp_dictoffset */
          0,                                          /* tp_init */
          0,                                          /* tp_alloc */
          0,                                          /* tp_new */
      };


      PyObject* PySymbolicVariable(triton::engines::symbolic::SymbolicVariable* symVar) {
        SymbolicVariable_Object* object;

        if (symVar == nullptr)
          return PyErr_Format(PyExc_TypeError, "PySymbolicVariable(): symVar cannot be null.");

        PyType_Ready(&SymbolicVariable_Type);
        object = PyObject_NEW(SymbolicVariable_Object, &SymbolicVariable_Type);
        if (object != NULL)
          object->symVar = symVar;

        return (PyObject*)object;
      }

    }; /* python namespace */
  }; /* bindings namespace */
}; /* triton namespace */

#endif /* TRITON_PYTHON_BINDINGS */
