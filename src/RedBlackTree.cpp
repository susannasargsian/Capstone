#include "RedBlackTree.h"
#include <iostream>

/*struct tree_node *tree_insert(struct tree_node *root, int data)
{
    if (root == NULL)
    {
        root = make_node(data);
    }
    else
    {
        int dir = root->data < data;

        root->link[dir] = tree_insert(root->link[dir], data);
    }

    return root;
}*/

RedBlackTree::RedBlackTree()
{
    root = new rb_tree;
    root->root = NULL;
}

void RedBlackTree::insert(Data d)
{
    tree_insert(root, d);
}

void RedBlackTree::remove(const Data& d)
{
    tree_remove(root, d);

}

void RedBlackTree::update(Data old_d, Data new_d)
{
    remove(old_d);
    insert(new_d);
}

Data RedBlackTree::getMax()
{
   tree_node* max=maximum_node(root);
   return max->data;
}

Data RedBlackTree::getMin()
{
   tree_node* min=minimum_node(root);
   return min->data;
}

int RedBlackTree::is_red( tree_node *root)
{
    return root != NULL && root->red == 1;
}

 tree_node* RedBlackTree::tree_single( tree_node *root, int dir)
{
    tree_node *save = root->link[!dir];

    root->link[!dir] = save->link[dir];
    save->link[dir] = root;

    root->red = 1;
    save->red = 0;

    return save;
}

 tree_node* RedBlackTree::tree_double( tree_node *root, int dir)
{
    root->link[!dir] = tree_single(root->link[!dir], !dir);

    return tree_single(root, dir);
}

 tree_node* RedBlackTree::make_node(Data data)
{
     tree_node *rn = new tree_node;

    if (rn != NULL)
    {
        rn->data = data;
        rn->red = 1; /* 1 is red, 0 is black */
        rn->link[0] = NULL;
        rn->link[1] = NULL;
    }

    return rn;
}

int RedBlackTree::tree_insert( rb_tree *tree, Data data)
{
    if (tree->root == NULL)
    {
        /* Empty tree case */
        tree->root = make_node(data);

        if (tree->root == NULL)
        {
            return 0;
        }
    }
    else
    {
         tree_node head = { 0 }; /* False tree root */

         tree_node *g, *t;     /* Grandparent & parent */
         tree_node *p, *q;     /* Iterator & parent */
        int dir = 0, last;

        /* Set up helpers */
        t = &head;
        g = p = NULL;
        q = t->link[1] = tree->root;

        /* Search down the tree */
        for (;;)
        {
            if (q == NULL)
            {
                /* Insert new node at the bottom */
                p->link[dir] = q = make_node(data);

                if (q == NULL)
                {
                    return 0;
                }
            }
            else if (is_red(q->link[0]) && is_red(q->link[1]))
            {
                /* Color flip */
                q->red = 1;
                q->link[0]->red = 0;
                q->link[1]->red = 0;
            }

            /* Fix red violation */
            if (is_red(q) && is_red(p))
            {
                int dir2 = t->link[1] == g;

                if (q == p->link[last])
                {
                    t->link[dir2] = tree_single(g, !last);
                }
                else
                {
                    t->link[dir2] = tree_double(g, !last);
                }
            }

            /* Stop if found */
            if (q->data == data)
            {
                break;
            }

            last = dir;
            dir = q->data < data;

            /* Update helpers */
            if (g != NULL)
            {
                t = g;
            }

            g = p, p = q;
            q = q->link[dir];
        }

        /* Update root */
        tree->root = head.link[1];
    }

    /* Make root black */
    tree->root->red = 0;

    return 1;
}

int RedBlackTree::tree_remove( rb_tree *tree, Data data)
{
    if (tree->root != NULL)
    {
         tree_node head = { 0 }; /* False tree root */
         tree_node *q, *p, *g; /* Helpers */
         tree_node *f = NULL;  /* Found item */
        int dir = 1;

        /* Set up helpers */
        q = &head;
        g = p = NULL;
        q->link[1] = tree->root;

        /* Search and push a red down */
        while (q->link[dir] != NULL)
        {
            int last = dir;

            /* Update helpers */
            g = p, p = q;
            q = q->link[dir];
            dir = q->data < data;

            /* Save found node */
            if (q->data == data)
            {
                f = q;
            }

            /* Push the red node down */
            if (!is_red(q) && !is_red(q->link[dir]))
            {
                if (is_red(q->link[!dir]))
                {
                    p = p->link[last] = tree_single(q, dir);
                }
                else if (!is_red(q->link[!dir]))
                {
                     tree_node *s = p->link[!last];

                    if (s != NULL)
                    {
                        if (!is_red(s->link[!last]) && !is_red(s->link[last]))
                        {
                            /* Color flip */
                            p->red = 0;
                            s->red = 1;
                            q->red = 1;
                        }
                        else
                        {
                            int dir2 = g->link[1] == p;

                            if (is_red(s->link[last]))
                            {
                                g->link[dir2] = tree_double(p, last);
                            }
                            else if (is_red(s->link[!last]))
                            {
                                g->link[dir2] = tree_single(p, last);
                            }

                            /* Ensure correct coloring */
                            q->red = g->link[dir2]->red = 1;
                            g->link[dir2]->link[0]->red = 0;
                            g->link[dir2]->link[1]->red = 0;
                        }
                    }
                }
            }
        }

        /* Replace and remove if found */
        if (f != NULL)
        {
            f->data = q->data;
            p->link[p->link[1] == q] = q->link[q->link[0] == NULL];
            delete q;
        }

        /* Update root and make it black */
        tree->root = head.link[1];

        if (tree->root != NULL)
        {
            tree->root->red = 0;
        }
    }

    return 1;
}

int RedBlackTree::tree_rb_assert( tree_node *root)
{
    int lh, rh;

    if (root == NULL)
    {
        return 1;
    }
    else
    {
         tree_node *ln = root->link[0];
         tree_node *rn = root->link[1];

        /* Consecutive red links */
        if (is_red(root))
        {
            if (is_red(ln) || is_red(rn))
            {
                std::cout<<"Red violation"<<std::endl;
                return 0;
            }
        }

        lh = tree_rb_assert(ln);
        rh = tree_rb_assert(rn);

        /* Invalid binary search tree */
        if ((ln != NULL && ln->data >= root->data) || (rn != NULL && rn->data <= root->data))
        {
            std::cout<<"Binary tree violation"<<std::endl;
            return 0;
        }

        /* Black height mismatch */
        if (lh != 0 && rh != 0 && lh != rh)
        {
            std::cout<<"Black violation"<<std::endl;
            return 0;
        }

        /* Only count black links */
        if (lh != 0 && rh != 0)
        {
            return is_red(root) ? lh : lh + 1;
        }
        else
        {
            return 0;
        }
    }
}

tree_node* RedBlackTree::maximum_node( rb_tree *root)
{

    tree_node* ptr = root->root;
    while (ptr->link[1] != NULL)
        ptr = ptr->link[1];
    return ptr;
}

tree_node* RedBlackTree::minimum_node( rb_tree *root)
{
    tree_node* ptr = root->root;
    while (ptr->link[0] != NULL)
        ptr = ptr->link[0];
    return ptr;
}

void RedBlackTree::getTitle()
{
    std::cout<<"Red-Black Tree\n\n"<<std::endl;
}
