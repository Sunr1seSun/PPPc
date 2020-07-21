#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <string>

typedef uint32_t lb_type;
typedef uint32_t tag_off;

class easyTag{
private:
public:
    std::map<std::set<tag_off>, lb_type> forward;
    std::vector<std::set<tag_off>*> nodes; 
public:
    easyTag();
    ~easyTag();
    lb_type insert(tag_off pos);

    lb_type combine(lb_type lb1, lb_type lb2);

    const std::vector<tag_off> find(lb_type lb);

    std::string to_string(lb_type lb);
};
easyTag::easyTag(){}
easyTag::~easyTag(){}

lb_type easyTag::insert(tag_off pos){
    lb_type lb = nodes.size();
    std::set<tag_off>* cur = new std::set<tag_off>();
    cur->insert(pos);
    nodes.push_back(cur);
    forward.insert(std::pair<std::set<tag_off>, lb_type>(*cur, lb));
    return lb; 
}

lb_type easyTag::combine(lb_type lb1, lb_type lb2){
    std::set<tag_off>* s1 = nodes[lb1];
    std::set<tag_off>* s2 = nodes[lb2];

    std::set<tag_off> *tmp = new std::set<tag_off>(*s1);
    (*tmp).insert(s2->begin(), s2->end());
    auto iter = forward.find(*tmp);
    if(iter == forward.end()){
        forward.insert(std::pair<std::set<tag_off>, lb_type>(*tmp, nodes.size()));
        nodes.push_back(tmp);
        return nodes.size();
    }else{
        delete tmp;
        return iter->second;
    }
}

const std::vector<tag_off> easyTag::find(lb_type lb){
    return std::vector<tag_off>((*(nodes[lb])).begin(),(*(nodes[lb])).end());
}

std::string easyTag::to_string(lb_type lb) {
    std::string tmp = "{";
    for(auto x: *nodes[lb]){
        tmp += std::to_string(x) + ",";
    }
    *(tmp.end()-1) = '}';
    return tmp;
}