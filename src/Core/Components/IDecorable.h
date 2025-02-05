// Copyright [2024] SunCAD

#ifndef CORE_COMPONENTS_IDECORABLE_H_
#define CORE_COMPONENTS_IDECORABLE_H_

class Component;

class Idecorable 
{
public:
    virtual ~Idecorable() = default;
    virtual void removeComponent(Component* comp) = 0;
};

#endif  // CORE_COMPONENTS_IDECORABLE_H_
