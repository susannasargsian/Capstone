#include "OrderBook.h"
#include "Utilities.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <stdio.h>
#include <stdlib.h>
using namespace std;


OrderBook::OrderBook()
{

}

OrderBook::~OrderBook()
{
    //dtor
}


double OrderBook:: MaxBid()
{
    return bid_tree.getMax().price;
}


double OrderBook:: MinAsk()
{
     return ask_tree.getMin().price;
}


void OrderBook :: ReadAsks(const Json::Value& root)
{
    const Json::Value all_asks = root["asks"];
    int all_asks_size = all_asks.size();
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
            // std::cout <<std::setprecision(3)<<std::fixed<< "Price="<<price<<endl;
            // std::cout <<std::setprecision(6)<<std::fixed<< "Size="<<size<<endl;


             Data d(price, size, o);
             ask_tree.insert(d);
         }

    }


    std::cout<<"Minimum Ask Value = "<<std::setprecision(6)<<std::fixed<<MinAsk()<<std::endl;


}


void OrderBook :: ReadBids(const Json::Value& root)
{
    const Json::Value all_bids = root["bids"];
    int all_bids_size = all_bids.size();
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
             bid_tree.insert(d);
         }
    }
    std::cout<<"Maximum Bid Value = "<<std::setprecision(6)<<std::fixed<<MaxBid()<<std::endl;
}


void OrderBook::ReadSequence(const Json::Value& root)
{
    const Json::Value all_sequences = root["sequence"];
}


void OrderBook::ReadProductId(const Json::Value& root)
{
    const Json::Value productId = root["product_id"];
}


void OrderBook::ReadOrder(const std::string& InitData)
{
    Json::Value root;
    Json::Reader Reader;

    Reader.parse(InitData, root);

    const Json::Value type = root["type"];
    const Json::Value side = root["side"];
    double price = toDouble(root["price"].asString(),6);
    double size = toDouble(root["size"].asString(),6);
    std::string order_id = root["order_id"].asString();
    Data d(price,size,order_id);

    if(type.asString()=="done")
    {

        if(side.asString()=="sell")
        {
            ask_tree.remove(d);
        }
        else if(side.asString()=="buy")
        {
            bid_tree.remove(d);
        }
    }
    else if(type.asString()=="open")
    {

        if(side.asString()=="sell")
        {
            ask_tree.insert(d);
        }

        else if(side.asString()=="buy")
        {
            bid_tree.insert(d);
        }
    }
    else if(type.asString()=="change")
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
        if(side.asString()=="sell")
        {
            ask_tree.update(old_d,new_d);
        }

        else if(side.asString()=="buy")
        {
            bid_tree.update(old_d,new_d);
        }


    }

}


void OrderBook::InitOrderBook(const std::string& InitData)
{
    Json::Value root;
    Json::Reader Reader;

    Reader.parse(InitData, root);

    ReadAsks(root);
    ReadBids(root);
    ReadSequence(root);
    ReadProductId(root);
}


void OrderBook::ReadFile()
{
    ask_tree.getTitle();
    std::ifstream DataFile("Right_File.txt", std::ifstream::binary);
    std::string CurLine;
    if(getline(DataFile, CurLine))
    {
        int start_s=clock();
        InitOrderBook(CurLine);
        int stop_s=clock();
        cout << "Execution time of initialization: " << (stop_s-start_s)/double(CLOCKS_PER_SEC)<< endl;
    }

    bool OK=false;
    int start_s=clock();
    do {
        OK = getline(DataFile, CurLine);
        if(OK) {

            ReadOrder(CurLine);

        }
    } while(OK );
    int stop_s=clock();
    cout << "Execution time of updating orders: " << (stop_s-start_s)/double(CLOCKS_PER_SEC)<< endl;

    DataFile.close();

}





