// DO NOT EDIT THIS FILE - it is machine generated -*- c++ -*-

#ifndef __java_security_interfaces_DSAKeyPairGenerator__
#define __java_security_interfaces_DSAKeyPairGenerator__

#pragma interface

#include <java/lang/Object.h>

extern "Java"
{
  namespace java
  {
    namespace security
    {
      class SecureRandom;
      namespace interfaces
      {
        class DSAKeyPairGenerator;
        class DSAParams;
      }
    }
  }
}

class java::security::interfaces::DSAKeyPairGenerator : public ::java::lang::Object
{
public:
  virtual void initialize (::java::security::interfaces::DSAParams *, ::java::security::SecureRandom *) = 0;
  virtual void initialize (jint, jboolean, ::java::security::SecureRandom *) = 0;

  static ::java::lang::Class class$;
} __attribute__ ((java_interface));

#endif /* __java_security_interfaces_DSAKeyPairGenerator__ */