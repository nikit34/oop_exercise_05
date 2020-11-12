#pragma once
#include <iostream>
#include <memory>
#include <algorithm>


template<typename T>
class Queue {
private:
	class Node {
	public:
		Node(T val): next{nullptr}, prev{next}, value{val} {};
		friend class Queue;

	private:
		std::shared_ptr<Node> next;
		std::weak_ptr<Node> prev;
		T value;
	};

public:
	class ForwardIterator {
	public:
		using value_type = T;
	    using reference = T&;
	    using pointer = T*;
	    using difference_type = ptrdiff_t;
	    using iterator_category = std::forward_iterator_tag;
		friend class Queue;

		ForwardIterator(std::shared_ptr<Node> it = nullptr): ptr{it} {};
		ForwardIterator(const ForwardIterator &other): ptr{other.ptr} {};

		ForwardIterator operator++() {
			if (this->ptr.lock() == nullptr) {
				return *this;
			}
			this->ptr = ptr.lock()->next;
			return *this;
		}

		ForwardIterator operator++(int s) {
			if (ptr.lock() == nullptr) {
				return *this;
			}
			ForwardIterator old{this->ptr.lock()};
			++(*this);
			return old;
		}

		T& operator*() {
			return this->ptr.lock()->value;
		}

		const T& operator*() const {
			return this->ptr.lock()->value;
		}

		std::shared_ptr<Node> operator->() {
			return this->ptr.lock();
		}

		std::shared_ptr<const Node> operator->() const {
			return this->ptr.lock();
		}

		bool operator==(const ForwardIterator &rhs) const {
			return this->ptr.lock() == rhs.ptr.lock();
		}

		bool operator!=(const ForwardIterator &rhs) const {
			return this->ptr.lock() != rhs.ptr.lock();
		}

		ForwardIterator Next() const {
			if (this->ptr.lock() == nullptr)
				return ForwardIterator{};
			return this->ptr.lock()->next;
		}

	private:
		std::weak_ptr<Node> ptr;
	};

	Queue(): head{nullptr}, tail{head}, size{0} {};

	void Push(const T& val) {
		if (!head) {
			head = std::make_shared<Node>(val);
			tail = head;
		} else {
			std::shared_ptr<Node> newElem = std::make_shared<Node>(val);
			newElem->prev = tail;
			tail.lock()->next = newElem;
			tail = newElem;
		}
		size++;
	}

	void Pop() {
		if (this->head) {
			head = head->next;
			size--;
		}
	}

	ForwardIterator Insert(const ForwardIterator it, const T& val) {
		if (it == ForwardIterator{}) {
			if (tail.lock() == nullptr) {
				Push(val);
				return Begin();
			}
			std::shared_ptr<Node> newElem = std::make_shared<Node>(val);
			newElem->prev = tail;
			tail.lock()->next = newElem;
			tail = newElem;
			size++;
			return newElem;
		}
		if (it == Begin()) {
			std::shared_ptr<Node> newElem = std::make_shared<Node>(val);
			newElem->next = it.ptr.lock();
			it->prev.lock() = newElem;
			head = newElem;
			size++;
			return newElem;
		}
		std::shared_ptr<Node> newElem = std::make_shared<Node>(val);
		newElem->next = it.ptr.lock();
		it->prev.lock()->next = newElem;
		newElem->prev = it->prev;
		it->prev.lock() = newElem;
		size++;
		return newElem;
	}


	ForwardIterator Erase(const ForwardIterator it) {
		if (it == ForwardIterator{}) {
			return End();
		}
		if (it->prev.lock() == nullptr && head == tail.lock()) {
			head = nullptr;
			tail = head;
			size = 0;
			return End();
		}
		if (it->prev.lock() == nullptr) {
			it->next->prev.lock() = nullptr;
			head = it->next;
			size--;
			return head;
		}
		ForwardIterator res = it.Next();
		if (res == ForwardIterator{}) {
			it->prev.lock()->next = nullptr;
			size--;
			return End();
		}
		it->next->prev = it->prev;
		it->prev.lock()->next = it->next;
	    size--;
		return res;
	}

	const T Front() {
		if (head == nullptr)
			throw std::out_of_range("Empty item");
		return head->value;
	}

	const T& Front() const {
		if (head == nullptr)
			throw std::out_of_range("Empty item");
		return head->value;
	}

	const T Back() {
		if (head == nullptr)
			throw std::out_of_range("Empty item");
		return tail.lock()->value;
	}

	const T& Back() const {
		if (head == nullptr)
			throw std::out_of_range("Empty item");
		return tail.lock()->value;
	}

	ForwardIterator Begin() {
		return head;
	}

	ForwardIterator End() {
		return ForwardIterator{};
	}

	bool Empty() const {
		return size == 0;
	}

	size_t Size() const {
		return size;
	}

	void Swap(Queue &rhs) {
		std::shared_ptr<Node> temp = head;
		head = rhs.head;
		rhs.head = temp;
	}

	void Clear() {
		head = nullptr;
		tail = head;
		size = 0;
	}

	void Print() {
		ForwardIterator it = Begin();
		std::for_each(Begin(), End(), [it, this](auto e)mutable{
			std::cout << e;
			if (it.Next() != this->End()) {
				std::cout << " <- ";
			}
			it++;
		});
		std::cout << "\n";
	}

private:

	std::shared_ptr<Node> head;
	std::weak_ptr<Node> tail;
	size_t size;
};