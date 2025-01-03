// Copyright [2024] SunCAD

#ifndef COMM_BASEOBJECT_H_
#define COMM_BASEOBJECT_H_

#include <string>

#include <boost/signals2.hpp>
#include <boost/uuid/nil_generator.hpp>
#include <boost/uuid/uuid.hpp>

#include <Standard_Handle.hxx>
#include <Standard_Transient.hxx>

namespace sun 
{

class BaseObject : public Standard_Transient 
{
public:
    BaseObject() : SuppressPropertyChangedEvent(false), IsDeserializing(false) {}

    // PropertyChanged signal
    boost::signals2::signal<void(const std::string&)> PropertyChanged;

    // Property to control event suppression
    bool SuppressPropertyChangedEvent;

    // To handle the event notification
    virtual void RaisePropertyChanged(const std::string& propertyName = "") 
    {
        if (PropertyChanged.num_slots() != 0 && !SuppressPropertyChangedEvent) {
            PropertyChanged(propertyName);
        }
    }

    // Serialization and deserialization state
    bool IsDeserializing;

    virtual void OnBeforeUndo() {}

    virtual void OnAfterUndo() {}

    // Serialization methods (placeholders)
    virtual void OnBeginSerializing() {}

    virtual void OnSerialized() {}

    virtual void OnBeginDeserializing() 
    {
        IsDeserializing = true;
    }

    virtual void OnDeserialized() 
    {
        IsDeserializing = false;
    }

    // Guid equivalent method
    virtual boost::uuids::uuid GetReferenceId() 
    {
        return boost::uuids::nil_uuid();  // Return nil UUID as default
    }

};

}  // namespace sun

#endif  // COMM_BASEOBJECT_H_
