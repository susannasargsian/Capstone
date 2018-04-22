 #ifndef ORDERBOOK_H
#define ORDERBOOK_H
#include "Heap.h"
#include "Treap.h"
#include "RBTree.h"
#include "RBTRee.h"
#include "json/json.h"
#include <string>
using namespace std;


class OrderBook
{
    public:
        OrderBook();
        virtual ~OrderBook();
        double MaxBid();
        double MinAsk();
        void ReadFile();

     private:
        void InitOrderBook(const std::string& InitData);
        void ReadOrder(const std::string& InitData);
        void ReadAsks(const Json::Value& root);
        void ReadBids(const Json::Value& root);
        void ReadSequence(const Json::Value& root);
        void ReadProductId(const Json::Value& root);

     private:
        RBTree  bid_tree;
        RBTree  ask_tree;

};



#endif // ORDERBOOK_H
