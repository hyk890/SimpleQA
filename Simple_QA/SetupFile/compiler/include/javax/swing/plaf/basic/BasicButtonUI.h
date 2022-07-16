// DO NOT EDIT THIS FILE - it is machine generated -*- c++ -*-

#ifndef __javax_swing_plaf_basic_BasicButtonUI__
#define __javax_swing_plaf_basic_BasicButtonUI__

#pragma interface

#include <javax/swing/plaf/ButtonUI.h>

extern "Java"
{
  namespace javax
  {
    namespace swing
    {
      namespace plaf
      {
        namespace basic
        {
          class BasicButtonUI;
        }
        class ComponentUI;
      }
      class JComponent;
    }
  }
  namespace java
  {
    namespace awt
    {
      class Rectangle;
      class Graphics;
      class Dimension;
      class Color;
    }
  }
}

class javax::swing::plaf::basic::BasicButtonUI : public ::javax::swing::plaf::ButtonUI
{
public:
  static ::javax::swing::plaf::ComponentUI *createUI (::javax::swing::JComponent *);
  virtual void installUI (::javax::swing::JComponent *);
  virtual ::java::awt::Dimension *getPreferredSize (::javax::swing::JComponent *);
  virtual void paint (::java::awt::Graphics *, ::javax::swing::JComponent *);
public:  // actually protected
  virtual void paintFocus (::java::awt::Graphics *, ::javax::swing::JComponent *, ::java::awt::Rectangle *, ::java::awt::Rectangle *, ::java::awt::Rectangle *) { }
  virtual void paintIcon (::java::awt::Graphics *, ::javax::swing::JComponent *, ::java::awt::Rectangle *);
  virtual void paintButtonPressed (::java::awt::Graphics *, ::javax::swing::JComponent *);
  virtual void paintButtonNormal (::java::awt::Graphics *, ::javax::swing::JComponent *);
  virtual void paintText (::java::awt::Graphics *, ::javax::swing::JComponent *, ::java::awt::Rectangle *, ::java::lang::String *);
public:
  BasicButtonUI ();
public: // actually package-private
  jint __attribute__((aligned(__alignof__( ::javax::swing::plaf::ButtonUI ))))  gap;
  ::java::awt::Color *textColor;
  ::java::awt::Color *disabledTextColor;
  ::java::awt::Color *pressedBackgroundColor;
  ::java::awt::Color *normalBackgroundColor;
public:

  static ::java::lang::Class class$;
};

#endif /* __javax_swing_plaf_basic_BasicButtonUI__ */