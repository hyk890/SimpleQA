// DO NOT EDIT THIS FILE - it is machine generated -*- c++ -*-

#ifndef __java_lang_VMSecurityManager__
#define __java_lang_VMSecurityManager__

#pragma interface

#include <java/lang/Object.h>
#include <gcj/array.h>

class java::lang::VMSecurityManager : public ::java::lang::Object
{
public: // actually package-private
  static JArray< ::java::lang::Class *> *getClassContext ();
  static ::java::lang::ClassLoader *currentClassLoader ();
  VMSecurityManager ();
public:

  static ::java::lang::Class class$;
};

#endif /* __java_lang_VMSecurityManager__ */