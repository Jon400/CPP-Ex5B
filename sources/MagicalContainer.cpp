# include "MagicalContainer.hpp"
#include <climits>
#include <stdexcept>
#include <cmath>
#include <algorithm>

/*
    here is empty implementation for magical container and its iterators
*/
int ariel::MagicalContainer::operator[](int) const{
    return -1;
}
void ariel::MagicalContainer::validate(){
    std::size_t i = 0, j = 0;
    while (i < this->elements.size())
    {
        if (isPrime(this->elements[i]))
        {
            this->prime_elements[j] = &this->elements[i];
            j++;
        }
        i++; 
    }  
}
ariel::MagicalContainer::MagicalContainer(){
    this->elements = std::vector<int>();
    this->numOfElements = 0;
}
ariel::MagicalContainer::~MagicalContainer(){}
void ariel::MagicalContainer::addElement(int element){
    for (std::size_t i = 0; i < this->numOfElements; i++)
    {
        if (this->elements[i] == element)
        {
            return;
        }
    }
    for (std::size_t i = 0; i < this->numOfElements; i++)
    {
        // add element to the sorted way
        if (this->elements[i] > element)
        {
            this->elements.insert(this->elements.begin() + (long)i, element);
            this->numOfElements++;
            if (ariel::isPrime(element)){
                this->prime_elements.push_back(&this->elements[i]);
            }
            validate();
            return;
        }
    }
    this->elements.push_back(element);
    if (ariel::isPrime(element)){
        this->prime_elements.push_back(&this->elements[this->elements.size() - 1]);
    }
    validate();
    this->numOfElements++;
}
void ariel::MagicalContainer::removeElement(int element){
    for (std::size_t i = 0; i < this->numOfElements; i++)
    {
        if (this->elements[i] == element)
        {
            int * element_ptr = &this->elements[i];
            this->elements.erase(this->elements.begin() + (long)i);
            if (ariel::isPrime(element)){
                this->prime_elements.erase(std::find(this->prime_elements.begin(), this->prime_elements.end(), element_ptr));
            }
            validate();
            this->numOfElements--;
            return;
        }
    }
    throw std::runtime_error("element not found");
}
int ariel::MagicalContainer::size(){
    return this->numOfElements;
}
ariel::MagicalContainer *ariel::MagicalContainer::Iterator::getContainer() const{
    return this->container;
}
// int *ariel::MagicalContainer::Iterator::getCurrent() const{
//     return this->current;
// }
ariel::MagicalContainer::Iterator::Iterator() : container(nullptr), it() {}
ariel::MagicalContainer::Iterator::Iterator(MagicalContainer &container) : container(&container), it(container.elements.begin()) {}
// void ariel::MagicalContainer::Iterator::setCurrent(int * index){
//     this->current = index;
// }
std::vector<int>::iterator ariel::MagicalContainer::Iterator::getIterator() const{
    return this->it;
}
void ariel::MagicalContainer::Iterator::setIterator(const std::vector<int>::iterator & iterator){
    this->it = iterator;
}
ariel::MagicalContainer::Iterator::Iterator(const Iterator &other_iterator) : container(other_iterator.container), it(other_iterator.it) {}
ariel::MagicalContainer::Iterator::~Iterator(){}
bool ariel::MagicalContainer::Iterator::operator==(const Iterator & other) const
{
    return false;
}
bool ariel::MagicalContainer::Iterator::operator!=(const Iterator & other) const
{
    return false;
}
bool ariel::MagicalContainer::Iterator::operator<(const Iterator & other) const
{
    return false;
}
bool ariel::MagicalContainer::Iterator::operator>(const Iterator & other) const
{
    return false;
}
int ariel::MagicalContainer::Iterator::operator*() const
{
    return *it;
}
ariel::MagicalContainer::Iterator &ariel::MagicalContainer::Iterator::operator++()
{
    return *this;
}
ariel::MagicalContainer::AscendingIterator::AscendingIterator() : Iterator() {}
ariel::MagicalContainer::AscendingIterator::AscendingIterator(MagicalContainer & container) : Iterator(container){
    this->setIterator(this->getContainer()->elements.begin());
}
ariel::MagicalContainer::AscendingIterator::AscendingIterator(const AscendingIterator & other_iterator):
Iterator(other_iterator){
    this->setIterator(other_iterator.getIterator());
}
ariel::MagicalContainer::AscendingIterator::~AscendingIterator() {}
ariel::MagicalContainer::AscendingIterator& ariel::MagicalContainer::AscendingIterator::operator=(const AscendingIterator& Iterator){
    if (this->getContainer() != Iterator.getContainer())
    {
        throw std::runtime_error("iterators are not from the same container");
    }
    this->setIterator(Iterator.getIterator());
    return *this;
}
bool ariel::MagicalContainer::AscendingIterator::operator==(const AscendingIterator& other) const{
    // throw an exception if the iterators are not from the same container
    if (this->getContainer() != other.getContainer())
    {
        throw std::runtime_error("iterators are not from the same container");
    }
    return this->getIterator() == other.getIterator();
}
// bool ariel::MagicalContainer::AscendingIterator::operator==(const Iterator &) const{
//     return false;
// }
bool ariel::MagicalContainer::AscendingIterator::operator!=(const AscendingIterator &other) const
{
    return !(*this == other);
}
// bool ariel::MagicalContainer::AscendingIterator::operator!=(const Iterator &) const{
//     return false;
// }
bool ariel::MagicalContainer::AscendingIterator::operator<(const AscendingIterator &other) const
{
    return this->getIterator() < other.getIterator();
}
// bool ariel::MagicalContainer::AscendingIterator::operator<(const Iterator &) const{
//     return false;
// }
bool ariel::MagicalContainer::AscendingIterator::operator>(const AscendingIterator &other) const
{
    return other < *this;
}
// bool ariel::MagicalContainer::AscendingIterator::operator>(const Iterator &) const{
//     return false;
// }
int ariel::MagicalContainer::AscendingIterator::operator*() const
{
    return *(this->getIterator());
}
ariel::MagicalContainer::AscendingIterator& ariel::MagicalContainer::AscendingIterator::operator++(){
    if ( this->getIterator() == this->getContainer()->elements.end()){
        throw std::runtime_error("out of range");
    }
    this->setIterator(this->getIterator() + 1);
    return *this;
}
ariel::MagicalContainer::AscendingIterator ariel::MagicalContainer::AscendingIterator::begin() const{
    return AscendingIterator(*this->getContainer());
}
ariel::MagicalContainer::AscendingIterator ariel::MagicalContainer::AscendingIterator::end() const
{
    AscendingIterator Iterator(*this->getContainer());
    Iterator.setIterator(this->getContainer()->elements.end());
    return Iterator;
}
ariel::MagicalContainer::SideCrossIterator::SideCrossIterator() : Iterator() {}
ariel::MagicalContainer::SideCrossIterator::SideCrossIterator(MagicalContainer & container): Iterator(container){
    this->setIterator(this->getContainer()->elements.begin());
    this->rightIt = this->getContainer()->elements.end() - 1;
    this->isLeft = true;
}
ariel::MagicalContainer::SideCrossIterator::SideCrossIterator(const SideCrossIterator & other){
    this->setIterator(other.getIterator());
    this->rightIt = other.rightIt;
    this->isLeft = other.isLeft;
}
ariel::MagicalContainer::SideCrossIterator::~SideCrossIterator() {}
ariel::MagicalContainer::SideCrossIterator& ariel::MagicalContainer::SideCrossIterator::operator=(const SideCrossIterator& other){
    if (this->getContainer() != other.getContainer())
    {
        throw std::runtime_error("iterators are not from the same container");
    }
    this->~SideCrossIterator();
    this->setIterator(other.getIterator());
    this->rightIt = other.rightIt;
    this->isLeft = other.isLeft;
    return *this;
}
// bool ariel::MagicalContainer::SideCrossIterator::operator==(const Iterator &) const{
//     return false;
// }
bool ariel::MagicalContainer::SideCrossIterator::operator==(const SideCrossIterator &other) const
{
    return this->getIterator() == other.getIterator() && this->rightIt == other.rightIt && this->isLeft == other.isLeft;
}
// bool ariel::MagicalContainer::SideCrossIterator::operator!=(const Iterator &) const{
//     return false;
// }
bool ariel::MagicalContainer::SideCrossIterator::operator!=(const SideCrossIterator &other) const
{
    return !(*this == other);
}
// bool ariel::MagicalContainer::SideCrossIterator::operator<(const Iterator &) const{
//     return false;
// }
bool ariel::MagicalContainer::SideCrossIterator::operator<(const SideCrossIterator &other) const
{
    if (this->isLeft && other.isLeft){
        return this->getIterator() < other.getIterator();
    }
    else if (!this->isLeft && !other.isLeft){
        return this->rightIt < other.rightIt;
    }
    else{
        return this->rightIt < other.rightIt || this->getIterator() < other.getIterator();
    }
}
// bool ariel::MagicalContainer::SideCrossIterator::operator>(const Iterator &) const{
//     return false;
// }
bool ariel::MagicalContainer::SideCrossIterator::operator>(const SideCrossIterator &other) const
{
    return other < *this;
}
int ariel::MagicalContainer::SideCrossIterator::operator*(){
    if (this->isLeft){
        return *(this->getIterator());
    }
    else{
        return *(this->rightIt);
    }
}
ariel::MagicalContainer::SideCrossIterator& ariel::MagicalContainer::SideCrossIterator::operator++(){
    if (this->getIterator() > this->rightIt){
        throw std::runtime_error("Iterator out of range");
    }
    if (this->isLeft){
        this->setIterator(this->getIterator() + 1);
        this->isLeft = false;
    }
    else{
        this->rightIt--;
        this->isLeft = true;
    }
    return *this;
}
ariel::MagicalContainer::SideCrossIterator ariel::MagicalContainer::SideCrossIterator::begin() const{
    return SideCrossIterator(*this->getContainer());
}
ariel::MagicalContainer::SideCrossIterator ariel::MagicalContainer::SideCrossIterator::end() const{
    SideCrossIterator Iterator(*this->getContainer());
    // get the middle of the container
    Iterator.setIterator(this->getContainer()->elements.begin() + (this->getContainer()->elements.size() / 2));
    Iterator.rightIt  = this->getContainer()->elements.end() -  (this->getContainer()->elements.size() / 2);
    if (this->getContainer()->elements.size() % 2 == 1){
        Iterator.isLeft = false;
        Iterator.setIterator(Iterator.getIterator() + 1);
        Iterator.rightIt--;
    }
    else{
        Iterator.isLeft = true;
        Iterator.rightIt--;
    }
    return Iterator;
}
ariel::MagicalContainer::PrimeIterator::PrimeIterator(){}
ariel::MagicalContainer::PrimeIterator::PrimeIterator(MagicalContainer & container): Iterator(container){
    this->primeIt = this->getContainer()->prime_elements.begin();
}
ariel::MagicalContainer::PrimeIterator::PrimeIterator(const PrimeIterator & other) : Iterator(other){
    this->primeIt = other.primeIt;
}
ariel::MagicalContainer::PrimeIterator::~PrimeIterator() {}
ariel::MagicalContainer::PrimeIterator& ariel::MagicalContainer::PrimeIterator::operator=(const PrimeIterator& other){
    if (this->getContainer() != other.getContainer())
    {
        throw std::runtime_error("iterators are not from the same container");
    }
    this->~PrimeIterator();
    this->primeIt = other.primeIt;
    return *this;
}
// bool ariel::MagicalContainer::PrimeIterator::operator==(const Iterator &) const{
//     return false;
// }
bool ariel::MagicalContainer::PrimeIterator::operator==(const PrimeIterator &other) const
{
    return this->primeIt == other.primeIt;
}
// bool ariel::MagicalContainer::PrimeIterator::operator!=(const Iterator &) const{
//     return false;
// }
bool ariel::MagicalContainer::PrimeIterator::operator!=(const PrimeIterator &other) const
{
    return !(*this == other);
}
// bool ariel::MagicalContainer::PrimeIterator::operator<(const Iterator &) const{
//     return false;
// }
bool ariel::MagicalContainer::PrimeIterator::operator<(const PrimeIterator &other) const
{
    return this->primeIt < other.primeIt;
}
// bool ariel::MagicalContainer::PrimeIterator::operator>(const Iterator &) const{
//     return false;
// }
bool ariel::MagicalContainer::PrimeIterator::operator>(const PrimeIterator &other) const
{
    return other < *this;
}
int ariel::MagicalContainer::PrimeIterator::operator*(){
    return *(*(this->primeIt));
}
ariel::MagicalContainer::PrimeIterator& ariel::MagicalContainer::PrimeIterator::operator++(){
    if (this->primeIt == this->getContainer()->prime_elements.end()){
        throw std::runtime_error("out of range");
    }
    this->primeIt++;
    return *this;
}
ariel::MagicalContainer::PrimeIterator ariel::MagicalContainer::PrimeIterator::begin() const{
    return PrimeIterator(*this->getContainer());
}
ariel::MagicalContainer::PrimeIterator ariel::MagicalContainer::PrimeIterator::end() const{
    PrimeIterator Iterator(*this->getContainer());
    Iterator.primeIt = this->getContainer()->prime_elements.end();
    return Iterator;
}

bool ariel::isPrime(int num){
    if (num <= 1){
        return false;
    }
    std::size_t i;
    for (i = 2; i <= std::sqrt(num); i++)
    {
        if (num % (int)i == 0)
        {
            return false;
        }
    }
    return true;
}
