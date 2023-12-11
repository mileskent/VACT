#include "sllist.hpp"

int main (void) {
    SLList list;
    Word w1, w2, w3;
    w1.setdef ("one");
    w2.setdef ("two");
    w3.setdef ("three");
    list.push_back_node(w1);
    list.push_back_node(w2);
    list.push_back_node(w3);
    list.showlist(list.get_head());
    return 0;
}
