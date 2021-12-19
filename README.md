# semi_uniform_iterator

## I would like to stress that if THIS is a solution to your coding problem, you should refactor your code to NOT run into this problem in the first place!
### This repository should be looked at as a fun thought experiment, not an instruction book.
#### There is a section on how to use this code near the bottom.

While working on a project, I coded myself into a corner. Here is a small example of my problem

```c++
class Component{
public:
    enum class ComponentType{
        Transform,
        Sprite,
        Physics,
    };
    virtual ComponentType GetComponentType() const = 0;
    virtual void Update() {}
};

class Transform : public Component{
public:
    ComponentType GetComponentType() const {
        return ComponentType::Transform;
    }
    // More functions and variables here
};

class Sprite : public Component{
public:
    ComponentType GetComponentType() const {
        return ComponentType::Sprite;
    }
    virtual void Update() {
        // do stuff here
    }
    // More functions and variables here
};

class Physics : public Component{
public:
    ComponentType GetComponentType() const {
        return ComponentType::Physics;
    }
    virtual void Update() {
        // do stuff here
    }
    // More functions and variables here
};

```
```c++
class Container{
public:
    virtual ComponentType GetContainerType() const = 0;
    virtual Component* GrabFromID(const GUID& id) = 0;
};

template<typename T, ComponentType U>
class GenericContainer : public Container {
    std::unordered_map<UUID, T> data;
public:
    ComponentType GetContainerType() const {
        return U;
    }
    Component* GrabFromID(const GUID& id) {
        if (data.count(id)) {
            return data[id];
        }
        return nullptr;
    }
};
```
```c++
class Engine{
public:
    std::vector<Container*> containers;
};
```
The problem here is that I cannot iterate over any of the data in the GenericContainer class.
If I wanted to iterate over every physics component and update them, I would have to grab the IDs of
everything, check to see if there is a corresponding physics component, and then update them. However,
C++ iterators do just that but without any of the searching overhead.

The exact problem that I had was slightly more complex, but this is a good short version of the problem.
So now I had to find a way to get access to a specific, templated iterator but without compile time knowledge
of what specific container I was looking at.

So, the only two pieces of knowledge I knew was all the information through the Container base class
and the Component base class. Which meant that I had to make an iterator that would allow you to return
something standard through the Container base class and access the data on the Component base class.

This code repository is my solution to that problem.
This allows me to add these function signatures to the Container base class:
```c++
{
public:
    virtual Iterator<Component> begin() = 0;
    virtual Iterator<Component> end() = 0;
}
```

And this allowed me to do some more with my extremely generic Container base class.

Such as updating every component regardless of what anything actually is
```c++
void EngineUpdate()
{
    // iterate over every container using the std::vector<>'s  begin and end
    foreach(Container*& container : containers) { 
        // iterators to the start and end of each internal container
        Iterator<Component> start = container.begin();
        Iterator<Component> end = container.end();
        // iterating over every container
        for (; start != end; ++start) {
            // calling update on every object
            start->Update();
        }
    }
}
```

Doing specific code just for sprites since they need to be rendered
```c++
void EngineUpdate()
{
    foreach(Container*& container : containers) {
        Iterator<Component> start = container.begin();
        Iterator<Component> end = container.end();
        for (; start != end; ++start) {
            start->Update();
            if (start->GetComponentType() == ComponentType::Sprite) {
                dynamic_cast<Sprite&>(*start).Render();
            }
        }
    }
}
```

And doing all kinds of other wacky things.

Read more about how I got myself into this problem and how I designed the solution here: LINK TBD

##How to Use

A short list of things you should know to use this code:
```c++
Iterator<T> iterator;
MakeIterator<T>(vector.begin());
MakeIteratorLeft<T>(map.begin());
MakeIteratorRight<T>(map.begin());
```

The `Iterator<T>` is a forward iterator that exposes the base class of whatever you are iterating over.
You can use the dereference operator, the arrow operator, pre-decrement, post-decrement, assignment,
copy and move constructors, and the subrtaction operator to signify the distance between two iterators.

`MakeIterator<T>()` returns a simple iterator. This is what would be used in a class that looks like this:
```c++
class VectorContainer : public Container {
private:
    std::vector<Sprite> data;
    
public:
    virtual Iterator<Component> begin() override {
        return MakeIterator<Component>(data.begin());
    }
    virtual Iterator<Component> end() override {
        return MakeIterator<Component>(data.end());
    }
};
```

`MakeIteratorLeft<T>()` and `MakeIteratorRight<T>()` are meant to be used with pair-based data structures
such as maps and hashes. Examples:
```c++
class MapContainer1 : public Container {
private:
    std::map<int, Sprite> data;
    
public:
    virtual Iterator<Component> begin() override {
        return MakeIteratorRight<Component>(data.begin());
    }
    virtual Iterator<Component> end() override {
        return MakeIteratorRight<Component>(data.end());
    }
};
```
```c++
class MapContainer2 : public Container {
private:
    std::vector<Sprite, int> data;
    
public:
    virtual Iterator<Component> begin() override {
        return MakeIteratorLeft<Component>(data.begin());
    }
    virtual Iterator<Component> end() override {
        return MakeIteratorLeft<Component>(data.end());
    }
};
```

The implementation of the `MakeIterator...<T>()` functions are a single line of code, so you could also
just write the implementation in your own begin and end functions.

Another note is the `DisableMemoryManager()` function in the `IteratorWrapper<T, U>` class. If you ever
end up making an IteratorWrapper class on the stack, call this function to stop delete from being called
on the stack. However, you should not need make IteratorWrapper classes on the stack. I had to for testing.
