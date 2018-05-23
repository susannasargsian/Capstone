#include "OrderBook.h"
#include "Utilities.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <stdio.h>
#include <stdlib.h>
using namespace std;


OrderBook::OrderBook(int type) : ask_tree(0), bid_tree(0), removeTime(0), insertTime(0)
{
  switch (type)
  {
      case 1:
        ask_tree=new MinHeap();
        bid_tree=new MaxHeap();
      break;

      case 2:
        ask_tree=new Treap();
        bid_tree=new Treap();
      break;

      case 3:
        ask_tree=new RedBlackTree();
        bid_tree=new RedBlackTree();
        break;
      default:
      cout<<"None of three types selected"<<endl;
  }
}

OrderBook::~OrderBook()
{
    delete ask_tree;
    delete bid_tree;
}


double OrderBook:: MaxBid()
{
    return bid_tree->getMax().price;
}


double OrderBook:: MinAsk()
{
     return ask_tree->getMin().price;
}

void OrderBook:: ProcessAsks(std::vector <Data>& asks_storage)
{
    int start_s=clock();
    size_t all_asks_size=asks_storage.size();
    for( size_t i=0; i<all_asks_size; i++)
    {
        ask_tree->insert(asks_storage[i]);
    }
    int stop_s=clock();
    insertTime+=(stop_s-start_s)/double(CLOCKS_PER_SEC);
    std::cout<<"Minimum Ask Value = "<<std::setprecision(6)<<std::fixed<<MinAsk()<<std::endl;

}


void OrderBook :: ReadAsks(const Json::Value& root, std::vector <Data>& asks_storage )
{
    const Json::Value all_asks = root["asks"];
    int all_asks_size = all_asks.size();
    asks_storage.resize(all_asks_size);
    for ( int i=0; i<all_asks_size; i++ )
    {
         const Json::Value single_ask = all_asks[i];
         int single_ask_size = single_ask.size();
         if (single_ask_size == 3)
         {
            std::string p = single_ask[0].asString();
            std::string s = single_ask[1].asString();
            std::string o = single_ask[2].asString();


            double price = toDouble( p, 3);
            double size = toDouble( s, 6);

            Data d(price, size, o);
            asks_storage[i]=d;
         }
    }
}

void OrderBook:: ProcessBids(std::vector<Data>& bids_storage)
{
    int start_s=clock();
    size_t all_bids_size = bids_storage.size();
    for( size_t i=0; i<all_bids_size; i++)
    {
        bid_tree->insert(bids_storage[i]);
    }
    int stop_s=clock();
    insertTime += (stop_s-start_s)/double(CLOCKS_PER_SEC);
    std::cout<<"Maximum Bid Value = "<<std::setprecision(6)<<std::fixed<<MaxBid()<<std::endl;
}


void OrderBook :: ReadBids(const Json::Value& root, std::vector<Data>& bids_storage)
{
    const Json::Value all_bids = root["bids"];
    int all_bids_size = all_bids.size();
    bids_storage.resize(all_bids_size);
    for ( int i=0; i<all_bids_size; i++ )
    {
         const Json::Value single_bid = all_bids[i];
         int single_bid_size = single_bid.size();
         if (single_bid_size == 3)
         {
             std::string p = single_bid[0].asString();
             std::string s = single_bid[1].asString();
             std::string o = single_bid[2].asString();

            double price = toDouble( p, 3);
             double size = toDouble( s, 6);

             Data d(price, size, o);
             bids_storage[i]=d;
         }
    }
}


void OrderBook::ReadSequence(const Json::Value& root)
{
    const Json::Value all_sequences = root["sequence"];
}

void OrderBook::ReadProductId(const Json::Value& root)
{
    const Json::Value productId = root["product_id"];
}

void OrderBook::ReadOrder(const Json::Value& root, std::vector<Order>& orders_storage)
{
    const Json::Value type = root["type"];
    const Json::Value side = root["side"];
    double price = toDouble(root["price"].asString(),6);
    double size = toDouble(root["size"].asString(),6);
    std::string order_id = root["order_id"].asString();
    std::string time = root["time"].asString();
    Time tm;
    toTime(time, tm);
    Data d(price,size,order_id);
    Order o(type.asString(), side.asString(), d, tm);

    if(o.type=="change")
    {

        double old_size =size;
        double new_size = size;
        double old_price = price;
        double new_price = price;

        if(root.isMember("old_size") && root.isMember ("new_size"))
        {
            old_size = toDouble(root["old_size"].asString(),6);
            new_size = toDouble(root["new_size"].asString(),6);
        }

        if(root.isMember("old_price") && root.isMember ("new_price"))
        {
            old_price = toDouble(root["old_price"].asString(),6);
            new_price = toDouble(root["new_price"].asString(),6);
        }

        Data old_d(old_price,old_size,order_id);
        Data new_d(new_price,new_size,order_id);
        o.data=old_d;
        o.new_data=new_d;

    }

    orders_storage.push_back(o);

}

