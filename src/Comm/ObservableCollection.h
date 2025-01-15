#ifndef COMM_OBSERVABLECOLLECTION_H_
#define COMM_OBSERVABLECOLLECTION_H_

#include <boost/signals2.hpp>
#include <vector>
#include <iostream>
#include <stdexcept>
#include <algorithm>

template <typename T>
class ObservableCollection 
{
public:
    using CollectionChangedSignal = boost::signals2::signal<void(const T&, const std::string&, size_t)>; // Signal: item, action, index
    using PropertyChangedSignal = boost::signals2::signal<void(const std::string&)>; // Signal: property name

    // �źţ����Ϸ�������ʱ
    CollectionChangedSignal collectionChanged;
    PropertyChangedSignal propertyChanged;

    // ���캯��
    ObservableCollection() = default;
    ObservableCollection(const std::vector<T>& collection) : items(collection) {}

    // ��ȡԪ������
    size_t size() const {
        return items.size();
    }

    bool contains(const T& item) 
    {
        auto it = std::find(items.begin(), items.end(), item);
        return it != items.end();
    }

    // ���Ԫ��
    void add(const T& item) {
        items.push_back(item);
        emitCollectionChanged(item, "Add", items.size() - 1);
        emitPropertyChanged("Count");
    }

    // ����Ԫ��
    void insert(size_t index, const T& item) {
        if (index > items.size()) {
            throw std::out_of_range("Index out of range");
        }
        items.insert(items.begin() + index, item);
        emitCollectionChanged(item, "Insert", index);
        emitPropertyChanged("Count");
    }

    // �Ƴ�Ԫ��
    void remove(const T& item) {
        auto it = std::find(items.begin(), items.end(), item);
        if (it != items.end()) {
            size_t index = std::distance(items.begin(), it);
            items.erase(it);
            emitCollectionChanged(item, "Remove", index);
            emitPropertyChanged("Count");
        }
    }

    // ���������Ƴ�Ԫ��
    void removeAt(size_t index) {
        if (index >= items.size()) {
            throw std::out_of_range("Index out of range");
        }
        T removedItem = items[index];
        items.erase(items.begin() + index);
        emitCollectionChanged(removedItem, "Remove", index);
        emitPropertyChanged("Count");
    }

    // ����Ԫ��
    void set(size_t index, const T& item) {
        if (index >= items.size()) {
            throw std::out_of_range("Index out of range");
        }
        T oldItem = items[index];
        items[index] = item;
        emitCollectionChanged(oldItem, "Replace", index);
    }

    // ��ȡԪ��
    T at(size_t index) const {
        if (index >= items.size()) {
            throw std::out_of_range("Index out of range");
        }
        return items[index];
    }

    // �ƶ�Ԫ��
    void move(size_t oldIndex, size_t newIndex) {
        if (oldIndex >= items.size() || newIndex >= items.size()) {
            throw std::out_of_range("Index out of range");
        }
        T movedItem = items[oldIndex];
        items.erase(items.begin() + oldIndex);
        items.insert(items.begin() + newIndex, movedItem);
        emitCollectionChanged(movedItem, "Move", newIndex);
    }

private:
    std::vector<T> items;

    // �������ϸ����¼�
    void emitCollectionChanged(const T& item, const std::string& action, size_t index) {
        collectionChanged(item, action, index);
    }

    // �������Ը����¼�
    void emitPropertyChanged(const std::string& propertyName) {
        propertyChanged(propertyName);
    }
};

#endif // COMM_OBSERVABLECOLLECTION_H_
