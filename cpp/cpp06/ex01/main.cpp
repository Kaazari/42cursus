#include <iostream>
#include "Serializer.hpp"
#include "Data.hpp"

int main() {
    Data data;
    data.name = "Test";
    data.value = 42;
    data.price = 19.99;

    std::cout << "Original pointer: " << &data << std::endl;
    std::cout << "Original data: " << data.name << ", " << data.value << ", " << data.price << std::endl;

    uintptr_t serialized = Serializer::serialize(&data);
    std::cout << "Serialized: " << serialized << std::endl;

    Data* deserialized = Serializer::deserialize(serialized);
    std::cout << "Deserialized pointer: " << deserialized << std::endl;
    std::cout << "Deserialized data: " << deserialized->name << ", " << deserialized->value << ", " << deserialized->price << std::endl;

    if (&data == deserialized)
        std::cout << "✅ Pointers match!" << std::endl;
    else
        std::cout << "❌ Pointers don't match!" << std::endl;

    return 0;
}
