#ifndef __nasdaq_vwap_h__
#define __nasdaq_vwap_h__
#include <vector>
#include <string>
#include <unordered_map>

const int off_system_event_event_code = 11;
const int off_system_event_ts = 5;
const int len_system_event_ts = 6;

const int off_stock_dir_locate = 1;
const int len_stock_dir_locate = 2;
const int off_stock_dir_symbol = 11;
const int len_stock_dir_symbol = 8;

const int off_add_ref = 11;
const int len_add_ref = 8;
const int off_add_price = 32;
const int len_add_price = 4;
const int dec_add_price = 4;

const int off_ord_exec_locate = 1;
const int len_ord_exec_locate = 2;
const int off_ord_exec_ts = 5;
const int len_ord_exec_ts = 6;
const int off_ord_exec_ref = 11;
const int len_ord_exec_ref = 8;
const int off_ord_exec_shares = 19;
const int len_ord_exec_shares = 4;

const int off_ord_exec_wp_locate = 1;
const int len_ord_exec_wp_locate = 2;
const int off_ord_exec_wp_ts = 5;
const int len_ord_exec_wp_ts = 6;
const int off_ord_exec_wp_shares = 19;
const int len_ord_exec_wp_shares = 4;
const int off_ord_exec_wp_price = 32;
const int len_ord_exec_wp_price = 4;
const int dec_ord_exec_wp_price = 4;

const int off_replace_locate = 1;
const int len_replace_locate = 2;
const int off_replace_oref = 11;
const int len_replace_oref = 8;
const int off_replace_ref = 19;
const int len_replace_ref = 8;
const int off_replace_price = 31;
const int len_replace_price = 4;
const int dec_replace_price = 4;

const int off_trade_locate = 1;
const int len_trade_locate = 2;
const int off_trade_ts = 5;
const int len_trade_ts = 6;
const int off_trade_shares = 20;
const int len_trade_shares = 4;
const int off_trade_price = 32;
const int len_trade_price = 4;
const int dec_trade_price = 4;

const int off_cross_locate = 1;
const int len_cross_locate = 2;
const int off_cross_ts = 5;
const int len_cross_ts = 6;
const int off_cross_shares = 11;
const int len_cross_shares = 8;
const int off_cross_price = 27;
const int len_cross_price = 4;
const int dec_cross_price = 4;

enum class Status {
    None,
    MsgStart,
    Start,
    Open,
    Close,
    End,
    MsgEnd
};

struct Vwap {
    int sum_share = 0;
    double sum_wgtd_prc = 0.;
    void add_trade(int share, double prc);
    double get_vwap() const;
};

class VwapColl {
    public:
        VwapColl();
        void run();
    private:
        Status _status;
        int _last_hour;

        constexpr static unsigned long _hour_ns = 60*60*1e9;
        constexpr static unsigned long _minute_ns = 60*1e9;
        constexpr static int _buflen = 64;

        std::unordered_map<int, double> _prc_map;
        std::unordered_map<int, std::string> _symbol_map;
        std::unordered_map<char, int> _msglen;
        std::unordered_map<int, Vwap> _vwcoll;

        void add_trade(int locate, int share, double prc, unsigned long ts);
        double get_vwap(int locate) const;
        void print_vwap(unsigned long ts) const;

        unsigned long get_int64(const std::vector<char>& buf, int off, int len) const;
        std::string get_string(const std::vector<char>& buf, int off, int len) const;
        double get_double(const std::vector<char>& buf, int off, int len, int dec) const;

        void handle_system_event(const std::vector<char>& buf);
        void handle_stock_directory(const std::vector<char>& buf);
        void handle_add_order(const std::vector<char>& buf);
        void handle_add_mpid_order(const std::vector<char>& buf);
        void handle_order_executed(const std::vector<char>& buf);
        void handle_order_executed_with_price(const std::vector<char>& buf);
        void handle_order_replace(const std::vector<char>& buf);
        void handle_trade(const std::vector<char>& buf);
        void handle_cross_trade(const std::vector<char>& buf);
};

#endif