void OrderBook:: ProcessOrders(std::vector<Order>& orders_storage)
{
    size_t orders_size = orders_storage.size();
    cout<<orders_size<<endl;
    Time tm = orders_storage[0].time;
    for(size_t i=0; i<orders_size; i++)
    {
        Order& o = orders_storage[i];
        int secs = o.time.Difference(tm);
        if(secs>=1)
        {
            MaxBid();
            MinAsk();
            tm=o.time;
        }


        if(o.type=="done")
        {
            if(o.side=="sell")
            {
                int start_t=clock();
                ask_tree->remove(o.data);
                int stop_t=clock();
                removeTime+=(stop_t-start_t)/double(CLOCKS_PER_SEC);
            }

            else if(o.side=="buy")
            {
                int start_t=clock();
                bid_tree->remove(o.data);
                int stop_t=clock();
                removeTime+=(stop_t-start_t)/double(CLOCKS_PER_SEC);
            }
        }
        else if(o.type=="open")
        {

            if(o.side=="sell")
            {
                int start_t=clock();
                ask_tree->insert(o.data);
                int stop_t=clock();
                insertTime+=(stop_t-start_t)/double(CLOCKS_PER_SEC);
            }

            else if(o.side=="buy")
            {
                int start_t=clock();
                bid_tree->insert(o.data);
                int stop_t=clock();
                insertTime+=(stop_t-start_t)/double(CLOCKS_PER_SEC);

            }
        }
        else if(o.type=="change")
        {
            if(o.side=="sell")
            {
                ask_tree->update(o.data, o.new_data);
            }

            else if(o.side=="buy")
            {
                bid_tree->update(o.data, o.new_data);
            }
        }
    }

    cout<<  "Remove time: "<<removeTime<<std::endl;
    cout<<  "Insert time: "<<insertTime<<std::endl;
}

void OrderBook::Parse(std::ifstream& DataFile, std::vector<Data>& asks_storage, std::vector<Data>& bids_storage,
                      std::vector<Order>& orders_storage )
{
    int start_s=clock();
    Json::Value root;
    Json::Reader Reader;

    std::string CurLine;
    while(getline(DataFile, CurLine))
    {
        Reader.parse(CurLine, root);
        if(root.isMember("asks"))
        {
           ReadAsks(root, asks_storage);
           ReadBids(root, bids_storage);
           ReadSequence(root);
           ReadProductId(root);
        }
        else if(root.isMember("order_id"))
        {
            ReadOrder(root, orders_storage);
        }
    }
    int stop_s=clock();
    cout << "Execution time of Parsing: " << (stop_s-start_s)/double(CLOCKS_PER_SEC)<< endl;

}

void OrderBook::Process(std::vector<Data>& asks_storage, std::vector<Data>& bids_storage, std::vector<Order>& orders_storage)
{
    int start_s=clock();

    ProcessAsks(asks_storage);
    ProcessBids(bids_storage);
    ProcessOrders (orders_storage);

    int stop_s=clock();
    cout << "Execution time of Processing: " << (stop_s-start_s)/double(CLOCKS_PER_SEC)<< endl;
}


void OrderBook::ReadFile()
{
    int start_s=clock();

    ask_tree->getTitle();

    std::vector<Data> asks_storage;
    std::vector<Data> bids_storage;
    std::vector<Order> orders_storage;

    std::ifstream DataFile("Wanted.txt", std::ifstream::in);
    Parse(DataFile, asks_storage, bids_storage, orders_storage);
    DataFile.close();
    Process(asks_storage, bids_storage, orders_storage);
    int start_1=clock();
    std::cout<<"Minimum Ask Value = "<<std::setprecision(6)<<std::fixed<<MinAsk()<<std::endl;
    int stop_1=clock();
    std::cout<<"Min ask processing time: "<<(stop_1-start_1)/double(CLOCKS_PER_SEC)<<std::endl;
    int start_2=clock();
    std::cout<<"Maximum Bid Value = "<<std::setprecision(6)<<std::fixed<<MaxBid()<<std::endl;
    int stop_2=clock();
    std::cout<<"Max bid processing time: "<<(stop_2-start_2)/double(CLOCKS_PER_SEC)<<std::endl;
    std::cout<<  "Remove time: "<<removeTime<<std::endl;
    std::cout<<  "Insert time: "<<insertTime<<std::endl;

    int stop_s=clock();
    cout << "Execution time: " << (stop_s-start_s)/double(CLOCKS_PER_SEC)<<std::endl;
}





