#include <functional>
#include "../list.h"
#include "../Exceptions.h"
#include "../mtmtest.h"
#include <string>

/**
 * Function object for finding a target integer
 */
class EqualTo {
private:
    int target;
public:
    EqualTo(int i) : target(i) {}
    bool operator()(const int& i) const {
        return i == target;
    }
};

static void IteratorTests(){
    using std::string;
    using mtm::ListExceptions::ElementNotFound;
    List<unsigned int > list;
    list.begin();
    list.insert(1, list.end());
    list.insert(2, list.end());
    list.insert(3, list.end());
    list.insert(4, list.end());
    List<unsigned int >::Iterator it=list.begin();
    unsigned int counter=1;
    /** ------------------Move forward on list----------------------------- */
    for(;it!=list.end();it++){
        ASSERT_TRUE((*(it))==counter);
        counter++;
    }
    /** ------------------end Dereffrence exception-------------------------- */
    ASSERT_THROWS(mtm::ListExceptions::ElementNotFound,(*it));
    --it;
    counter=4;
    /** ------------------Move backwards on list----------------------------- */
    for (;it!=(--(list.begin())); it--){
        ASSERT_TRUE((*(it))==counter);
        counter--;
    }
    List<unsigned int > list2;
    list2.begin();
    list2.insert(1, list2.end());
    list2.insert(2, list2.end());
    list2.insert(3, list2.end());
    list2.insert(4, list2.end());
    List<unsigned int>::Iterator it2=list2.begin();
    /** ------------------check iterator == operator ------------------------ */
    ASSERT_TRUE(it!=it2);
    ASSERT_TRUE(it2!=it);
    ASSERT_FALSE(it==it2);
    ASSERT_FALSE(it2==it);
    List<unsigned int>::Iterator it3=it;
    ASSERT_TRUE(it==it3);
    ASSERT_FALSE(it3==it2);
}

static void ListTests() {
    using std::string;
    using mtm::ListExceptions::ElementNotFound;
    List<string> list, list2;
    list.begin();
    list.insert("Amir", list.end());
    list.insert("Shahar", list.begin());
    list.insert("Sagi", list.end());
    list.insert("Guy", list.begin());
    list.insert("Michel", (--list.end()));
    list.insert("Amit", (list.begin()++));
/** ------------------check list throws---------------------------- */
    ASSERT_THROWS(ElementNotFound, list2.insert(" ", list.begin()));
    ASSERT_THROWS(ElementNotFound, list.insert(")-:", list2.end()));
    /** ------------------check list random accessesed move remove---------- */
    for (int j = 0; j < 100; j++) {
        int random = rand() % 4;
        int i = 1;
        List<string>::Iterator it = list.begin();
        for (; i < random; it++, i++) {}
        if (random % 2 == 0) {
            list.insert(")-:", it);
        } else {
            list.insert("(-:", it);
        }
        random = rand() % 5;
        it = list.end();
        it--;
        for (; i < random; --it, i++) {}
        list.remove(it);

    }
}
    /** ------------------check list sort for strings---------- */
void ListtestSORT() {
    List<int> list_to_sort;
    for(int j=0;j<400;j++) {
        if(j%4==0)list_to_sort.insert(1);
        if(j%4==1)list_to_sort.insert(2);
        if(j%4==2)list_to_sort.insert(3);
        if(j%4==3)list_to_sort.insert(4);
    }
    using std::string;
    list_to_sort.sort(std::less<int>());
    List<int>::Iterator iterator=list_to_sort.begin();
    int i=1;
    for(;iterator!=list_to_sort.end();iterator++,i++){
        if(i<=100)ASSERT_TRUE((*iterator)==1);
        if(i>100&&i<=200)ASSERT_TRUE((*iterator)==2);
        if(i>200&&i<=300)ASSERT_TRUE((*iterator)==3);
        if(i>300&&i<=400)ASSERT_TRUE((*iterator)==4);
    }

    /** ------------------check list find---------- */
}
void testListFind(){
    List<int> list_to_find;
    int random=rand()%1000;
    for(int j=0;j<random;j++) {
        int sec_random=rand()%1000;
        list_to_find.insert(sec_random);
    }
    list_to_find.insert(23);
    for(int j=0;j<random;j++) {
        int sec_random=rand()%1000;
        list_to_find.insert(sec_random);
    }
    list_to_find.sort(std::less<int>());
    // Should be able to find the number 23
    ASSERT_TRUE(list_to_find.find(EqualTo(23))!=list_to_find.end());
    // Should NOT be able to find the number 1000
    ASSERT_TRUE(list_to_find.find(EqualTo(1000))==list_to_find.end());
}

int run_list_tests() {
    RUN_TEST(IteratorTests);
    RUN_TEST(ListtestSORT);
    RUN_TEST(ListTests);
    RUN_TEST(testListFind);

    return 0;
}
