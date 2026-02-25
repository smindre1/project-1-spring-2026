// Written By Shane Mindreau 2/24/2026
#ifndef CSCI335_HOMEWORK1_POINTS2D_H_
#define CSCI335_HOMEWORK1_POINTS2D_H_

#include <array>
#include <iostream>
#include <cstddef>
#include <string>
#include <sstream>
#include <vector>
// Applies namespace to the class Points2D
namespace teaching_project {

// Points2D is a class that records a sequence of coordinate pairs (or points) as well as the number of coordinates (size) in the sequence.
// The sequence is an array pointer with each coordinate within the array being an array of size two. (ex: [[2, 3], [8,9], [10,14]] )
template<typename Object>
class Points2D {
  private:
    // Sequence of points recorded as an array pointer.
    std::array<Object, 2> *sequence_;

    // Size of sequence.
    size_t size_;

  public:
    // Zero-parameter constructor.
    // @brief: Sets sequence pointer to nullptr and size_ to 0.
    Points2D(): sequence_(nullptr), size_{0} {};

    // Copy-constructor.
    // @pre: Takes a const ref to a Points2D object
    // @brief: Sets the new Points2D object to the same value as the const ref Points2D object
    Points2D(const Points2D &rhs){
        size_ = rhs.size_;
        sequence_ = new std::array<Object, 2>[size_];
        for(size_t i = 0; i < size_; i++) {
            sequence_[i] = rhs.sequence_[i];
        }
    };

    // Copy-assignment.
    // @brief: Copies the values the parameter const ref Points2D object on the right of the '=' operator to the Points2D object on the left of the operator.
    Points2D& operator=(const Points2D &rhs) {
        Points2D copy = rhs;
        std::swap(*this, copy);
        return *this;
    };

    // Move-constructor.
    // @brief: Transfers the data/values from the parameter Points2D object to a new Points2D object.
    // @example: Points2D<int> e = move(c);
    // @example explained: the values from obj c are transferred to obj e.
    Points2D(Points2D &&rhs){
        size_ = rhs.size_;
        sequence_ = rhs.sequence_;
        rhs.sequence_ = nullptr;
        rhs.size_ = 0;
    };

    // Move-assignment.
    // @brief: The values are swapped between two Points2D objects
    // @example: e = move(c);
    // @example explained: the values from obj c are swapped to obj e, and vice versa.
    Points2D& operator=(Points2D &&rhs) {
        std::swap(size_, rhs.size_);
        std::swap(sequence_, rhs.sequence_);
        return *this;
    };

    // Points2D Destructor
    // @brief: prepares the object to be deleted, and free up memory
    ~Points2D(){
        size_ = 0;
        delete [] sequence_;
        sequence_ = nullptr;
    };

    // One parameter constructor.
    // @brief: Constructs a Points2D object given a const ref parameter to an array of points
    Points2D(const std::array<Object, 2>& item) {
        size_ = 1;
        sequence_ = new std::array<Object, 2>(item);
    }

    // Size function
    // @brief: retrieve the size of the sequence from the object's private members
    size_t size() const {
        return size_;
    }

    // Square bracket - operator overloading
    // @brief: given an index value, the operator will provide the point at that location in the sequence.
    // @returns the point at @location.
    // const version, means it cannot modify the sequence.
    // @exception: if the index provided is out-of-range, then the function will abort().
    const std::array<Object, 2>& operator[](size_t location) const {
        if(location >= size_)
            abort();
        return sequence_[location];
    }

    // @c1: A sequence.
    // @c2: A second sequence.
    // @brief: given two Points2D objects the sequences will be combined.
    // @return their sum. If the sequences are not of the same size, append the result with the remaining part of the larger sequence.
    // For example, sequence [ [a, b], [c, d]] will be added to [ [e, f], [g, h], [i, j]] to get [ [a+e, b+f], [c+g, d+h], [i, j]]
    friend Points2D operator+(const Points2D &c1, const Points2D &c2) {
        if(c1.size_ != c2.size_){
            //Finds which sequence is bigger/smaller
            size_t maxSize = (c1.size_ > c2.size_) ? c1.size_ : c2.size_;
            size_t minSize = (c1.size_ < c2.size_) ? c1.size_ : c2.size_;
    
            std::array<Object, 2> *c3 = new std::array<Object, 2>[maxSize];
            
            for(size_t i = 0; i<minSize; i++) {
                c3[i][0] = c1.sequence_[i][0] + c2.sequence_[i][0];
                c3[i][1] = c1.sequence_[i][1] + c2.sequence_[i][1];
            }

            std::array<Object, 2> *big = (c1.size_ > c2.size_) ? c1.sequence_ : c2.sequence_;
            for(size_t i = minSize; i < maxSize; i++) {
                c3[i][0] = big[i][0];
                c3[i][1] = big[i][1];
            }
            Points2D newPoints2D;
            newPoints2D.size_ = maxSize;
            newPoints2D.sequence_ = c3;

            return newPoints2D;

        } else {
            std::array<Object, 2> *c3 = new std::array<Object, 2>[c1.size_];
            
            for(size_t i = 0; i<c1.size_; i++) {
                c3[i][0] = c1.sequence_[i][0]+ c2.sequence_[i][0];
                c3[i][1] = c1.sequence_[i][1] + c2.sequence_[i][1];
            }
            Points2D newPoints2D;
            newPoints2D.size_ = c1.size_;
            newPoints2D.sequence_ = c3;

            return newPoints2D;
        }
    }

    // Overloading the << operator.
    // @brief: Given a Points2d object, its sequence will be taken and converted to a stringstream object and returned
    // @return: An ostream object 
    friend std::ostream &operator<<(std::ostream &out, const Points2D &some_points) {
        if(some_points.size_ == 0){
            out << "()";
        }
        for(size_t i = 0; i < some_points.size_; i++) {
            if(!some_points.sequence_[i][0] || !some_points.sequence_[i][1]) {
                out << "()";
            } else {
                out << "("<< some_points.sequence_[i][0] << ", " << some_points.sequence_[i][1] << ")";
                if(i != some_points.size_ - 1) {
                    out << " ";
                }
            }
        }
        out << std::endl;
        return out;
    }

    // Overloading the >> operator.
    // @brief: Read a chain from an input stream (e.g., standard input) and place them in the Points2D sequence.
    friend std::istream &operator>>(std::istream &in, Points2D &some_points) {
        // Extracts the first number, which is the size, from the input string
        size_t size;
        in >> size;

        if(some_points.sequence_){
            delete[] some_points.sequence_;
        }
        some_points.sequence_ = new std::array<Object, 2>[size];
        for(size_t i = 0; i < size; i++) {
            if(!in) {
                std::cerr << "ERROR";
                std::abort();
            }
            in >> some_points.sequence_[i][0];
            if(!in) {
                std::cerr << "ERROR";
                std::abort();
            }
            in >> some_points.sequence_[i][1];
        }
        some_points.size_ = size;

        return in;
    }


};

}  // namespace teaching_project
#endif // CSCI_335_HOMEWORK1_Points2D_H_
