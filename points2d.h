// Written By Shane Mindreau
// Few comments describing the class Points2D

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

// Place comments that provide a brief explanation of the class,
// and its sample usage.
template<typename Object>
class Points2D {
  private:
    // Sequence of points.
    std::array<Object, 2> *sequence_;

    // Size of sequence.
    size_t size_;

  public:
    // Default "big five" -- you have to alter them for your assignment.
    // That means that you will remove the "= default" statement.
    //  and you will provide an implementation.
    
    // Zero-parameter constructor.
    // Set size to 0.
    Points2D(): sequence_(nullptr), size_{0} {};

    // Copy-constructor.
    Points2D(const Points2D &rhs){
        size_ = rhs.size_;
        sequence_ = new std::array<Object, 2>[size_];
        for(size_t i = 0; i < size_; i++) {
            sequence_[i] = rhs.sequence_[i];
            // sequence_[i][1] = rhs.sequence_[i][1];
        }
    };

    // Copy-assignment. If you have already written
    // the copy-constructor and the move-constructor
    // you can just use:
    // {
    // Points2D copy = rhs;
    // std::swap(*this, copy);
    // return *this;
    // }
    Points2D& operator=(const Points2D &rhs) {
        Points2D copy = rhs;
        std::swap(*this, copy);
        return *this;
    };

    // Move-constructor.
    Points2D(Points2D &&rhs){
        size_ = rhs.size_;
        sequence_ = rhs.sequence_;
        rhs.sequence_ = nullptr;
        rhs.size_ = 0;
    };

    // Move-assignment.
    // Just use std::swap() for all variables.
    Points2D& operator=(Points2D &&rhs) {
        std::swap(size_, rhs.size_);
        std::swap(sequence_, rhs.sequence_);
        return *this;
    };

    ~Points2D(){
        size_ = 0;
        delete [] sequence_;
        sequence_ = nullptr;
    };

    // End of big-five.

    // One parameter constructor.
    Points2D(const std::array<Object, 2>& item) {
        size_ = 1;
        sequence_ = new std::array<Object, 2>(item);
    }

    size_t size() const {
        return size_;
    }

    // @location: an index to a location in the sequence.
    // @returns the point at @location.
    // const version.
    // abort() if out-of-range.
    const std::array<Object, 2>& operator[](size_t location) const {
        if(location >= size_)
            abort();
        return sequence_[location];
    }

    //  @c1: A sequence.
    //  @c2: A second sequence.
    //  @return their sum. If the sequences are not of the same size, append the
    //    result with the remaining part of the larger sequence.
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
    // **** Add the ""
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
        out <<  std::endl;
        return out;
    }

    // Overloading the >> operator.
    // Read a chain from an input stream (e.g., standard input).
    friend std::istream &operator>>(std::istream &in, Points2D &some_points) {
        // Extracts the first num (size) from string
        size_t size;
        in >> size;
        // Assigns the remaining string to 'line'
        // std::string line;
        // std::getline(in, line);

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
        
        // //Checking that there is an even number of inputs...
        // std::string num;
        // int count = 0;
        // std::stringstream ss2(line);
        // while(ss2 >> num){
        //     count++;
        // }

        // //Reset stringstream to the beginning of string
        // ss2.clear();
        // ss2.seekg(0);
        // count = 0;

        // //Checking the numbers' data type (doubles or ints)
        // bool intTrue = (line.find('.') == std::string::npos) ? true : false;


        // delete[] some_points.sequence_;
        // some_points.sequence_ = new std::array<Object, 2>[size];

        // if(intTrue) {
        //     //integers
        //     auto next;
        //     size_t itr = 0;
        //     while(ss2 >> next) {
        //         if(next) {
        //             some_points.sequence_[count][itr] = next;
        //             if(itr == 1) {
        //                 count++;
        //                 itr = 0;
        //             } else {
        //                 itr++;
        //             }
        //         } else {
        //             std::cerr << "ERROR";
        //             std::abort();
        //         }

        //     }
        // } else {
        //     //doubles
        //     double next;
        //     size_t itr = 0;
        //     while(ss2 >> next) {
        //         if(next) {
        //             some_points.sequence_[count][itr] = next;
        //             if(itr == 1) {
        //                 count++;
        //                 itr = 0;
        //             } else {
        //                 itr++;
        //             }
        //         } else {
        //             std::cerr << "ERROR";
        //             //std::abort();
        //         }

        //     }
        // }
        some_points.size_ = size;

        // std::cout << std::endl;

        return in;
    }


};

}  // namespace teaching_project
#endif // CSCI_335_HOMEWORK1_Points2D_H_
