// Copyright [2024] SunCAD

#ifndef SRC_COMM_OBSERVABLECOLLECTION_H_
#define SRC_COMM_OBSERVABLECOLLECTION_H_

#include <iostream>
#include <vector>
#include <stdexcept>
#include <algorithm>

#include <boost/signals2.hpp>

namespace sun 
{

template <typename T>
class ObservableCollection 
{
public:
    // Signals for collection changes
    boost::signals2::signal<void()> CollectionChanged;   // Signal when collection changes (e.g. add, remove)
    boost::signals2::signal<void()> PropertyChanged;     // Signal when a property changes (e.g. size)

    ObservableCollection() = default;

    ObservableCollection(const std::vector<T>& collection) : data(collection) {}

    void Add(const T& item) {
        data.push_back(item);
        OnCollectionChanged();
        OnPropertyChanged();
    }

    void RemoveAt(std::size_t index) {
        if (index >= data.size()) {
            throw std::out_of_range("Index out of range");
        }
        data.erase(data.begin() + index);
        OnCollectionChanged();
        OnPropertyChanged();
    }

    void Insert(std::size_t index, const T& item) {
        if (index > data.size()) {
            throw std::out_of_range("Index out of range");
        }
        data.insert(data.begin() + index, item);
        OnCollectionChanged();
        OnPropertyChanged();
    }

    void Move(std::size_t oldIndex, std::size_t newIndex) {
        if (oldIndex >= data.size() || newIndex >= data.size()) {
            throw std::out_of_range("Index out of range");
        }
        T item = data[oldIndex];
        data.erase(data.begin() + oldIndex);
        data.insert(data.begin() + newIndex, item);
        OnCollectionChanged();
    }

    void Clear() {
        data.clear();
        OnCollectionChanged();
        OnPropertyChanged();
    }

    const T& operator[](std::size_t index) const {
        if (index >= data.size()) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    std::size_t Size() const {
        return data.size();
    }

    // PropertyChanged will be called when the size of the collection changes
    void OnPropertyChanged() {
        PropertyChanged();
    }

    // CollectionChanged will be called when an item is added/removed/modified
    void OnCollectionChanged() {
        CollectionChanged();
    }

private:
    std::vector<T> data; // Underlying data structure
};

}  // namespace sun

#endif  // SRC_COMM_OBSERVABLECOLLECTION_H_
