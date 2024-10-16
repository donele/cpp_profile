#include <iostream>
#include <map>
#include <vector>
#include <nasdaq_vwap.h>
using namespace std;

void Vwap::add_trade(int volume, double prc) {
    sum_share += volume;
    sum_wgtd_prc += volume * prc;
}

double Vwap::get_vwap() const {
    if(sum_share > 0) {
        return sum_wgtd_prc / sum_share;
    }
    return 0.;
}

VwapColl::VwapColl():
    _status(Status::None),
    _last_hour(0) {
    _msglen = {
        {'S', 11},
        {'R', 38},
        {'H', 24},
        {'Y', 19},
        {'L', 25},
        {'V', 34},
        {'W', 11},
        {'K', 27},
        {'J', 34},
        {'h', 20},
        {'A', 35},
        {'F', 39},
        {'E', 30},
        {'C', 35},
        {'X', 22},
        {'D', 18},
        {'U', 34},
        {'P', 43},
        {'Q', 39},
        {'B', 18},
        {'I', 49},
        {'N', 19},
        {'O', 47}};
}

unsigned long VwapColl::get_int64(const std::vector<char>& buf, int off, int len) const {
    if(len > sizeof(unsigned long)) {
        cerr << "Warning: possible precision loss\n";
    }
    unsigned long i64 = 0;
    int cnt = 0;
    for(int i = off + len - 1; i >= off; --i) {
        unsigned long i_int = buf[i] & 0xFF;
        i64 |= i_int << 8 * cnt++;
    }
    return i64;
}

string VwapColl::get_string(const std::vector<char>& buf, int off, int len) const {
    string str;
    for(int i = off; i < off + len; ++i) {
        if(isalnum(buf[i])) {
            str += buf[i];
        } else {
            break;
        }
    }
    return str;
}

double VwapColl::get_double(const std::vector<char>& buf, int off, int len, int dec) const {
    if(len > sizeof(unsigned long)) {
        cerr << "Warning: possible precision loss\n";
    }
    unsigned long i64 = get_int64(buf, off, len);
    double d = (double)i64;
    for(int i = 0; i < dec; ++i)
        d /= 10.;
    return d;
}

void VwapColl::handle_system_event(const vector<char>& buf) {
    char event_code = buf[off_system_event_event_code];
    if(event_code == 'O') {
        _status = Status::MsgStart;
    } else if(event_code == 'S') {
        _status = Status::Start;
    } else if(event_code == 'Q') {
        _status = Status::Open;
    } else if(event_code == 'M') {
        unsigned long ts = get_int64(buf, off_system_event_ts, len_system_event_ts);
        print_vwap(ts);
        _status = Status::Close;
    } else if(event_code == 'E') {
        _status = Status::End;
    } else if(event_code == 'C') {
        _status = Status::MsgEnd;
    }
}

void VwapColl::handle_stock_directory(const vector<char>& buf) {
    unsigned long locate = get_int64(buf, off_stock_dir_locate, len_stock_dir_locate);
    string symbol = get_string(buf, off_stock_dir_symbol, len_stock_dir_symbol);
    if(!symbol.empty()) {
        _symbol_map[locate] = symbol;
    }
}

void VwapColl::handle_add_order(const vector<char>& buf) {
    unsigned long ref = get_int64(buf, off_add_ref, len_add_ref);
    double prc = get_double(buf, off_add_price, len_add_price, dec_add_price);
    _prc_map[ref] = prc;
}

void VwapColl::handle_add_mpid_order(const vector<char>& buf) {
    handle_add_order(buf);
}

void VwapColl::handle_order_executed(const vector<char>& buf) {
    unsigned long locate = get_int64(buf, off_ord_exec_locate, len_ord_exec_locate);
    unsigned long ts = get_int64(buf, off_ord_exec_ts, len_ord_exec_ts);
    unsigned long ref = get_int64(buf, off_ord_exec_ref, len_ord_exec_ref);
    unsigned long shares = get_int64(buf, off_ord_exec_shares, len_ord_exec_shares);
    double prc = _prc_map[ref];
    add_trade(locate, shares, prc, ts);
}

