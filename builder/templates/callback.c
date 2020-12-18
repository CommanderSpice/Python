typedef struct {
  PyObject_HEAD;
  const struct SSkirmishAICallback* callback; // C Callback Object
} PyAICallbackObject;

static PyTypeObject PyAICallback_Type;

PyObject*
PyAICallback_New(const struct SSkirmishAICallback* callback)
{
  PyAICallbackObject *self;
  self = (PyAICallbackObject *)PyAICallback_Type.tp_alloc(&PyAICallback_Type, 0);
  
  if (self)
  {
    self->callback=callback;
  }
  return (PyObject*)self;
}

{% for funcname in clbfuncs %}
PyObject*
{{funcname}}(PyObject* ob, PyObject* args)
{
  {{clbfuncs[funcname]}}
}
{% endfor %}

static PyMethodDef callback_methods[] = {
{% for funcname in clbfuncs %}
     {"{{funcname}}", (PyCFunction){{funcname}}, METH_VARARGS, "{{funcname}}" },
{% endfor %}
    {NULL}  /* Sentinel */
};

static PyTypeObject PyAICallback_Type = {
    {PyObject_HEAD_INIT(NULL)},
    .tp_name = "PyAICallback",
    .tp_basicsize = sizeof(PyAICallbackObject),
    .tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
    .tp_doc = "callback object",
    .tp_methods = callback_methods,
};
