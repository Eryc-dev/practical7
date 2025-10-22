#ifndef Tree_hpp
#define Tree_hpp

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <climits>
#include <stdexcept> 

template <typename T>
class Heap
{
private:
    typedef std::vector<T> heap;
    typedef typename heap::size_type heapIndex;

    heap tree;

    void heapifyUp(heapIndex index)
    {
        if (index <= 1) return; 
        heapIndex parentIndex = getParentPosition(index);

        while (index > 1 && tree[index] < tree[parentIndex])
        {
            std::swap(tree[index], tree[parentIndex]);
            index = parentIndex;
            parentIndex = getParentPosition(index);
        }
    }

    heapIndex getLeftChildPosition(heapIndex i)
    {
        return (2 * i);
    }

    heapIndex getRightChildPosition(heapIndex i)
    {
        return (2 * i) + 1;
    }

    heapIndex getParentPosition(heapIndex i)
    {
        return (heapIndex)std::floor(i / 2);
    }

    void heapifyDown(heapIndex index)
    {
        heapIndex leftChildIndex = this->getLeftChildPosition(index);
        heapIndex rightChildIndex = this->getRightChildPosition(index);
        heapIndex smallest = index;

        if (leftChildIndex < this->tree.size() && this->tree[leftChildIndex] < this->tree[smallest])
        {
            smallest = leftChildIndex;
        }

        if (rightChildIndex < this->tree.size() && this->tree[rightChildIndex] < this->tree[smallest])
        {
            smallest = rightChildIndex;
        }

        if (smallest != index)
        {
            std::swap(this->tree[index], this->tree[smallest]);
            this->heapifyDown(smallest);
        }
    }

public:

    Heap()
    {
        this->tree.push_back((T)NULL);
    }

    Heap(std::vector<T> initial_values)
    {
        tree.push_back((T)NULL); 
        for(const auto& val : initial_values) {
            insert(val);
        }
    }

    bool isHeapEmpty()
    {
        return this->tree.size() <= 1;
    }

    void printHeap()
    {
        this->printVector(this->tree);
    }

    void heapify(std::vector<T> tree_vals)
    {
        this->tree.assign(tree_vals.begin(), tree_vals.end());
        this->tree.insert(this->tree.begin(), (T)NULL);
        for (heapIndex index = (this->tree.size() - 1) / 2; index >= 1; index--)
        {
            this->heapifyDown(index);
        }
    }

    void printVector(std::vector<T> numVector)
    {
        std::cout << "[ ";
        for (heapIndex index = 1; index < numVector.size(); index++)
        {
            std::cout << numVector.at(index);
            if (index != (numVector.size() - 1))
            {
                std::cout << ", ";
            }
        }
        std::cout << " ]" << std::endl;
    }

    T popTop()
    {
        if (this->isHeapEmpty())
        {
            throw std::out_of_range("Heap is empty");
        }
        const heapIndex ROOT_INDEX = 1;

        T topElement = this->tree.at(ROOT_INDEX);
        this->tree.at(ROOT_INDEX) = this->tree.back();
        this->tree.pop_back();

        if (!isHeapEmpty()) {
            this->heapifyDown(ROOT_INDEX);
        }
        return topElement;
    }
    
    void insert(T element)
    {
        tree.push_back(element);
        heapifyUp(tree.size() - 1);
    }

    void remove(T value)
    {
        heapIndex indexToRemove = 0;
        bool found = false;
        for (heapIndex i = 1; i < tree.size(); ++i) {
            if (tree[i] == value) {
                indexToRemove = i;
                found = true;
                break;
            }
        }

        if (!found) {
            return;
        }

        tree[indexToRemove] = tree.back();
        tree.pop_back();

        if (!isHeapEmpty() && indexToRemove < tree.size()) {

            if (indexToRemove > 1 && tree[indexToRemove] < tree[getParentPosition(indexToRemove)]) {
                heapifyUp(indexToRemove);
            } else {
                heapifyDown(indexToRemove);
            }
        }
    }

    T getMin()
    {
        if (isHeapEmpty()) {
            throw std::out_of_range("Heap is empty");
        }
        return tree.at(1);
    }
};

#endif
