#include <kore/type_traits/list.hpp>
#include <kore/containers/heap.hpp>
#include <kore/containers/utility.hpp>
#include <map>

#include <iostream>

int main() {
    kore::k_heap<int> queue;
    queue.insert(2);
    queue.insert(3);
    queue.insert(2);
    queue.insert(1);
    queue.insert(2);
    queue.insert(5);
    queue.insert(3);
    queue.insert(1);
    std::cout << "All inserterd" << std::endl;
    // std::cout << kore::utils::to_string(queue.storage()) << std::endl;
    while (!queue.empty()) {
        std::cout << queue.top() << std::endl;
         // std::cout << kore::utils::to_string(queue.storage()) << std::endl;
    }
    return 0;
}
