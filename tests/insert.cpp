//
// insert.cpp

//- если элемент уже присутствует в дереве, то метод должен вернуть false
//- если элемент не присутствует в дереве, то метод должен вернуть true

//- если вставляемый элемент меньше элемента находящегося в корне дерева, то он должен быть вставлен слева от него
//- если вставляемый элемент больше элемента находящегося в корне дерева, то он должен быть вставлен справа от него

//- если элемент уже присутствует в дереве, то метод должен не изменять значения размера дерева
//- если элемент не присутствует в дереве, то метод должен увеличить значение размера дерева на 1

#include "catch.hpp"
#include "binary_search_tree.h"

SCENARIO("if already exist")
{
    GIVEN("object")
    {
        BinarySearchTree<int> tree{1, 2, 3, 4, 5, 6, 7};
        int object= 5;
        WHEN("insert")
        {
         tree.insert(object);
            THEN("if it already in the tree")
            {
                REQUIRE(!tree.insert(object));
            }
        }
    }
}

SCENARIO("if not already exist")
{
    GIVEN("object")
    {
        BinarySearchTree<int> tree{1, 2, 3, 4, 5, 6, 7};
        int object= 9;
        WHEN("insert")
        {
            THEN("insert ok")
            {   
                REQUIRE(tree.insert(object));                
            }
        }
    }
}

SCENARIO ("If object < root")
{
    GIVEN ("object and root")
    {
        BinarySearchTree <int> tree={9,4};
        int object=1;
        BinarySearchTree <int> tree2={9,4,1};

        WHEN ("insert")
        {
            tree.insert(object);
            THEN ("insert ok. (left)") 
            { 
                REQUIRE(tree==tree2);
            }
        };
    }
}

SCENARIO ("If object > root")
{
    GIVEN ("object and root")
    {
        BinarySearchTree <int> tree={1,3};
        int object=5;
        BinarySearchTree <int> tree2={1,3,5};

        WHEN ("insert")
        {
            tree.insert(object);
            THEN ("insert ok. (right)") { REQUIRE(tree==tree2);}
        };
    }
}
