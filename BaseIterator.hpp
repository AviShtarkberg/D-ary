#ifndef BASE_ITERATOR_HPP
#define BASE_ITERATOR_HPP

/**
 * @brief Base class for tree iterators.
 *
 * This abstract class provides the interface for different types of tree iterators.
 * It defines the required methods for traversal of a tree.
 */
template <typename T>
class BaseIterator
{
public:
    virtual ~BaseIterator() = default;

    /**
     * @brief Advances the iterator to the next node in the traversal.
     * @return Reference to the updated iterator.
     */
    virtual BaseIterator &operator++() = 0;

    /**
     * @brief Compares two iterators for inequality.
     * @param other The other iterator to compare with.
     * @return True if the iterators are not equal, false otherwise.
     */
    virtual bool operator!=(const BaseIterator &other) const = 0;

    /**
     * @brief Dereferences the iterator to access the current node.
     * @return Pointer to the current node.
     */
    virtual Node<T> *operator*() const = 0;

    /**
     * @brief Dereferences the iterator to access the current node's members.
     * @return Pointer to the current node.
     */
    virtual Node<T> *operator->() const = 0;

protected:
    Node<T> *_current; // Pointer to the current node in the traversal.
};

#endif
