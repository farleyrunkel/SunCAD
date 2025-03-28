// Copyright [2024] SunCAD

#ifndef COMM_QtMouseHelper_H_
#define COMM_QtMouseHelper_H_

#include <QMouseEvent>
#include <QWheelEvent>
#include <QKeyEvent>

#include <Aspect_VKeyFlags.hxx>
#include <Aspect_VKey.hxx>

class QtMouseHelper
{
public:

    //! Map Qt buttons bitmask to virtual keys.
    static Aspect_VKeyMouse qtMouseButtons2VKeys(Qt::MouseButtons theButtons);

    //! Map Qt mouse modifiers bitmask to virtual keys.
    static Aspect_VKeyFlags qtMouseModifiers2VKeys(Qt::KeyboardModifiers theModifiers);

    //! Map Qt key to virtual key.
    static Aspect_VKey qtKey2VKey(int theKey);
};

#endif  // COMM_QtMouseHelper_H_