void VwapColl::handle_order_executed_with_price(const vector<char>& buf) {
    unsigned long locate = get_int64(buf, off_ord_exec_wp_locate, len_ord_exec_wp_locate);
    unsigned long ts = get_int64(buf, off_ord_exec_wp_ts, len_ord_exec_wp_ts);
    unsigned long shares = get_int64(buf, off_ord_exec_wp_shares, len_ord_exec_wp_shares);
    double prc = get_double(buf, off_ord_exec_wp_price, len_ord_exec_wp_price, dec_ord_exec_wp_price);
    add_trade(locate, shares, prc, ts);
}

void VwapColl::handle_order_replace(const vector<char>& buf) {
    unsigned long locate = get_int64(buf, off_replace_locate, len_replace_locate);
    unsigned long oref = get_int64(buf, off_replace_oref, len_replace_oref);
    unsigned long ref = get_int64(buf, off_replace_ref, len_replace_ref);
    double prc = get_double(buf, off_replace_price, len_replace_price, dec_replace_price);
    _prc_map.erase(oref);
    _prc_map[ref] = prc;
}

void VwapColl::handle_trade(const vector<char>& buf) {
    unsigned long locate = get_int64(buf, off_trade_locate, len_trade_locate);
    unsigned long ts = get_int64(buf, off_trade_ts, len_trade_ts);
    unsigned long shares = get_int64(buf, off_trade_shares, len_trade_shares);
    double prc = get_double(buf, off_trade_price, len_trade_price, dec_trade_price);
    add_trade(locate, shares, prc, ts);
}

void VwapColl::handle_cross_trade(const vector<char>& buf) {
    unsigned long locate = get_int64(buf, off_cross_locate, len_cross_locate);
    unsigned long ts = get_int64(buf, off_cross_ts, len_cross_ts);
    unsigned long shares = get_int64(buf, off_cross_shares, len_cross_shares);
    double prc = get_double(buf, off_cross_price, len_cross_price, dec_cross_price);
    add_trade(locate, shares, prc, ts);
}

void VwapColl::run() {
    vector<char> buf;
    buf.reserve(_buflen);
    while(fread(buf.data(), sizeof(buf[0]), 1, stdin)) {
        char c = buf[0];
        if(c >= 'A' && c <= 'z') {
            auto it = _msglen.find(c);
            if(it != _msglen.end()) {
                size_t bytes_read = fread(&buf[1], sizeof(buf[0]), it->second, stdin);
                if(bytes_read != it->second)
                    continue;
            }

            switch(c) {
                case 'S':
                    handle_system_event(buf);
                    break;
                case 'R':
                    handle_stock_directory(buf);
                    break;
                case 'A':
                    handle_add_order(buf);
                    break;
                case 'E':
                    handle_order_executed(buf);
                    break;
                case 'C':
                    handle_order_executed_with_price(buf);
                    break;
                case 'P':
                    handle_trade(buf);
                    break;
                case 'Q':
                    handle_cross_trade(buf);
                    break;
            }
        }
    }
}

void VwapColl::add_trade(int locate, int share, double prc, unsigned long ts) {
    unsigned long ts_hour = ts / _hour_ns;
    if(_status == Status::Open) {
        if(ts_hour == _last_hour + 1) {
            print_vwap(ts);
        }
        _last_hour = ts_hour;
        _vwcoll[locate].add_trade(share, prc);
    }
}

double VwapColl::get_vwap(int locate) const {
    auto it = _vwcoll.find(locate);
    if(it != _vwcoll.end()) {
        return it->second.get_vwap();
    }
    return 0.;
}

void VwapColl::print_vwap(unsigned long ts) const {
    int hr = ts / _hour_ns;
    int mm = ts % _hour_ns / _minute_ns;
    printf("Beginning of VWAP at %02d:%02d\n", hr, mm);
    for(auto& kv : _vwcoll) {
        int locate = kv.first;
        auto itsym = _symbol_map.find(locate);
        if(itsym != _symbol_map.end()) {
            const string& symbol = itsym->second;
            double vwap = kv.second.get_vwap();
            printf("%s %.4f\n", symbol.c_str(), vwap);
        }
    }
    printf("End of VWAP at %02d:%02d\n", hr, mm);
}
