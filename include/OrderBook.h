 #ifndef ORDERBOOK_H
#define ORDERBOOK_H
#include "Heap.h"
#include "Order.h"
#include "Treap.h"
#include "RedBlackTree.h"
#include "json/json.h"
#include <string>
using namespace std;


class OrderBook
{
    public:
        OrderBook(int);
        virtual ~OrderBook();
        double MaxBid();
        double MinAsk();
        void ReadFile();

     private:
        void ReadAsks(const Json::Value& root, std::vector<Data>& asks_storage);
        void ReadBids(const Json::Value& root, std::vector<Data>& bids_storage);
        void ReadSequence(const Json::Value& root);
        void ReadProductId(const Json::Value& root);
        void ReadOrder(const Json::Value& root, std::vector<Order>& orders_storage);
        void ProcessAsks(std::vector<Data>& asks_storage);
        void ProcessBids(std::vector<Data>& bidss_storage);
        void ProcessOrders(std::vector<Order>& orders_storage);
        void Parse(std::ifstream& DataFile, std::vector<Data>& asks_storage, std::vector<Data>& bids_storage,
                      std::vector<Order>& orders_storage);
        void Process(std::vector<Data>& asks_storage, std::vector<Data>& bids_storage, std::vector<Order>& orders_storage);



     private:
        Base*  ask_tree;
        Base*  bid_tree;
        double removeTime;
        double insertTime;

};



#endif // ORDERBOOK_H
